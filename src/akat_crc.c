///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2019 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

static AKAT_UNUSED AKAT_PURE u8 akat_crc_add(u8 const orig_crc, u8 const orig_byte) {
    u8 crc = orig_crc;
    u8 byte = orig_byte;

    for (u8 j = 0; j < 8; j++) {
        u8 m = (crc ^ byte) & AKAT_ONE;
        crc >>= 1;
        if (m) {
            crc ^= 0x8C;
        }
        byte >>= 1;
    }

    return crc;
}

static AKAT_UNUSED u8 akat_crc_add_bytes(u8 const orig_crc, u8 const *bytes, const u8 size) {
    u8 crc = orig_crc;
    for (u8 i = 0; i < size; i++) {
        crc = akat_crc_add(crc, bytes[i]);
    }
    return crc;
}
