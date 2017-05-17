///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

//
//     a
//    ----
//   |    | b
//  f|    |
//   |-g--|
//   |    | c
//  e|    |
//    ----
//     d        : h
//


//                                    hgfedcba
#define AKAT_X_TM1637_C_0           0b00111111
#define AKAT_X_TM1637_C_1           0b00000110
#define AKAT_X_TM1637_C_2           0b01011011
#define AKAT_X_TM1637_C_3           0b01001111
#define AKAT_X_TM1637_C_4           0b01100110
#define AKAT_X_TM1637_C_5           0b01101101
#define AKAT_X_TM1637_C_6           0b01111101
#define AKAT_X_TM1637_C_7           0b00000111
#define AKAT_X_TM1637_C_8           0b01111111
#define AKAT_X_TM1637_C_9           0b01101111

#define AKAT_X_TM1637_COLON_MASK    0b10000000

static AKAT_PURE u8 akat_x_tm1637_encode_digit(u8 const  digit, u8 const  colon);

typedef enum {AKAT_X_TM1637_POS_1 = 1, AKAT_X_TM1637_POS_2 = 2, AKAT_X_TM1637_POS_3 = 3, AKAT_X_TM1637_POS_4 = 4} akat_x_tm1637_pos_t;
