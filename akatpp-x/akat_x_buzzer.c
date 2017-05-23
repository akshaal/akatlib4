X_GPIO_OUTPUT$(${oname}__Pin, ${pin});

static akat_x_buzzer_sound_t const * ${oname}__sound_p;
static u8 ${oname}__play_deciseconds;
static akat_x_buzzer_finish_cbk_t ${oname}__play_finish_cbk;

#include <avr/pgmspace.h>

OBJECT$(${oname}) {
    METHOD$(void __set_cs_and_ocr(u8 const cs, u8 const ocr)) {
        TCNT0 = 0; // Reset timer
        TCCR0A = 1 << COM0A0 | (1 << WGM01); // It means TOGGLE on Compare Match and CTC
        OCR0A = ocr; // Compare Match value
        TCCR0B = cs; // Clock Select
    }

    METHOD$(void interrupt()) {
        TCCR0B = 0;

        if (${oname}__play_deciseconds == 0) {
            return; // Already interrupted
        }

        ${oname}.__call_finish_cbk(1);
    }

    METHOD$(void __call_finish_cbk(u8 const interrupted)) {
        if (${oname}__play_finish_cbk) {
            ${oname}__play_finish_cbk(interrupted);
        }
    }

    METHOD$(void __play_current_sound()) {
        ${oname}__play_deciseconds = pgm_read_byte(&(${oname}__sound_p->deciseconds));
        if (${oname}__play_deciseconds == 0) {
            TCCR0B = 0;
            ${oname}.__call_finish_cbk(0);
        } else {
            u8 cs = pgm_read_byte(&(${oname}__sound_p->cs));
            u8 ocr = pgm_read_byte(&(${oname}__sound_p->ocr));
            ${oname}.__set_cs_and_ocr(cs, ocr);
        }
    }

    METHOD$(void __play(akat_x_buzzer_sound_t const * const melody)) {
        ${oname}__sound_p = melody;
        ${oname}.__play_current_sound();
    }

    METHOD$(void play(akat_x_buzzer_sound_t const * const melody, akat_x_buzzer_finish_cbk_t const finish_cbk)) {
        ${oname}.interrupt();
        ${oname}__play_finish_cbk = finish_cbk;
        ${oname}.__play(melody);
    }
}

X_EVERY_DECISECOND$(${oname}__every_deci) {
    if (${oname}__play_deciseconds) {
        ${oname}__play_deciseconds--;

        if (${oname}__play_deciseconds == 0) {
            ${oname}.__play(${oname}__sound_p + 1);
        }
    }
}
