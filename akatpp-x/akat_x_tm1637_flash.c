GLOBAL$() {
    STATIC_VAR$(u8 ${dname}__saved_byte1);
    STATIC_VAR$(u8 ${dname}__saved_byte2);
    STATIC_VAR$(u8 ${dname}__saved_byte3);
    STATIC_VAR$(u8 ${dname}__saved_byte4);
}

X_EVERY_DECISECOND$(${dname}__every_decisecond) {
    FUNCTION$(${dname}__restore1) {
        if (${dname}.get_pos_1() == 0) {
            ${dname}.set_pos_1(${dname}__saved_byte1);
        }
        ${dname}__saved_byte1 = 0;
    }

    if (${condition1}) {
        // TODO
    } else if (${dname}__saved_byte1) {
        ${dname}__restore1();
    }

    // TODO: Do the same for the rest
}
