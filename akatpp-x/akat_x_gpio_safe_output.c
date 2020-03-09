// Like X_GPIO_OUTPUT$ but times out if state is not updated witjin state_timeout_deciseconds.
// If timeout happens, then the state of pin is set to 'safe_state'

X_GPIO_OUTPUT$(${object_name}__output, ${pin_name})

X_INIT$(${object_name}__init) {
    ${object_name}__output.set(${safe_state});
}

GLOBAL$() {
    STATIC_VAR$(u8 ${object_name}__updated_ago, initial = 255);
}

OBJECT$(${object_name}) {
    METHOD$(void set(u8 state), inline) {
        ${object_name}__output.set(state);
        ${object_name}__updated_ago = 0;
    }
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    ${object_name}__updated_ago += 1;
    if (!${object_name}__updated_ago) {
        ${object_name}__updated_ago -= 1;
    }
    
    if (${object_name}__updated_ago >= ${state_timeout_deciseconds}) {
        ${object_name}__output.set(${safe_state});
    }
}