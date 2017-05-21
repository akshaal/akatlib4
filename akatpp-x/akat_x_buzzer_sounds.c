static PROGMEM akat_x_buzzer_sound_t const ${oname}[] = {
    % for sound in sounds:
        {.deciseconds = ${sound.deciseconds}, .prescaler = ${sound.prescaler}, .ocr = ${sound.ocr}},
    % endfor
    {.deciseconds = 0, .prescaler = 0, .ocr = 0}
};
