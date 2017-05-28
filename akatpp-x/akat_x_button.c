X_GPIO_INPUT$(${object_name}__input, ${pin_name})

static akat_x_button_state_t ${object_name}__state;

X_INIT$(${object_name}__init) {
    ${object_name}__state.awaiting_key_press = AKAT_TRUE;
    ${object_name}__state.checks_left = AKAT_X_BUTTON_CHECKS;
}

FUNCTION$(void ${object_name}__cbk()) {
    ${body}
}

RUNNABLE$(${object_name}__runnable) {
    akat_x_button_action_t const rc = akat_x_button_handle_pin_state(&${object_name}__state, ${object_name}__input.is_set());
    if (rc == AKAT_X_BUTTON_ACTION_KEYPRESS) {
        ${object_name}__cbk();
    }
}
