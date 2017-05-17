///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

#define AKAT_X_BUTTON_CHECKS 255

typedef void (*akat_x_button_cbk_t)();

typedef struct {
    uint8_t awaiting_key_press;
    uint8_t checks_left;
} akat_x_button_state_t;
