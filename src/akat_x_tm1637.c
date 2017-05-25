///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

#include <avr/pgmspace.h>

static PROGMEM AKAT_UNUSED u8 const akat_x_tm1637_digits_map[] = {
    AKAT_X_TM1637_C_0,
    AKAT_X_TM1637_C_1,
    AKAT_X_TM1637_C_2,
    AKAT_X_TM1637_C_3,
    AKAT_X_TM1637_C_4,
    AKAT_X_TM1637_C_5,
    AKAT_X_TM1637_C_6,
    AKAT_X_TM1637_C_7,
    AKAT_X_TM1637_C_8,
    AKAT_X_TM1637_C_9
};

static AKAT_UNUSED AKAT_PURE u8 akat_x_tm1637_encode_digit(u8 const digit, u8 const colon) {
    return pgm_read_byte(akat_x_tm1637_digits_map + digit) | (colon ? AKAT_X_TM1637_COLON_MASK : 0);
}
