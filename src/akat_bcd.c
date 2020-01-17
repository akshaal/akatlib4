///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

FUNCTION$(u8 akat_bcd_inc(u8 bcd), pure, unused) {
    if (AKAT_BCD_GET_L(bcd) == 9) {
        bcd += 16 - 9;
    } else {
        bcd++;
    }

    return bcd;
}

FUNCTION$(u8 akat_bcd_dec(u8 bcd), pure, unused) {
    if (AKAT_BCD_GET_L(bcd)) {
        bcd--;
    } else {
        bcd += -16 + 9;
    }

    return bcd;
}
