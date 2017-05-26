GLOBAL$() {
    STATIC_VAR$(u8 ${oname}__started[4], initial = {0, 0, 0, 0});
    STATIC_VAR$(u8 ${oname}__saved_byte[4], initial = {0, 0, 0, 0});
    STATIC_VAR$(u8 ${oname}__restore_now);
}

FUNCTION$(void ${oname}__restore(akat_x_tm1637_pos_t const pos)) {
    if (${dname}.get(pos) == 0) {
        ${dname}.set(pos, ${oname}__saved_byte[pos]);
    }
}

FUNCTION$(void ${oname}__save(akat_x_tm1637_pos_t const pos)) {
    ${oname}__saved_byte[pos] = ${dname}.get(pos);
}

OBJECT$(${oname}) {
    METHOD$(void start(akat_x_tm1637_pos_t const pos)) {
        ${oname}__started[pos] = AKAT_ONE;
        ${oname}__save(pos);
    }

    METHOD$(void stop(akat_x_tm1637_pos_t const pos)) {
        ${oname}__started[pos] = 0;
        ${oname}__restore(pos);
    }

    METHOD$(void stop_pos_1()) { ${oname}.stop(AKAT_X_TM1637_POS_1); }
    METHOD$(void stop_pos_2()) { ${oname}.stop(AKAT_X_TM1637_POS_2); }
    METHOD$(void stop_pos_3()) { ${oname}.stop(AKAT_X_TM1637_POS_3); }
    METHOD$(void stop_pos_4()) { ${oname}.stop(AKAT_X_TM1637_POS_4); }

    METHOD$(void start_pos_1()) { ${oname}.start(AKAT_X_TM1637_POS_1); }
    METHOD$(void start_pos_2()) { ${oname}.start(AKAT_X_TM1637_POS_2); }
    METHOD$(void start_pos_3()) { ${oname}.start(AKAT_X_TM1637_POS_3); }
    METHOD$(void start_pos_4()) { ${oname}.start(AKAT_X_TM1637_POS_4); }

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
    for (u8 pos = 0; pos <= AKAT_X_TM1637_POS_4; pos++) {
        if (${oname}__started[pos]) {
            if (${oname}__restore_now) {
                ${oname}__restore(pos);
            } else {
                ${oname}__save(pos);
                ${dname}.set(pos, 0);
            }
        }
    }

    ${oname}__restore_now = ~${oname}__restore_now;
}
