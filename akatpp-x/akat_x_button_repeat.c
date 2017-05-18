OBJECT$(${object_name}) {
    ${body}
}

GLOBAL$() {
    STATIC_VAR$(u8 ${object_name}__delay);
}

X_BUTTON_FULL$(${object_name}__button_full, ${pin_name}) {
    METHOD$(void on_press()) {
        ${object_name}__delay = 6;
        ${object_name}.on_press();
    }

    METHOD$(void on_release()) {
        ${object_name}.on_release();
    }
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    if (!${object_name}__button_full.is_awaiting_key_press()) {
        if (${object_name}__delay) {
            ${object_name}__delay--;
        } else {
            ${object_name}.on_repeat();
        }
    }
}
