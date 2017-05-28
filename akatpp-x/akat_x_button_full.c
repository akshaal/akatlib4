X_GPIO_INPUT$(${object_name}__input, ${pin_name})

static akat_x_button_state_t ${object_name}__state;

X_INIT$(${object_name}__init) {
    ${object_name}__state.awaiting_key_press = AKAT_TRUE;
    ${object_name}__state.checks_left = AKAT_X_BUTTON_CHECKS;
}

OBJECT$(${object_name}) {
    METHOD$(u8 is_awaiting_key_press(), inline) {
        return ${object_name}__state.awaiting_key_press;
    }

    ${body}
}

RUNNABLE$(${object_name}__runnable) {
    akat_x_button_action_t const rc = akat_x_button_handle_pin_state(&${object_name}__state, ${object_name}__input.is_set());
    if (rc == AKAT_X_BUTTON_ACTION_KEYPRESS) {
        ${object_name}.on_press();
    } else if (rc == AKAT_X_BUTTON_ACTION_KEYRELEASE) {
        ${object_name}.on_release();
    }
}
