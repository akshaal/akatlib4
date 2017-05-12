static AKAT_FORCE_INLINE AKAT_CONST AKAT_PURE uint32_t akat_cpu_freq_hz() {
    return ${cpu_freq};
}

static AKAT_FORCE_INLINE AKAT_UNUSED uint8_t akat_get_tick() {
    return TCNT0;
}

static AKAT_FORCE_INLINE AKAT_UNUSED uint8_t akat_tick_period_us() {
    return ${tick_period_us};
}

AKAT_NO_RETURN void main() {
    % if tick_period_us != 0:
    // Initial value of TCCR0B is zero, three low bits (CS02, CS01, CS00) configure prescaler (frequency divider)
    // CS means Clock Select
    // ===========================================
    // Bits of TCCR0B:
    // bit number:        2      1      0
    // bit name:       CS02   CS01   CS00
    // default value:     0      0      0
    // ===========================================
    // CS02 CS01 CS00
    //   0    0    0     No clock source (Timer/Counter stopped)
    //   0    0    1     Freq / 1 (No prescaling)
    //   0    1    0     Freq / 8
    //   0    1    1     Freq / 64
    //   1    0    0     Freq / 256
    //   1    0    1     Freq / 1024
    //   1    1    0     External clock on T0 pin. Falling edge.
    //   1    1    1     External clock on T0 pin. Rising edge
    // ===========================================

    // Configuring Timer0 for tick period ${tick_period_us}us (prescaler value ${int(tick_prescaler)})
    // This gives us max measured period ${int(tick_period_us * 200)}us or something like that
    TCCR0B |= (${cs02} << CS02) | (${cs01} << CS01) | (${cs00} << CS00);

    % endif

    % for init in inits:
        ${init}();
    % endfor

    // Init
    ${body}

    // Endless loop with threads, tasks and such
    while(1) {
        % for i in range(unroll):
            % for runnable in runnables:
                ${runnable}();
            % endfor
        % endfor
    }
}
