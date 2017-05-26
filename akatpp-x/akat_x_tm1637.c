X_GPIO_OUTPUT$(${object_name}__clk, ${clk_pin});
X_GPIO_INPUT_OUTPUT$(${object_name}__dio, ${dio_pin});

// Static variable for commands
GLOBAL$() {
    STATIC_VAR$(u8 ${object_name}__dirty, initial = 1);
    STATIC_VAR$(u8 ${object_name}__byte[4], initial = {0, 0, 0, 0});
}

// ==================================================================================================================
// ==================================================================================================================
// ==================================================================================================================
//
// Main thread for TM1637 which handles requested commands
THREAD$(${object_name}__thread) {
    // -----------------------------------------------------------------------------------------------------
    OBJECT$(f) {
        METHOD$(void delay()) {
            akat_delay_us(${delay_us});
        }

        METHOD$(void set_dio(u8 state), inline) {
            ${object_name}__dio.set(state);
        }

        METHOD$(void set_dio_input_mode(), inline) {
            ${object_name}__dio.set_input_mode();
        }

        METHOD$(void set_dio_output_mode(), inline) {
            ${object_name}__dio.set_output_mode();
        }

        METHOD$(void set_clk(u8 state), inline) {
            ${object_name}__clk.set(state);
        }

        METHOD$(void start()) {
            // Start communication
            // When CLK is a high level and DIO changes from high to low level, data input starts.
            f.set_dio(1);
            f.set_clk(1);
            f.delay();
            f.set_dio(0);
        }

        METHOD$(void end()) {
            // End communication
            // When CLK is a high level and DIO changes from low level to high level, data input ends.
            f.set_clk(0);
            f.delay();
            f.set_dio(0);
            f.delay();
            f.set_clk(1);
            f.delay();
            f.set_dio(1);
        }

        METHOD$(void write_byte(u8 byte_for_write)) {
            // In data transmit mode: data should change it is value when clock pin is low.
            // That's why we lower CLK pin and then change DIO pin value.
            // In other words: TM1637 samples DIO pin on Front edge
            for (u8 bit_idx = 0; bit_idx < 8; bit_idx++) {
                f.set_clk(0);
                f.set_dio(byte_for_write & 1);
                f.delay();
                f.set_clk(1);
                f.delay();

                byte_for_write >>= 1;
            }

            // ACK
            f.set_clk(0);
            f.set_dio_input_mode();
            f.delay();

            // ... read pin state but we don't care

            f.delay();

            f.set_clk(1);
            f.delay();

            f.set_clk(0);
            f.set_dio_output_mode();
        }
    };

    // -----------------------------------------------------------------------------------------------------
    // Initialize (turn on / set brightness)

    f.set_dio(1);
    f.set_dio_output_mode();
    f.set_clk(1);

    f.start();
    f.write_byte(0x88); // Where 0x80 is command and 0x08 is <<full brightness>>
    f.end();

    // ---------------------------------------------------------------------
    // Main loop
    while(1) {
        // Wait until there is an update
        WAIT_UNTIL$(${object_name}__dirty, unlikely);

        // Reset flag immediately
        ${object_name}__dirty = 0;

        // .----------------------------------
        // Data command
        // It is byte 0x40.
        // IT is actually bits like this B7=0 B6=1 B5=0 B4=0 B3=m B2=a B1=d B0=0)
        // where B7  is 0
        //       B6  is 1
        //       B5  is 0
        //       b4  is 0
        //       B3  is mode (0 - normal, 1 - test)
        //       B2  is address (0 - automatic, 1 - fixed)
        //       B1  is direction (0 - write display, 1 - read keys)
        //       B0  is 0

        f.start();
        YIELD$();

        f.write_byte(0x40);
        YIELD$();

        f.end();
        YIELD$();

        // -----------------------------------------------
        // Address command
        // It is byte 0xC0: Two high bits are always 1, the rest gives register address, in our case register address are 0
        // So it is: 1100 0000 == C0

        f.start();
        YIELD$();

        f.write_byte(0xC0);
        YIELD$();

        f.write_byte(${object_name}__byte[AKAT_X_TM1637_POS_1]); YIELD$();
        f.write_byte(${object_name}__byte[AKAT_X_TM1637_POS_2]); YIELD$();
        f.write_byte(${object_name}__byte[AKAT_X_TM1637_POS_3]); YIELD$();
        f.write_byte(${object_name}__byte[AKAT_X_TM1637_POS_4]); YIELD$();

        f.end();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface

OBJECT$(${object_name}) {
    METHOD$(void set(akat_x_tm1637_pos_t pos, u8 const v)) {
        ${object_name}__dirty = AKAT_TRUE;
        ${object_name}__byte[pos] = v;
    }

    METHOD$(u8 get(akat_x_tm1637_pos_t pos)) {
        return ${object_name}__byte[pos];
    }

    METHOD$(u8 get_pos_1()) { return ${object_name}.get(AKAT_X_TM1637_POS_1); }
    METHOD$(u8 get_pos_2()) { return ${object_name}.get(AKAT_X_TM1637_POS_2); }
    METHOD$(u8 get_pos_3()) { return ${object_name}.get(AKAT_X_TM1637_POS_3); }
    METHOD$(u8 get_pos_4()) { return ${object_name}.get(AKAT_X_TM1637_POS_4); }

    METHOD$(void set_pos_1(u8 const v)) {
        ${object_name}.set(AKAT_X_TM1637_POS_1, v);
    }

    METHOD$(void set_pos_2(u8 const v)) {
        ${object_name}.set(AKAT_X_TM1637_POS_2, v);
    }

    METHOD$(void set_pos_3(u8 const v)) {
        ${object_name}.set(AKAT_X_TM1637_POS_3, v);
    }

    METHOD$(void set_pos_4(u8 const v)) {
        ${object_name}.set(AKAT_X_TM1637_POS_4, v);
    }

    METHOD$(void set_digit(akat_x_tm1637_pos_t pos, u8 const digit, u8 const colon)) {
        ${object_name}.set(pos, akat_x_tm1637_encode_digit(digit, colon));
    }

    METHOD$(void set_digit_pos_1(u8 const v, u8 const colon)) {
        ${object_name}.set_digit(AKAT_X_TM1637_POS_1, v, colon);
    }

    METHOD$(void set_digit_pos_2(u8 const v, u8 const colon)) {
        ${object_name}.set_digit(AKAT_X_TM1637_POS_2, v, colon);
    }

    METHOD$(void set_digit_pos_3(u8 const v, u8 const colon)) {
        ${object_name}.set_digit(AKAT_X_TM1637_POS_3, v, colon);
    }

    METHOD$(void set_digit_pos_4(u8 const v, u8 const colon)) {
        ${object_name}.set_digit(AKAT_X_TM1637_POS_4, v, colon);
    }
};
