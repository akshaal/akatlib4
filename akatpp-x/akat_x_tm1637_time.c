OBJECT$(${oname}) {
    METHOD$(void __update_hh(akat_x_timestamp_level_t level)) {
        if (level == AKAT_X_TIMESTAMP_LEVEL_HOUR_H) {
            tm1637.set_digit_pos_1(${tname}.get_hours_h(), 0);
        }

        if (level == AKAT_X_TIMESTAMP_LEVEL_HOUR_L) {
            tm1637.set_digit_pos_2(${tname}.get_hours_l(), 0);
        }
    }

    METHOD$(void __update_mm(akat_x_timestamp_level_t level, akat_x_tm1637_pos_t pos)) {
        if (level == AKAT_X_TIMESTAMP_LEVEL_MINUTE_H) {
            tm1637.set_digit(pos, ${tname}.get_minutes_h(), 0);
        }

        if (level == AKAT_X_TIMESTAMP_LEVEL_MINUTE_L) {
            tm1637.set_digit(pos + 1, ${tname}.get_minutes_l(), 0);
        }
    }

    METHOD$(void __update_ss(akat_x_timestamp_level_t level, akat_x_tm1637_pos_t pos)) {
        if (level == AKAT_X_TIMESTAMP_LEVEL_SECOND_H) {
            tm1637.set_digit(pos, ${tname}.get_seconds_h(), 0);
        }

        if (level == AKAT_X_TIMESTAMP_LEVEL_SECOND_L) {
            tm1637.set_digit(pos + 1, ${tname}.get_seconds_l(), 0);
        }
    }

    METHOD$(void update(akat_x_timestamp_level_t level)) {
        if (${condition}) {
            if (${tname}.get_hours_h() != 0 || ${tname}.get_hours_l() != 0) {
                // Here we know that HH != 0, so we only update HH:MM
                ${oname}.__update_hh(level);
                ${oname}.__update_mm(level, AKAT_X_TM1637_POS_3);
            } else if (${tname}.get_minutes_h() != 0 || ${tname}.get_minutes_l() != 0) {
                // Here we know that HH == 0, but MM != 0, so we only update MM:SS
                ${oname}.__update_mm(level, AKAT_X_TM1637_POS_1);
                ${oname}.__update_ss(level, AKAT_X_TM1637_POS_3);
            } else {
                // Here we know that HH == 0, but MM == 0, so we only update SS  d
                ${oname}.__update_ss(level, AKAT_X_TM1637_POS_1);

                if (level == AKAT_X_TIMESTAMP_LEVEL_DECISECOND) {
                    tm1637.set_digit_pos_3(${tname}.get_deciseconds(), 0);
                    tm1637.set_digit_pos_4(${tname}.get_deciseconds(), 0);
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
