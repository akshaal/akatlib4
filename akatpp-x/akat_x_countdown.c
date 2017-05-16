OBJECT$(${oname}) {
    ${body}

    METHOD$(void on_new_decisecond(), inline, ignore_dup) {}
    METHOD$(void on_new_second_l(), inline, ignore_dup) {}
    METHOD$(void on_new_minute_l(), inline, ignore_dup) {}
    METHOD$(void on_new_hour_l(), inline, ignore_dup) {}
    METHOD$(void on_new_second_h(), inline, ignore_dup) {}
    METHOD$(void on_new_minute_h(), inline, ignore_dup) {}
    METHOD$(void on_new_hour_h(), inline, ignore_dup) {}

    METHOD$(void on_start(), inline, ignore_dup) {}
    METHOD$(void on_finish(), inline, ignore_dup) {}

    METHOD$(u8 get_current_decisecond(), inline) { return akat_countdown_current_decisecond; }
    METHOD$(u8 get_current_second_h(), inline) { return akat_countdown_current_second_h; }
    METHOD$(u8 get_current_second_l(), inline) { return akat_countdown_current_second_l; }
    METHOD$(u8 get_current_minute_l(), inline) { return akat_countdown_current_minute_l; }
    METHOD$(u8 get_current_minute_h(), inline) { return akat_countdown_current_minute_h; }
    METHOD$(u8 get_current_hour_h(), inline) { return akat_countdown_current_hour_h; }
    METHOD$(u8 get_current_hour_l(), inline) { return akat_countdown_current_hour_l; }
}

GLOBAL$() {
    STATIC_VAR$(u8 akat_countdown_current_decisecond);
    STATIC_VAR$(u8 akat_countdown_current_second_h);
    STATIC_VAR$(u8 akat_countdown_current_minute_h);
    STATIC_VAR$(u8 akat_countdown_current_hour_h);
    STATIC_VAR$(u8 akat_countdown_current_second_l);
    STATIC_VAR$(u8 akat_countdown_current_minute_l);
    STATIC_VAR$(u8 akat_countdown_current_hour_l);
}

static AKAT_FORCE_INLINE void akat_call_on_new_decisecond();
static AKAT_FORCE_INLINE void akat_call_on_new_second_l();
static AKAT_FORCE_INLINE void akat_call_on_new_minute_l();
static AKAT_FORCE_INLINE void akat_call_on_new_hour_l();
static AKAT_FORCE_INLINE void akat_call_on_new_second_h();
static AKAT_FORCE_INLINE void akat_call_on_new_minute_h();
static AKAT_FORCE_INLINE void akat_call_on_new_hour_h();

X_EVERY_DECISECOND$(countdown_dechandler) {
    akat_countdown_current_decisecond += 1;

    if (akat_countdown_current_decisecond == 10) {
        akat_countdown_current_decisecond = 0;

        akat_countdown_current_second_l += 1;
        if (akat_countdown_current_second_l == 10) {
            akat_countdown_current_second_l = 0;

            akat_countdown_current_second_h += 1;
            if (akat_countdown_current_second_h == 6) {
                akat_countdown_current_second_h = 0;

                akat_countdown_current_minute_l += 1;
                if (akat_countdown_current_minute_l == 10) {
                    akat_countdown_current_minute_l = 0;

                    akat_countdown_current_minute_h += 1;
                    if (akat_countdown_current_minute_h == 6) {
                        akat_countdown_current_minute_h = 0;

                        akat_countdown_current_hour_l += 1;
                        if (akat_countdown_current_hour_l == 10) {
                            akat_countdown_current_hour_l = 0;
                            akat_countdown_current_hour_h += 1;
                            akat_call_on_new_hour_h();
                        } else if (akat_countdown_current_hour_l == 4 && akat_countdown_current_hour_h == 2) {
                            akat_countdown_current_hour_l = 0;
                            akat_countdown_current_hour_h = 0;
                            akat_call_on_new_hour_h();
                        }

                        akat_call_on_new_hour_l();
                    } // end if (akat_countdown_current_minute_h == 6)

                    akat_call_on_new_minute_h();
                } // if (akat_countdown_current_minute_l == 10)

                akat_call_on_new_minute_l();
            } // if (akat_countdown_current_second_h == 6)

            akat_call_on_new_second_h();
        } // if (akat_countdown_current_second_l == 10)

        akat_call_on_new_second_l();
    }

    akat_call_on_new_decisecond();
}

