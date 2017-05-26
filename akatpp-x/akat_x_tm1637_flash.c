GLOBAL$() {
    STATIC_VAR$(u8 ${oname}__started);
    STATIC_VAR$(u8 ${oname}__restore_now);
    STATIC_VAR$(u8 ${oname}__saved_byte1);
    STATIC_VAR$(u8 ${oname}__saved_byte2);
    STATIC_VAR$(u8 ${oname}__saved_byte3);
    STATIC_VAR$(u8 ${oname}__saved_byte4);
}

FUNCTION$(void ${oname}__restore1()) {
    if (${dname}.get_pos_1() == 0) {
        ${dname}.set_pos_1(${oname}__saved_byte1);
    }
}

FUNCTION$(void ${oname}__restore2()) {
    if (${dname}.get_pos_2() == 0) {
        ${dname}.set_pos_2(${oname}__saved_byte2);
    }
}

FUNCTION$(void ${oname}__restore3()) {
    if (${dname}.get_pos_3() == 0) {
        ${dname}.set_pos_3(${oname}__saved_byte3);
    }
}

FUNCTION$(void ${oname}__restore4()) {
    if (${dname}.get_pos_4() == 0) {
        ${dname}.set_pos_4(${oname}__saved_byte4);
    }
}

FUNCTION$(void ${oname}__save1()) {
    ${oname}__saved_byte1 = ${dname}.get_pos_1();
}

FUNCTION$(void ${oname}__save2()) {
    ${oname}__saved_byte2 = ${dname}.get_pos_2();
}

FUNCTION$(void ${oname}__save3()) {
    ${oname}__saved_byte3 = ${dname}.get_pos_3();
}

FUNCTION$(void ${oname}__save4()) {
    ${oname}__saved_byte4 = ${dname}.get_pos_4();
}


OBJECT$(${oname}) {
    METHOD$(void start_pos_1()) {
        ${oname}__started |= 1 << 0;
        ${oname}__save1();
    }

    METHOD$(void start_pos_2()) {
        ${oname}__started |= 1 << 1;
        ${oname}__save2();
    }

    METHOD$(void start_pos_3()) {
        ${oname}__started |= 1 << 2;
        ${oname}__save3();
    }

    METHOD$(void start_pos_4()) {
        ${oname}__started |= 1 << 3;
        ${oname}__save4();
    }



    METHOD$(void stop_pos_1()) {
        ${oname}__started &= ~(1 << 0);
        ${oname}__restore1();
    }

    METHOD$(void stop_pos_2()) {
        ${oname}__started &= ~(1 << 1);
        ${oname}__restore2();
    }

    METHOD$(void stop_pos_3()) {
        ${oname}__started &= ~(1 << 2);
        ${oname}__restore3();
    }

    METHOD$(void stop_pos_4()) {
        ${oname}__started &= ~(1 << 3);
        ${oname}__restore4();
    }

    METHOD$(void stop_all()) {
        ${oname}.stop_pos_1();
        ${oname}.stop_pos_2();
        ${oname}.stop_pos_3();
        ${oname}.stop_pos_4();
    }

    METHOD$(void start_all()) {
        ${oname}.start_pos_1();
        ${oname}.start_pos_2();
        ${oname}.start_pos_3();
        ${oname}.start_pos_4();
    }
}

X_EVERY_DECISECOND$(${oname}__every_decisecond) {
    if (!${oname}__started) {
        return;
    }

    if (${oname}__started & (1 << 0)) {
        if (${oname}__restore_now) {
            ${oname}__restore1();
        } else {
            ${oname}__save1();
            ${dname}.set_pos_1(0);
        }
    }

    if (${oname}__started & (1 << 1)) {
        if (${oname}__restore_now) {
            ${oname}__restore2();
        } else {
            ${oname}__save2();
            ${dname}.set_pos_2(0);
        }
    }

    if (${oname}__started & (1 << 2)) {
        if (${oname}__restore_now) {
            ${oname}__restore3();
        } else {
            ${oname}__save3();
            ${dname}.set_pos_3(0);
        }
    }

    if (${oname}__started & (1 << 3)) {
        if (${oname}__restore_now) {
            ${oname}__restore4();
        } else {
            ${oname}__save4();
            ${dname}.set_pos_4(0);
        }
    }

    ${oname}__restore_now = ~${oname}__restore_now;
}
