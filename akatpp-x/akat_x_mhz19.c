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
    STATIC_VAR$(u8 ${object_name}_abc_setup_needed);
    STATIC_VAR$(u16 ${object_name}_abc_setups);
    STATIC_VAR$(u32 ${object_name}_deciseconds_until_abc);
    STATIC_VAR$(u8 ${object_name}_crc_errors);
    STATIC_VAR$(u8 ${object_name}_update_id);
    STATIC_VAR$(u16 ${object_name}_concentration);
    STATIC_VAR$(u16 ${object_name}_clamped_concentration);
    STATIC_VAR$(u16 ${object_name}_raw_concentration);
    STATIC_VAR$(u8 ${object_name}_temperature);
    STATIC_VAR$(u8 ${object_name}_updated_deciseconds_ago, initial = 255);
    STATIC_VAR$(u8 ${object_name}_next_concentration_command_idx);
    STATIC_VAR$(u8 ${object_name}_different_concentration_type_reads_done);

    // https://habr.com/ru/post/401363/
    // and other pages... hard to tell what it is, likely
    //  s - status
    //  u - uncorrect minimum value of CO2 measured during previous 24h. Used for ABC (Automatic Baseline Correction).
    STATIC_VAR$(u8 ${object_name}_s);
    STATIC_VAR$(u16 ${object_name}_u);
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    // Maintain freshness
    ${object_name}_updated_deciseconds_ago += AKAT_ONE;
    if (!${object_name}_updated_deciseconds_ago) {
        // We can't go beyond 255
        ${object_name}_updated_deciseconds_ago -= AKAT_ONE;
    }

    // Maintain deciseconds until next ABC
    if (${object_name}_deciseconds_until_abc) {
        ${object_name}_deciseconds_until_abc -= 1;
    } else {
        ${object_name}_abc_setup_needed = 1;
        ${object_name}_deciseconds_until_abc = (u32)12 * 60 * 60 * 10; // 12 hours
    }
}

THREAD$(${object_name}_reader) {
    STATIC_VAR$(u8 dequeued_byte);
    STATIC_VAR$(u8 crc);
    STATIC_VAR$(u8 command);

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

            // 0x86 - Read CO2 concentration.. 0x79 is ack for ABC setup
            if (dequeued_byte == 0x86 || dequeued_byte == 0x79 || dequeued_byte == 0x84 || dequeued_byte == 0x85) {
                command = dequeued_byte;

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
                    if (command == 0x86) {
                        // CO2 read
                        if (b4 < 90 && b4 > 30) {
                            ${object_name}_clamped_concentration = (((u16)b2) << 8) + b3;
                            ${object_name}_temperature = b4 - 40;

                            // Only if have got response for 0x84 and 0x85
                            if (${object_name}_different_concentration_type_reads_done == 2) {
                                ${object_name}_updated_deciseconds_ago = 0;
                                ${object_name}_update_id += 1;
                            }
                        }
                        ${object_name}_s = b5;
                        ${object_name}_u = (((u16)b6) << 8) + b7;
                    } else if (command == 0x84) {
                        ${object_name}_raw_concentration = (((u16)b2) << 8) + b3;
                        ${object_name}_different_concentration_type_reads_done += 1;
                    } else if (command == 0x85) {
                        ${object_name}_concentration = (((u16)b4) << 8) + b5;
                        ${object_name}_different_concentration_type_reads_done += 1;
                    } else if (command == 0x79) {
                        // ABC setup result. b2 is 1 in ACK response.
                        if (b2 == 1) {
                            ${object_name}_abc_setup_needed = 0;
                            ${object_name}_abc_setups += 1;
                        }
                    }
                } else {
                    // CRC doesn't match
                    ${object_name}_crc_errors += 1;
                }
            } else {
                // Wrong command... may be 0xFF? Then we must try to use it as start of command.
                goto try_interpret_as_command;
            }
        } else {
            // Unknown byte
            % if debug:
            ${debug}(dequeued_byte);
            % endif
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

    SUB$(send_read_concentration_command) {
        // Send command sequence
        byte_to_send = 0xFF; CALL$(send_byte); // Header
        byte_to_send = 0x01; CALL$(send_byte); // Sensor #1

        if (${object_name}_next_concentration_command_idx == 0) {
            ${object_name}_different_concentration_type_reads_done = 0;

            byte_to_send = 0x84; // Command (Read raw light sensor value)
        } else if (${object_name}_next_concentration_command_idx == 1) {
            byte_to_send = 0x85; // Command (Read raw CO2)
        } else {
            byte_to_send = 0x86; // Command (Read CO2 concentration)
        }
        CALL$(send_byte);

        // 5 times zero
        byte_to_send = 0x00;
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);

        // CRC
        if (${object_name}_next_concentration_command_idx == 0) {
            byte_to_send = 0x7b; // Command (Read raw light sensor value)
        } else if (${object_name}_next_concentration_command_idx == 1) {
            byte_to_send = 0x7a; // Command (Read raw co2)
        } else {
            byte_to_send = 0x79; // Command (Read CO2 concentration)
        }
        CALL$(send_byte);

        ${object_name}_next_concentration_command_idx = (${object_name}_next_concentration_command_idx + 1) % 3;
    }

    SUB$(setup_abc) {
        // Send command sequence
        byte_to_send = 0xFF; CALL$(send_byte); // Header
        byte_to_send = 0x01; CALL$(send_byte); // Sensor #1
        byte_to_send = 0x79; CALL$(send_byte); // Command (ON/OFF Self-calibration for zero point)

        if (${use_abc}) {
            byte_to_send = 0xA0;
        } else {
            byte_to_send = 0x00;
        }
        CALL$(send_byte);

        byte_to_send = 0x00;
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);
        CALL$(send_byte);

        if (${use_abc}) {
            byte_to_send = 0xE6;
        } else {
            byte_to_send = 0x86;
        }
        CALL$(send_byte); // CRC
    }

    while(1) {
        // Wait until it's time to send the command sequence
        // This counter will be incremented every 0.1 second in the X_EVERY_DECISECOND above
        ${object_name}_command_countdown = 10; // No need to ask more often than that
        WAIT_UNTIL$(${object_name}_command_countdown == 0, unlikely);

        if (${object_name}_abc_setup_needed && ${object_name}_updated_deciseconds_ago != 255) {
            // Seems like sensor is responding to our commands and ABC (Automatic Baseline Correction) setup is needed
            // We do ${object_name}_abc_setup_needed = 0 when we receive ack-response.
            CALL$(setup_abc);
        } else {
            CALL$(send_read_concentration_command);
        }
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

    METHOD$(u16 get_raw_concentration(), inline) {
        return ${object_name}_raw_concentration;
    }

    METHOD$(u16 get_clamped_concentration(), inline) {
        return ${object_name}_clamped_concentration;
    }

    METHOD$(u16 get_u(), inline) {
        return ${object_name}_u;
    }

    METHOD$(u8 get_s(), inline) {
        return ${object_name}_s;
    }

    METHOD$(u8 get_update_id(), inline) {
        return ${object_name}_update_id;
    }

    METHOD$(u8 get_temperature(), inline) {
        return ${object_name}_temperature;
    }

    METHOD$(u16 get_abc_setups(), inline) {
        return ${object_name}_abc_setups;
    }

    METHOD$(u8 get_updated_deciseconds_ago(), inline) {
        return ${object_name}_updated_deciseconds_ago;
    }
}
