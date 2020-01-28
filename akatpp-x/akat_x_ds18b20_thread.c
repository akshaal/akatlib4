// Performs temperature measurements for sensors registered with X_DS18S20$ macro.
// We measure temperature for several sensors at the same time without blocking other threads as much as possible

GLOBAL$() {
    STATIC_VAR$(u8 ds18b20__tconv_countdown);
}

FUNCTION$(void ds18b20_ticker()) {
    // We are waiting for temperature conversion and decrement the counter every 0.1 second
    if (ds18b20__tconv_countdown) {
        ds18b20__tconv_countdown -= AKAT_ONE;
    }
}

THREAD$(ds18b20_thread) {
    // ---- All variable in the thread must be static (green threads requirement)
    STATIC_VAR$(u8 byte_to_send);
    STATIC_VAR$(u8 command_to_send);
    STATIC_VAR$(u8 receive_idx);

    // ---- Functions
    FUNCTION$(u8 has_connected_sensors(), inline) {
        % for object_name in object_names:
        if (${object_name}__connected) {
            return 1;
        }
        % endfor
        return 0;
    }

    FUNCTION$(void write_bit(const u8 bit)) {
        // 'bit' can be either zero or non zero. Non zero bit value is treated as 1.

        % for object_name in object_names:
        if (${object_name}__connected) {
            ${object_name}__pin.set_output_mode();
            ${object_name}__pin.set(0);
        }
        % endfor

        if (bit) {
            // Wait for edge to raise and slave to detect it
            akat_delay_us(4);

            // Set pin to 1 such that slave can sample the value we transmit
            % for object_name in object_names:
            if (${object_name}__connected) {
                ${object_name}__pin.set_input_mode();
            }
            % endfor
        }

        akat_delay_us(60);

        // Recovery, the pin will be pulled up by the external/internal pull-up resistor
        % for object_name in object_names:
        if (${object_name}__connected) {
            ${object_name}__pin.set_input_mode();
        }
        % endfor
        akat_delay_us(10);
    }

    FUNCTION$(void read_bit(u8 mask)) {
        // Returns either 0 or non zero (doesn't mean '1'!)

        // Indicate that we want to read a bit
        % for object_name in object_names:
        if (${object_name}__connected) {
            ${object_name}__pin.set_output_mode();
            ${object_name}__pin.set(0);
        }
        % endfor

        // Allow slave to detect the falling edge on the pin
        akat_delay_us(4);

        // Release the line and let slave set it to the value we will read after the delay
        % for object_name in object_names:
        if (${object_name}__connected) {
            ${object_name}__pin.set_input_mode();
        }
        % endfor

        akat_delay_us(9);

        % for object_name in object_names:
        if (${object_name}__connected) {
            if (${object_name}__pin.is_set()) {
                ${object_name}__received_byte += mask;
            }
        }
        % endfor

        // Total duration of reading slot must be at least 60
        akat_delay_us(55);
    }

    // ---- Subroutines can yield unlike functions

    // Sends byte from 'byte_to_send', initialization is supposed to be done
    SUB$(send_byte) {
        // LSB (Least significant bit) first order
        write_bit(byte_to_send & H(0)); YIELD$();
        write_bit(byte_to_send & H(1)); YIELD$();
        write_bit(byte_to_send & H(2)); YIELD$();
        write_bit(byte_to_send & H(3)); YIELD$();
        write_bit(byte_to_send & H(4)); YIELD$();
        write_bit(byte_to_send & H(5)); YIELD$();
        write_bit(byte_to_send & H(6)); YIELD$();
        write_bit(byte_to_send & H(7));
    }

    // Receive byte into 'received_byte'
    SUB$(receive_byte) {
        // LSB (Least significant bit) first order
        % for object_name in object_names:
        ${object_name}__received_byte = 0;
        % endfor

        read_bit(H(0)); YIELD$();
        read_bit(H(1)); YIELD$();
        read_bit(H(2)); YIELD$();
        read_bit(H(3)); YIELD$();
        read_bit(H(4)); YIELD$();
        read_bit(H(5)); YIELD$();
        read_bit(H(6)); YIELD$();
        read_bit(H(7));

        % for object_name in object_names:
        ${object_name}__scratchpad[receive_idx] = ${object_name}__received_byte;
        % endfor
    }

    // Sends command from 'command_to_send'
    // Does nothing if ${object_name}__connected is FALSE.
    // Sets ${object_name}__connected to FALSE if presence pulse is missing!
    SUB$(send_command) {
        // Starts communication:
        //   * send reset pulse
        //   * wait for presence response

        if (has_connected_sensors()) {
            // Reset pulse: 480 ... 960 us in low state
            % for object_name in object_names:
            if (${object_name}__connected) {
                ${object_name}__pin.set_output_mode();
                ${object_name}__pin.set(0);
            }
            % endfor

            akat_delay_us(600);

            // Slave awaits 15 ... 60 us
            // and then sinks pin to ground for 60 ... 240 us
            % for object_name in object_names:
            if (${object_name}__connected) {
                ${object_name}__pin.set_input_mode();
            }
            % endfor

            akat_delay_us(80);

            % for object_name in object_names:
            if (${object_name}__connected) {
                ${object_name}__connected = !${object_name}__pin.is_set();

                if (!${object_name}__connected) {
                    ${object_name}__disconnects += AKAT_ONE;
                    if (!${object_name}__disconnects) {
                        // We can't go beyond 255
                        ${object_name}__disconnects -= AKAT_ONE;
                    }
                }
            }
            % endfor

            YIELD$();

            // We must wait for present pulse for minimum of 480 us
            // We have already waited for 80 us in start_initialize + some time in 'yield'
            akat_delay_us(410);

            if (has_connected_sensors()) {
                YIELD$();

                // Skip ROM
                byte_to_send = 0xCC; CALL$(send_byte);
                YIELD$();

                // Send the command
                byte_to_send = command_to_send; CALL$(send_byte);
            }
        }
    }

    // - - - - - - - - - - -
    // Main loop in thread (thread will yield on calls to YIELD$ or WAIT_UNTIL$)
    while(1) {
        // Everything is connected until proven otherwise by presence pulse
        % for object_name in object_names:
        ${object_name}__connected = 1;
        % endfor

        // Start temperature conversion
        command_to_send = 0x44; CALL$(send_command);
        if (has_connected_sensors()) {
            // Wait for conversion to end. It takes 750ms to convert, but we "wait" for approx. 900ms ... 1 second
            // tconv_countdown will be decremented every 1/10 second.
            ds18b20__tconv_countdown = 10;
            WAIT_UNTIL$(ds18b20__tconv_countdown == 0, unlikely); // This will YIELD

            // Read scratchpad (temperature)
            command_to_send = 0xBE; CALL$(send_command);
            if (has_connected_sensors()) {
                % for i in range(9):
                receive_idx = ${i}; CALL$(receive_byte);
                % endfor

                // Check CRC
                % for object_name in object_names:
                if (${object_name}__connected) {
                    YIELD$();

                    // Check CRC
                    u8 crc = akat_crc_add_bytes(0, ${object_name}__scratchpad, 8);

                    if (${object_name}__scratchpad[8] == crc) {
                        // CRC is OK
                        ${object_name}__updated_deciseconds_ago = 0;
                        ${object_name}__temperature_lsb = ${object_name}__scratchpad[0];
                        ${object_name}__temperature_msb = ${object_name}__scratchpad[1];
                    } else {
                        // CRC is incorrect
                        ${object_name}__crc_errors += AKAT_ONE;
                        if (!${object_name}__crc_errors) {
                            // We can't go beyond 255
                            ${object_name}__crc_errors -= AKAT_ONE;
                        }
                    }
                }
                % endfor
            }
        }

        YIELD$();
    }
}
