% if first_time:

static AKAT_FORCE_INLINE void akat_on_every_decisecond();

// TODO: OPTIMIZE
// USE_REG$(akat_every_decisecond_run_required);

GLOBAL$() {
    STATIC_VAR$(u8 volatile akat_every_decisecond_run_required);
}

RUNNABLE$(akat_on_every_decisecond_runner) {
    if (akat_every_decisecond_run_required) {
        akat_every_decisecond_run_required = 0;
        akat_on_every_decisecond();
    }
}

// TODO: OPTIMIZE
ISR(TIMER1_COMPA_vect) {
    akat_every_decisecond_run_required = 1;
    // TODO: asm volatile("reti");
}

% endif

FUNCTION$(void ${fname}(), inline) {
    ${body}
}
