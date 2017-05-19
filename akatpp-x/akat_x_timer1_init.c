X_INIT$(timer1) {
    // Initial value of TCCR1B is zero, three low bits (CS12, CS11, CS10) configure prescaler (frequency divider)
    // CS means Clock Select
    // ===========================================
    // Bits of TCCR1B:
    // bit number:        2      1      0
    // bit name:       CS12   CS11   CS10
    // default value:     0      0      0
    // ===========================================
    // CS12 CS11 CS10
    //   0    0    0     No clock source (Timer/Counter stopped)
    //   0    0    1     Freq / 1 (No prescaling)
    //   0    1    0     Freq / 8
    //   0    1    1     Freq / 64
    //   1    0    0     Freq / 256
    //   1    0    1     Freq / 1024
    //   1    1    0     External clock on T1 pin. Falling edge.
    //   1    1    1     External clock on T1 pin. Rising edge
    // ===========================================

    % if int(ocr_a) > 0:
    OCR1A = ${ocr_a};
    % endif

    % if int(ocr_b) > 0:
    OCR1B = ${ocr_b};
    % endif

    % if ocie1a == 1 or ocie1b == 1:
    TIMSK1 |= (${ocie1a} << OCIE1A) | (${ocie1b} << OCIE1B);
    % endif

    // Configuring Timer1 for prescaler ${prescaler}
    TCCR1B |= (${cs12} << CS12) | (${cs11} << CS11) | (${cs10} << CS10) | (${wgm12} << WGM12);
}
