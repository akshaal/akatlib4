% if first_time:

static AKAT_FORCE_INLINE void akat_on_every_minute();

GLOBAL$() {
    STATIC_VAR$(u8 akat_every_minute_counter, initial = 60);
}

X_EVERY_SECOND$(akat_every_minute_second_handler) {
    akat_every_minute_counter -= 1;
    if (akat_every_minute_counter == 0) {
        akat_every_minute_counter = 60;
        akat_on_every_minute();
    }
}

% endif

FUNCTION$(void ${fname}(), inline) {
    ${body}
}
