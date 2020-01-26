// Read temperature from DS18B20.
// DS18B20 is supposed to be connected to the given port and must be properly powered.
// (parasitic powering mode is not supported/tested).
// DS18B20 must be the only device connected to the pin because we use SKIP-ROM command.

X_ONEWIRE$(${object_name}__onewire, ${pin});

// Static variable for communication between our thread and other parts of code
GLOBAL$() {
    // TODO: Add freshness which is 255 by default (maximum value, spoiled data)
    STATIC_VAR$(u8 ${object_name}__tconv_countdown, initial = 0);
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    // We are waiting for temperature conversion and decrement the counter every 0.1 second
    if (${object_name}__tconv_countdown) {
        ${object_name}__tconv_countdown -= 1;
    }
}

THREAD$(${object_name}__thread) {
    // ---- All variable in the thread must be static (green threads requirement)
    STATIC_VAR$(u8 byte_to_send);
    STATIC_VAR$(u8 received_byte);
    STATIC_VAR$(u8 command_to_send_and_is_success_result);

    // ---- Subroutines can yield unlike functions

    // Sends byte from 'byte_to_send', initialization is supposed to be done
    SUB$(send_byte) {
        // LSB (Least significant bit) first order
        ${object_name}__onewire.write_bit(byte_to_send & H(0)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(1)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(2)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(3)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(4)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(5)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(6)); YIELD$();
        ${object_name}__onewire.write_bit(byte_to_send & H(7));
    }

    // Receive byte into 'received_byte'
    SUB$(receive_byte) {
        // LSB (Least significant bit) first order
        received_byte = ${object_name}__onewire.read_bit() ? H(0) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(1) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(2) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(3) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(4) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(5) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(6) : 0; YIELD$();
        received_byte |= ${object_name}__onewire.read_bit() ? H(7) : 0;
    }

    // Sends command from 'command_to_send_and_is_success_result'
    // If fails, then command_to_send_and_is_success_result is zero on return from the subroutine
    SUB$(send_command) {
        // Start communication... Both branches looks a bit identical by design.
        if (${object_name}__onewire.start_initialize_ret_0_on_success()) {
            // Device not present
            YIELD$();
            ${object_name}__onewire.finish_initialize();

            // Failure
            command_to_send_and_is_success_result = 0;
        } else {
            // Device is present.
            YIELD$();
            ${object_name}__onewire.finish_initialize();
            YIELD$();

            // Skip ROM
            byte_to_send = 0xCC; CALL$(send_byte);
            YIELD$();

            // Send the command
            byte_to_send = command_to_send_and_is_success_result; CALL$(send_byte);

            // Success
            command_to_send_and_is_success_result = AKAT_ONE;
        }
    }

    // - - - - - - - - - - -
    // Main loop in thread (thread will yield on calls to YIELD$ or WAIT_UNTIL$)
    while(1) {
        // Start temperature conversion
        command_to_send_and_is_success_result = 0x44; CALL$(send_command);
        if (command_to_send_and_is_success_result) {
            // Wait for conversion to end. It takes 750ms to convert, but we "wait" for approx. 900ms ... 1 second
            // tconv_countdown will be decremented every 1/10 second.
            ${object_name}__tconv_countdown = 10;
            WAIT_UNTIL$(${object_name}__tconv_countdown == 0, unlikely); // This will YIELD

            // Read scratchpad (temperature)
            command_to_send_and_is_success_result = 0xBE; CALL$(send_command);
            if (command_to_send_and_is_success_result) {
                // TODO: read scratchpad... 9 bytes
                // TODO: check crc
                // TODO: Update freshness
                CALL$(receive_byte);
            }
        }
    }
}

OBJECT$(${object_name}) {

}
