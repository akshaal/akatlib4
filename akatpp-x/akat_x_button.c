X_GPIO_INPUT$(${object_name}__input, ${pin_name})

static akat_x_button_state_t ${object_name}__state;

X_INIT$(${object_name}__init) {
    ${object_name}__state.awaiting_key_press = 1;
    ${object_name}__state.checks_left = AKAT_X_BUTTON_CHECKS;
}

FUNCTION$(void ${object_name}__cbk()) {
    ${body}
}

RUNNABLE$(${object_name}__runnable) {
    akat_x_button_handle_pin_state(
        &${object_name}__state,
        ${object_name}__input.is_set(),
        &${object_name}__cbk);
}
