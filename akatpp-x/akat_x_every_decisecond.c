% if first_time:

static AKAT_FORCE_INLINE void akat_on_every_decisecond();

// Can't use LOW register here!
USE_REG$(akat_every_decisecond_run_required);

GLOBAL$() {
    STATIC_VAR$(u8 akat_every_decisecond_run_required);
}

RUNNABLE$(akat_on_every_decisecond_runner) {
    // Tell gcc that this variable can be changed somehow (in our case via ISR)
    AKAT_FLUSH_REG_VAR(akat_every_decisecond_run_required);

    if (akat_every_decisecond_run_required) {
        akat_every_decisecond_run_required = AKAT_FALSE;
        akat_on_every_decisecond();
    }
}

ISR(TIMER1_COMPA_vect, ISR_NAKED) {
    // NOTE: Make sure that 'akat_every_decisecond_run_required' is not a register under R16!
    // NOTE: Otherwise we have to save SREG. That's why we use assembler directly here.
    asm volatile("ldi %0, 0x01" : "=r" (akat_every_decisecond_run_required));
    asm volatile("reti");
}

% endif

FUNCTION$(void ${fname}(), inline) {
    ${body}
}
