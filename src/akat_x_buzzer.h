///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

typedef struct {
    uint8_t const cs;
    uint8_t const ocr;
    uint8_t const deciseconds;
} akat_x_buzzer_sound_t;

typedef void (*akat_x_buzzer_finish_cbk_t)(u8 interrupted);
