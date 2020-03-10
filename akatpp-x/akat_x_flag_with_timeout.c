GLOBAL$() {
    STATIC_VAR$(u8 ${oname}__v, initial = 0);
    STATIC_VAR$(u8 ${oname}__countdown, initial = 0);
}

OBJECT$(${oname}) {
    METHOD$(void set(u8 state), inline) {
        ${oname}__v = state;
        ${oname}__countdown = ${timeout};
    }

    METHOD$(u8 is_set(), inline) {
        return ${oname}__v;
    }
}

X_EVERY_${unit}$(${oname}__reset_checker) {
    if (${oname}__v) {
        ${oname}__countdown -= 1;
        if (!${oname}__countdown) {
            ${oname}__v = 0;
        }
    }
}