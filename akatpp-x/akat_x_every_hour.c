% if first_time:

static AKAT_FORCE_INLINE void akat_on_every_hour();

GLOBAL$() {
    STATIC_VAR$(u8 akat_every_hour_counter, initial = 60);
}

X_EVERY_MINUTE$(akat_every_hour_minute_handler) {
    akat_every_hour_counter -= 1;
    if (akat_every_hour_counter == 0) {
        akat_every_hour_counter = 60;
        akat_on_every_hour();
    }
}

% endif

FUNCTION$(void ${fname}(), inline) {
    ${body}
}
