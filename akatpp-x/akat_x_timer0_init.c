X_INIT$(timer0) {
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
    TCCR0B |= ${cs_expr};
    TCCR0A |= (${wgm01} << WGM01);
}
