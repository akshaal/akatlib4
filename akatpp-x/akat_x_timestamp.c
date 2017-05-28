GLOBAL$() {
    STATIC_VAR$(u8 akat_timestamp_decisecond__${oname});
    STATIC_VAR$(u8 akat_timestamp_second__${oname});
    STATIC_VAR$(u8 akat_timestamp_minute__${oname});
    STATIC_VAR$(u8 akat_timestamp_hour__${oname});
};

// BCD format
//    76543210
// -------------
// 0   0000000
// 1   0010001
// 2   0100010
// 3   0110011
// 4   1000100
// 5   1010101
// 6   1100110
// 7      0111
// 8      1000
// 9      1001
//10      1010

static void akat_timestamp_on_new_decisecond__${oname}();
static void akat_timestamp_on_new_minute__${oname}();
static void akat_timestamp_on_new_hour__${oname}();
static void akat_timestamp_on_new_second__${oname}();

OBJECT$(${oname}) {
    METHOD$(u8 get_deciseconds(), inline) { return akat_timestamp_decisecond__${oname}; }
    METHOD$(u8 get_seconds_h()) { return AKAT_BCD_GET_H(akat_timestamp_second__${oname}); }
    METHOD$(u8 get_seconds_l()) { return AKAT_BCD_GET_L(akat_timestamp_second__${oname}); }
    METHOD$(u8 get_minutes_h()) { return AKAT_BCD_GET_H(akat_timestamp_minute__${oname}); }
    METHOD$(u8 get_minutes_l()) { return AKAT_BCD_GET_L(akat_timestamp_minute__${oname}); }
    METHOD$(u8 get_hours_h()) { return AKAT_BCD_GET_H(akat_timestamp_hour__${oname}); }
    METHOD$(u8 get_hours_l()) { return AKAT_BCD_GET_L(akat_timestamp_hour__${oname}); }

    METHOD$(u8 has_hours()) { return akat_timestamp_hour__${oname}; }
    METHOD$(u8 has_minutes()) { return akat_timestamp_minute__${oname}; }
    METHOD$(u8 has_seconds()) { return akat_timestamp_second__${oname}; }

    METHOD$(void set_deciseconds(u8 v)) {
        akat_timestamp_decisecond__${oname} = v;
        akat_timestamp_on_new_decisecond__${oname}();
    }

    METHOD$(void set_bcd_seconds(u8 bcd)) {
        akat_timestamp_second__${oname} = bcd;
        akat_timestamp_on_new_second__${oname}();
    }

    METHOD$(void set_bcd_minutes(u8 bcd)) {
        akat_timestamp_minute__${oname} = bcd;
        akat_timestamp_on_new_minute__${oname}();
    }

    METHOD$(void set_bcd_hours(u8 bcd)) {
        akat_timestamp_hour__${oname} = bcd;
        akat_timestamp_on_new_hour__${oname}();
    }

    METHOD$(void reset()) {
        akat_timestamp_decisecond__${oname} = 0;
        akat_timestamp_second__${oname} = 0;
        akat_timestamp_minute__${oname} = 0;
        akat_timestamp_hour__${oname} = 0;

        akat_timestamp_on_new_decisecond__${oname}();
        akat_timestamp_on_new_second__${oname}();
        akat_timestamp_on_new_minute__${oname}();
        akat_timestamp_on_new_hour__${oname}();
    }

    METHOD$(u8 inc_hours()) {
        u8 rc = AKAT_FALSE; // Return true if there is an overflow

        if (akat_timestamp_hour__${oname} == AKAT_BCD(2, 3)) {
            akat_timestamp_hour__${oname} = 0;
            rc = AKAT_TRUE;
        } else {
            akat_timestamp_hour__${oname} = akat_bcd_inc(akat_timestamp_hour__${oname});
        }

        akat_timestamp_on_new_hour__${oname}();

        return rc;
    }

    METHOD$(u8 inc_minutes(u8 inc_further)) {
        u8 rc = 0; // Return true if there is an overflow

        if (akat_timestamp_minute__${oname} == AKAT_BCD(5, 9)) {
            akat_timestamp_minute__${oname} = 0;
            if (inc_further) {
                rc = ${oname}.inc_hours();
            }
        } else {
            akat_timestamp_minute__${oname} = akat_bcd_inc(akat_timestamp_minute__${oname});
        }

        akat_timestamp_on_new_minute__${oname}();

        return rc;
    }

    METHOD$(u8 inc_seconds(u8 inc_further)) {
        u8 rc = 0; // Return true if there is an overflow

        if (akat_timestamp_second__${oname} == AKAT_BCD(5, 9)) {
            akat_timestamp_second__${oname} = 0;
            if (inc_further) {
                rc = ${oname}.inc_minutes(inc_further);
            }
        } else {
            akat_timestamp_second__${oname} = akat_bcd_inc(akat_timestamp_second__${oname});
        }

        akat_timestamp_on_new_second__${oname}();

        return rc;
    }

    METHOD$(u8 inc_deciseconds(u8 inc_further)) {
        u8 rc = 0; // Return true if there is an overflow

        if (akat_timestamp_decisecond__${oname} == 9) {
            akat_timestamp_decisecond__${oname} = 0;
            if (inc_further) {
                rc = ${oname}.inc_seconds(inc_further);
            }
        } else {
            akat_timestamp_decisecond__${oname}++;
        }

        akat_timestamp_on_new_decisecond__${oname}();

        return rc;
    }

    METHOD$(u8 dec_deciseconds(u8 dec_further)) {
        u8 rc = 0; // Returns 0 if no underflow

        if (akat_timestamp_decisecond__${oname} == 0) {
            akat_timestamp_decisecond__${oname} = 9;

            if (dec_further) {
                rc = ${oname}.dec_seconds(dec_further);
            }
        } else {
            akat_timestamp_decisecond__${oname}--;
        }

        akat_timestamp_on_new_decisecond__${oname}();

        return rc;
    }

    METHOD$(u8 dec_seconds(u8 dec_further)) {
        u8 rc = AKAT_FALSE; // Returns 0 if no underflow

        if (akat_timestamp_second__${oname} == 0) {
            akat_timestamp_second__${oname} = AKAT_BCD(5, 9);
            if (dec_further) {
                rc = ${oname}.dec_minutes(dec_further);
            }
        } else {
            akat_timestamp_second__${oname} = akat_bcd_dec(akat_timestamp_second__${oname});
        }

        akat_timestamp_on_new_second__${oname}();

        return rc;
    }

    METHOD$(u8 dec_minutes(u8 dec_further)) {
        u8 rc = AKAT_FALSE; // Returns 0 if no underflow

        if (akat_timestamp_minute__${oname} == 0) {
            akat_timestamp_minute__${oname} = AKAT_BCD(5, 9);
            if (dec_further) {
                rc = ${oname}.dec_hours();
            }
        } else {
            akat_timestamp_minute__${oname} = akat_bcd_dec(akat_timestamp_minute__${oname});
        }

        akat_timestamp_on_new_minute__${oname}();

        return rc;
    }

    METHOD$(u8 dec_hours()) {
        u8 rc = AKAT_FALSE; // Returns 0 if no underflow

        if (akat_timestamp_hour__${oname} == 0) {
            akat_timestamp_hour__${oname} = AKAT_BCD(2, 3);
            rc = AKAT_TRUE;
        } else {
            akat_timestamp_hour__${oname} = akat_bcd_dec(akat_timestamp_hour__${oname});
        }

        akat_timestamp_on_new_hour__${oname}();

        return rc;
    }
}
