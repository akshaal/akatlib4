///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2019 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

static AKAT_PURE u8 akat_crc_add(u8 const crc, u8 const byte);
static u8 akat_crc_add_bytes(u8 const crc, u8 const *bytes, const u8 size);
