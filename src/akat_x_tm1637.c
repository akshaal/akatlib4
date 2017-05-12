///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////


static AKAT_UNUSED AKAT_PURE u8 akat_x_tm1637_encode_digit(u8 const digit, u8 const colon) {
    return (digit == 0 ? AKAT_X_TM1637_C_0 :
            digit == 1 ? AKAT_X_TM1637_C_1 :
            digit == 2 ? AKAT_X_TM1637_C_2 :
            digit == 3 ? AKAT_X_TM1637_C_3 :
            digit == 4 ? AKAT_X_TM1637_C_4 :
            digit == 5 ? AKAT_X_TM1637_C_5 :
            digit == 6 ? AKAT_X_TM1637_C_6 :
            digit == 7 ? AKAT_X_TM1637_C_7 :
            digit == 8 ? AKAT_X_TM1637_C_8 : AKAT_X_TM1637_C_9) | (colon ? AKAT_X_TM1637_COLON_MASK : 0);
}
