X_INIT$(timer1) {
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
    TCCR1B |= ${cs_expr} | (1 << WGM12);
}
