X_INIT$(timer0) {
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

    % if int(ocr_a) > 0:
    OCR0A = ${ocr_a};
    % endif

    % if int(ocr_b) > 0:
    OCR0B = ${ocr_b};
    % endif

    % if ocie0a == 1 or ocie0b == 1:
    TIMSK0 |= (${ocie0a} << OCIE0A) | (${ocie0b} << OCIE0B);
    % endif

    // Configuring Timer0 for prescaler ${prescaler}
    TCCR0B |= (${cs02} << CS02) | (${cs01} << CS01) | (${cs00} << CS00);
    TCCR0A |= (${wgm01} << WGM01);
}
