///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

#define AKAT_X_BUTTON_CHECKS 255

typedef void (*akat_x_button_cbk_t)();

typedef enum {AKAT_X_BUTTON_ACTION_NOTHING = 0, AKAT_X_BUTTON_ACTION_KEYPRESS = 1, AKAT_X_BUTTON_ACTION_KEYRELEASE = 2} akat_x_button_action_t;

typedef struct {
    uint8_t awaiting_key_press;
    uint8_t checks_left;
} akat_x_button_state_t;

static AKAT_UNUSED akat_x_button_action_t akat_x_button_handle_pin_state(akat_x_button_state_t * const state, uint8_t const pin_state);
