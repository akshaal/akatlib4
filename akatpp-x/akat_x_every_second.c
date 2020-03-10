% if first_time:

static AKAT_FORCE_INLINE void akat_on_every_second();

GLOBAL$() {
    STATIC_VAR$(u8 akat_every_second_counter, initial = 10);
}

X_EVERY_DECISECOND$(akat_every_second_decisecond_handler) {
    akat_every_second_counter -= 1;
    if (akat_every_second_counter == 0) {
        akat_every_second_counter = 10;
        akat_on_every_second();
    }
}

% endif

FUNCTION$(void ${fname}(), inline) {
    ${body}
}
