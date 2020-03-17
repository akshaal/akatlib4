OBJECT$(${object_name}) {
    ${body}
}

GLOBAL$() {
    STATIC_VAR$(u8 ${object_name}__delay);
}

X_BUTTON_FULL$(${object_name}__button_full, ${pin_name}) {
    METHOD$(void on_press()) {
        ${object_name}__delay = ${timeout_deciseconds};
    }

    METHOD$(void on_release()) {
        if (${object_name}__delay) {
            ${object_name}.on_press();
        }

        ${object_name}.on_release();
    }
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    if (!${object_name}__button_full.is_awaiting_key_press()) {
        if (${object_name}__delay) {
            ${object_name}__delay--;

            if (${object_name}__delay == 0) {
                 ${object_name}.on_long_press();
            }
        }
    }
}
