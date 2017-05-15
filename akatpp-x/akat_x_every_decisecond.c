% if first_time:

static AKAT_FORCE_INLINE void akat_on_every_decisecond();

//USE_REG$(akat_every_decisecond_run_required);

GLOBAL$() {
    STATIC_VAR$(u8 akat_every_decisecond_run_required);
}

RUNNABLE$(akat_on_every_decisecond_runner) {
    // Tell gcc that this variable can be changed somehow (in our case via ISR)
    //AKAT_FLUSH_REG_VAR(akat_every_decisecond_run_required);

    if (akat_every_decisecond_run_required) {
        akat_every_decisecond_run_required = 0;
        akat_on_every_decisecond();
    }
}

ISR(TIMER1_COMPA_vect) {
    akat_every_decisecond_run_required = 1;
//    asm volatile("reti");
}

% endif

FUNCTION$(void ${fname}(), inline) {
    ${body}
}
