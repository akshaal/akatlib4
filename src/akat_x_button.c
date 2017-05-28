///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

static AKAT_UNUSED akat_x_button_action_t akat_x_button_handle_pin_state(akat_x_button_state_t * const state, uint8_t const pin_state) {
    akat_x_button_action_t action = AKAT_X_BUTTON_ACTION_NOTHING;

    if (state->awaiting_key_press) {
        AKAT_HOT_CODE; // Usually we are awaiting a key press

        if (pin_state) {
            AKAT_HOT_CODE; // Often pin is high, it means that key is not pressed, reset counter

            state->checks_left = AKAT_X_BUTTON_CHECKS;
        } else {
            AKAT_COLD_CODE; // Sometimes pin is low, it means that key is pressed

            if (state->checks_left) {
                AKAT_HOT_CODE; // Usually we need to do more checks

                state->checks_left--;
            } else {
                AKAT_COLD_CODE; // Sometimes we find out that key is pressed and stable enough

                // Notify about key-press event
                action = AKAT_X_BUTTON_ACTION_KEYPRESS;

                // Wait for key-release event
                state->awaiting_key_press = 0;
                state->checks_left = AKAT_X_BUTTON_CHECKS;
            }
        }
    } else {
        AKAT_COLD_CODE; // Sometimes we are awaiting for key to be released

        if (pin_state) {
            AKAT_COLD_CODE; // After a long keypress, pin can be high, it means that key is released

            if (state->checks_left) {
                AKAT_HOT_CODE; // Often we have to check again to make sure that state is stable, not bouncing

                state->checks_left--;
            } else {
                AKAT_COLD_CODE; // When we checked enough times, wait for key-press event

                // Notify about key-press event
                action = AKAT_X_BUTTON_ACTION_KEYRELEASE;

                // Wait for key press
                state->awaiting_key_press = 1;
                state->checks_left = AKAT_X_BUTTON_CHECKS;
            }
        } else {
            AKAT_HOT_CODE; // Pin is low, it means that key is pressed
            state->checks_left = AKAT_X_BUTTON_CHECKS;
        }
    }

    return action;
}
