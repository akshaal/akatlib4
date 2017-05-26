///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

#define AKAT_BCD_GET_L(x)     ((x) & 15)
#define AKAT_BCD_GET_H(x)     (((x) / 16))
#define AKAT_BCD(h, l)        (((h) * 16) + (l))

static AKAT_UNUSED AKAT_CONST AKAT_PURE u8 akat_bcd_inc(u8 bcd);
static AKAT_UNUSED AKAT_CONST AKAT_PURE u8 akat_bcd_dec(u8 bcd);
