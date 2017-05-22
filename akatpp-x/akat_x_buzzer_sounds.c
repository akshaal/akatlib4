static PROGMEM akat_x_buzzer_sound_t const ${oname}[] = {
    % for sound in sounds:
        {.deciseconds = ${sound.deciseconds}, .cs = ${sound.cs}, .ocr = ${sound.ocr}},
    % endfor
    {.deciseconds = 0, .cs = 0, .ocr = 0}
};
