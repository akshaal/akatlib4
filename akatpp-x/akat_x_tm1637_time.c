OBJECT$(${oname}) {
    METHOD$(void __update_hh(u8 const colon)) {
        tm1637.set_digit_pos_1(${tname}.get_hours_h(), AKAT_FALSE);
        tm1637.set_digit_pos_2(${tname}.get_hours_l(), colon);
    }

    METHOD$(void __update_mm(akat_x_tm1637_pos_t const pos, u8 const colon)) {
        tm1637.set_digit(pos, ${tname}.get_minutes_h(), AKAT_FALSE);
        tm1637.set_digit(pos + 1, ${tname}.get_minutes_l(), colon);
    }

    METHOD$(void __update_ss(akat_x_tm1637_pos_t const pos, u8 const colon)) {
        tm1637.set_digit(pos, ${tname}.get_seconds_h(), AKAT_FALSE);
        tm1637.set_digit(pos + 1, ${tname}.get_seconds_l(), colon);
    }

    METHOD$(void update(akat_x_timestamp_level_t const level)) {
        if (${condition}) {
            if (${tname}.get_hours_h() != 0 || ${tname}.get_hours_l() != 0) {
                // Here we know that HH != 0, so we only update HH:MM
                if (level != AKAT_X_TIMESTAMP_LEVEL_DECISECOND) {
                    ${oname}.__update_hh(1);
                    ${oname}.__update_mm(AKAT_X_TM1637_POS_3, AKAT_FALSE);
                }
            } else if (${tname}.get_minutes_h() != 0 || ${tname}.get_minutes_l() != 0) {
                // Here we know that HH == 0, but MM != 0, so we only update MM:SS
                if (level != AKAT_X_TIMESTAMP_LEVEL_DECISECOND) {
                    ${oname}.__update_mm(AKAT_X_TM1637_POS_1, 1);
                    ${oname}.__update_ss(AKAT_X_TM1637_POS_3, AKAT_FALSE);
                }
            } else {
                // Here we know that HH == 0, but MM == 0, so we only update SS  d
                ${oname}.__update_ss(AKAT_X_TM1637_POS_1, 1);

                if (level == AKAT_X_TIMESTAMP_LEVEL_DECISECOND) {
                    tm1637.set(AKAT_X_TM1637_POS_3, AKAT_FALSE);
                    tm1637.set_digit_pos_4(${tname}.get_deciseconds(), AKAT_FALSE);
                }
            }
        }
    }
}

X_TIMESTAMP_CALLBACKS$(${tname}) {
    METHOD$(void on_new(akat_x_timestamp_level_t level), inline) {
        ${oname}.update(level);
    }
}
