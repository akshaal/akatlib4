X_GPIO_OUTPUT$(${oname}__Pin, ${pin});

GLOBAL$() {
    STATIC_VAR$(u8 ${oname}__play_deciseconds);
}

static akat_x_buzzer_sound_t const * ${oname}__sound_p;

% if not no_callbacks:
static akat_x_buzzer_finish_cbk_t ${oname}__play_finish_cbk;
% endif

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
        % if not no_callbacks:
        ${oname}.__call_finish_cbk(AKAT_ONE);
        % endif
    }

    % if not no_callbacks:
    METHOD$(void __call_finish_cbk(u8 const interrupted)) {
        if (${oname}__play_finish_cbk) {
            ${oname}__play_finish_cbk(interrupted);
        }
    }
    % endif

    METHOD$(void __play_current_sound()) {
        ${oname}__play_deciseconds = pgm_read_byte(&(${oname}__sound_p->deciseconds));
        if (${oname}__play_deciseconds == 0) {
            TCCR0B = 0;
            % if not no_callbacks:
            ${oname}.__call_finish_cbk(0);
            % endif
        } else {
            u8 cs = pgm_read_byte(&(${oname}__sound_p->cs));
            u8 ocr = pgm_read_byte(&(${oname}__sound_p->ocr));
            ${oname}.__set_cs_and_ocr(cs, ocr);
        }
    }

    METHOD$(void play(akat_x_buzzer_sound_t const * const melody
                      % if not no_callbacks:
                      , akat_x_buzzer_finish_cbk_t const finish_cbk
                      %endif
            )) {

        ${oname}.interrupt();

        % if not no_callbacks:
        ${oname}__play_finish_cbk = finish_cbk;
        % endif

        ${oname}__sound_p = melody - 1;
        ${oname}__play_deciseconds = AKAT_ONE;
    }
}

X_EVERY_DECISECOND$(${oname}__every_deci) {
    if (${oname}__play_deciseconds) {
        ${oname}__play_deciseconds--;

        if (${oname}__play_deciseconds == 0) {
            ${oname}__sound_p = ${oname}__sound_p + 1;
            ${oname}.__play_current_sound();
        }
    }
}
