X_GPIO_INPUT_OUTPUT$(${object_name}__pin, ${pin});

X_INIT$(${object_name}__init) {
    // Safe state - input
    ${object_name}__pin.set_input_mode();
}

OBJECT$(${object_name}) {
    METHOD$(void initialize()) {
    }
}
