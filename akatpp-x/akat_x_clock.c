% if first_time:

GLOBAL$() {
    STATIC_VAR$(u8 akat_clock_current_decisecond);
    STATIC_VAR$(u8 akat_clock_current_second);
    STATIC_VAR$(u8 akat_clock_current_minute);
    STATIC_VAR$(u8 akat_clock_current_hour);
}

static AKAT_FORCE_INLINE void akat_call_on_new_decisecond();
static AKAT_FORCE_INLINE void akat_call_on_new_second();
static AKAT_FORCE_INLINE void akat_call_on_new_minute();
static AKAT_FORCE_INLINE void akat_call_on_new_hour();

X_EVERY_DECISECOND$(clock_dechandler) {
    akat_clock_current_decisecond += 1;

    if (akat_clock_current_decisecond == 10) {
        akat_clock_current_decisecond = 0;

        akat_clock_current_second += 1;
        if (akat_clock_current_second == 60) {
            akat_clock_current_second = 0;

            akat_clock_current_minute += 1;
            if (akat_clock_current_minute == 60) {
                akat_clock_current_minute = 0;

                akat_clock_current_hour += 1;
                if (akat_clock_current_hour == 24) {
                    akat_clock_current_hour = 0;
                }

                akat_call_on_new_hour();
            }

            akat_call_on_new_minute();
        }

        akat_call_on_new_second();
    }

    akat_call_on_new_decisecond();
}

% endif

OBJECT$(${oname}) {
    ${body}

    METHOD$(u8 get_current_decisecond(), inline) { return akat_clock_current_decisecond; }
    METHOD$(u8 get_current_second(), inline) { return akat_clock_current_second; }
    METHOD$(u8 get_current_minute(), inline) { return akat_clock_current_minute; }
    METHOD$(u8 get_current_hour(), inline) { return akat_clock_current_hour; }
}
