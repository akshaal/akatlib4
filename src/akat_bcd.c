///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

static AKAT_UNUSED AKAT_CONST AKAT_PURE u8 akat_bcd_inc(u8 bcd) {
    if (AKAT_BCD_GET_L(bcd) == 9) {
        bcd += 16 - 9;
    } else {
        bcd++;
    }

    return bcd;
}

static AKAT_UNUSED AKAT_CONST AKAT_PURE u8 akat_bcd_dec(u8 bcd) {
    if (AKAT_BCD_GET_L(bcd)) {
        bcd--;
    } else {
        bcd += -16 + 9;
    }

    return bcd;
}
