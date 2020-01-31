X_INIT$(${object_name}_init) {
    // Set baud rate
    const u16 ubrr = akat_cpu_freq_hz() / (9600 * 8L) - 1;
    UBRR${uart}H = ubrr >> 8;
    UBRR${uart}L = ubrr % 256;
    UCSR${uart}A = H(U2X${uart});

    // Set frame format: 8N1
    UCSR${uart}C = H(UCSZ${uart}0) | H(UCSZ${uart}1);

    // Enable transmitter, receiver and interrupt for receiver (interrupt for 'byte is received')
    UCSR${uart}B = H(TXEN${uart}) | H(RXEN${uart}) | H(RXCIE${uart});
}

// --- - - - - - - - - - - - RX - - - - - - - -  - - - - - - - --
// Interrupt handler for 'byte is received' event..

GLOBAL$() {
    STATIC_VAR$(volatile u8 ${object_name}_rx_bytes_buf[${rx_buf_size}], initial = {});
    STATIC_VAR$(volatile u8 ${object_name}_rx_overflow_count);
    STATIC_VAR$(volatile u8 ${object_name}_rx_next_empty_idx);
    STATIC_VAR$(volatile u8 ${object_name}_rx_next_read_idx);
}

ISR(USART${uart}_RX_vect) {
    u8 b = UDR${uart}; // we must read here, no matter what, to clear interrupt flag

    u8 new_next_empty_idx = (${object_name}_rx_next_empty_idx + AKAT_ONE) & (${rx_buf_size} - 1);
    if (new_next_empty_idx == ${object_name}_rx_next_read_idx) {
        ${object_name}_rx_overflow_count += AKAT_ONE;
        // Don't let it overflow!
        if (!${object_name}_rx_overflow_count) {
            ${object_name}_rx_overflow_count -= AKAT_ONE;
        }
    } else {
        ${object_name}_rx_bytes_buf[${object_name}_rx_next_empty_idx] = b;
        ${object_name}_rx_next_empty_idx = new_next_empty_idx;
    }
}

//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ${object_name}(CO2): This thread processes input from ${object_name}_rx_bytes_buf that gets populated in ISR

GLOBAL$() {
    STATIC_VAR$(u8 ${object_name}_crc_errors);
    STATIC_VAR$(u16 ${object_name}_concentration, initial = 0);
    STATIC_VAR$(u8 ${object_name}_updated_deciseconds_ago, initial = 255);
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    // Maintain freshness
    ${object_name}_updated_deciseconds_ago += AKAT_ONE;
    if (!${object_name}_updated_deciseconds_ago) {
        // We can't go beyond 255
        ${object_name}_updated_deciseconds_ago -= AKAT_ONE;
    }
}

THREAD$(${object_name}_reader) {
    STATIC_VAR$(u8 dequeued_byte);
    STATIC_VAR$(u8 crc);

    // byte of protocol, we don't put them into named variables until CRC is checked
    STATIC_VAR$(u8 b2);
    STATIC_VAR$(u8 b3);
    STATIC_VAR$(u8 b4);
    STATIC_VAR$(u8 b5);
    STATIC_VAR$(u8 b6);
    STATIC_VAR$(u8 b7);

    // Gets byte from ${object_name}_rx_bytes_buf buffer.
    SUB$(dequeue_byte) {
        // Wait until there is something to read
        WAIT_UNTIL$(${object_name}_rx_next_empty_idx != ${object_name}_rx_next_read_idx, unlikely);

        // Read byte first, then increment idx!
        dequeued_byte = ${object_name}_rx_bytes_buf[${object_name}_rx_next_read_idx];
        ${object_name}_rx_next_read_idx = (${object_name}_rx_next_read_idx + 1) & (${rx_buf_size} - 1);
        crc += dequeued_byte;
    }

    // - - - - - - - - - - -
    // Main loop in thread (thread will yield on calls to YIELD$ or WAIT_UNTIL$)
    while(1) {
        CALL$(dequeue_byte);

    try_interpret_as_command:
        if (dequeued_byte == 0xFF) {
            // 0xFF means start of the command...

            // CRC starts calculation only after 0xFF byte
            crc = 0;

            // Read command identifier
            CALL$(dequeue_byte);

            // 0x86 - Read CO2 concentration..
            if (dequeued_byte == 0x86) {
                CALL$(dequeue_byte); b2 = dequeued_byte;
                CALL$(dequeue_byte); b3 = dequeued_byte;
                CALL$(dequeue_byte); b4 = dequeued_byte;
                CALL$(dequeue_byte); b5 = dequeued_byte;
                CALL$(dequeue_byte); b6 = dequeued_byte;
                CALL$(dequeue_byte); b7 = dequeued_byte;

                // Check CRC
                CALL$(dequeue_byte);
                crc -= dequeued_byte;
                crc = 0xFF - crc + 1;
                if (dequeued_byte == crc) {
                    ${object_name}_concentration = b2 * 256 + b3;
                    ${object_name}_updated_deciseconds_ago = 0;
                } else {
                    // CRC doesn't match
                    ${object_name}_crc_errors += 1;
                }
            } else {
                // Wrong command... may be 0xFF? Then we must try to use it as start of command.
                goto try_interpret_as_command;
            }
        }
    }
}

// --- - - - - - - - - - - - TX - - - - - - - - - - - - - - -

GLOBAL$() {
    STATIC_VAR$(u8 ${object_name}_command_countdown);
}

X_EVERY_DECISECOND$(${object_name}_ticker) {
    if (${object_name}_command_countdown) {
        ${object_name}_command_countdown -= 1;
    }
}

THREAD$(${object_name}_writer) {
    STATIC_VAR$(u8 byte_to_send);

    SUB$(send_byte) {
        // Wait until USART0 is ready to transmit next byte
        // from 'byte_to_send';
        WAIT_UNTIL$(UCSR${uart}A & H(UDRE${uart}), unlikely);
        UDR${uart} = byte_to_send;
    }

    SUB$(send_read_gas_command) {
        // Send command sequence
        byte_to_send = 0xFF; CALL$(send_byte); // Header
        byte_to_send = 0x01; CALL$(send_byte); // Sensor #1
        byte_to_send = 0x86; CALL$(send_byte); // Command (Read gas concentration)

        // 5 times zero
        byte_to_send = 0x00;
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);

        byte_to_send = 0x79; CALL$(send_byte); // CRC
    }

    while(1) {
        // TODO: Disable ABC, see all the comments here https://github.com/letscontrolit/ESPEasy/issues/466

        // Wait until it's time to send the command sequence
        // This counter will be incremented every 0.1 second in the X_EVERY_DECISECOND above
        co2_command_countdown = 10; // TODO: Try to use lower value
        WAIT_UNTIL$(${object_name}_command_countdown == 0, unlikely);

        CALL$(send_read_gas_command);
    }
}

// --- - - - - - - - - - - - Interface - - - - - - - - - - - - - - -

OBJECT$(${object_name}) {
    METHOD$(u8 get_rx_overflow_count(), inline) {
        return ${object_name}_rx_overflow_count;
    }

    METHOD$(u8 get_crc_errors(), inline) {
        return ${object_name}_crc_errors;
    }

    METHOD$(u16 get_concentration(), inline) {
        return ${object_name}_concentration;
    }

    METHOD$(u8 get_updated_deciseconds_ago(), inline) {
        return ${object_name}_updated_deciseconds_ago;
    }
}
