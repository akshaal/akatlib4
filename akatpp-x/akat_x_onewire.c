// Very low level implementation of one wire protocol.
// Is supposed to be used by other modules like X_DS18B20.

// Typical flow in a thread:
//   1. call start_initialize_ret_0_on_success
//   2. if 0 then yield and continue to 4
//   3. if not 0 then yield, call finish_initialize, yield and then do something else, don't continue
//   4. call finish_initialize and yield
//   5. write bit, yield, write bit, yield etc read_bit yield, read bit yield
// see X_DS18B20.c for example of how this is used.

X_GPIO_INPUT_OUTPUT$(${object_name}__pin, ${pin});

X_INIT$(${object_name}__init) {
    // Safe state - input
    ${object_name}__pin.set_input_mode();
}

// Timing are taken from DS18B20 spec..
OBJECT$(${object_name}) {
    METHOD$(u8 start_initialize_ret_0_on_success()) {
        // Starts communication:
        //   * send reset pulse
        //   * wait for presence response
        // Returns zero if a slave device is present.

        // Reset pulse: 480 ... 960 us in low state
        ${object_name}__pin.set_output_mode();
        ${object_name}__pin.set(0);

        akat_delay_us(600);

        // Slave waits 15 ... 60 us
        // and then sinks pin to ground for 60 ... 240 us
        ${object_name}__pin.set_input_mode();
        akat_delay_us(80);

        return ${object_name}__pin.is_set();
    }

    METHOD$(void finish_initialize()) {
        // We must wait for present pulse for minimum of 480 us
        // We have already waited for 80 us in start_initialize + some time in 'yield'
        akat_delay_us(410);
    }

    METHOD$(void write_bit(const u8 bit)) {
        // 'bit' can be either zero or non zero. Non zero bit value is treated as 1.

        ${object_name}__pin.set_output_mode();
        ${object_name}__pin.set(0);

        if (bit) {
            // Wait for edge to raise and slave to detect it
            akat_delay_us(6);

            // Set pin to 1 such that slave can sample the value we transmit
            ${object_name}__pin.set_input_mode();
        }

        akat_delay_us(60);

        // Recovery, the pin will be pulled up by the external/internal pull-up resistor
        ${object_name}__pin.set_input_mode();
        akat_delay_us(10);
    }

    METHOD$(u8 read_bit()) {
        // Returns either 0 or non zero (doesn't mean '1'!)

        // Indicate that we want to read a bit
        ${object_name}__pin.set_output_mode();
        ${object_name}__pin.set(0);

        // Allow slave to detect the falling edge on the pin
        akat_delay_us(6);

        // Release the line and let slave set it to the value we will read after the delay
        ${object_name}__pin.set_input_mode();
        akat_delay_us(9);

        const u8 result = ${object_name}__pin.is_set();

        // Total length of reading slot must be at least 1
        akat_delay_us(55);

        return result;
    }
}
