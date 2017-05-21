static AKAT_UNUSED AKAT_PURE u16 ${oname}__get_prescaler(u16 const freq);

X_GPIO_OUTPUT$(${oname}__Pin, ${pin});

OBJECT$(${oname}) {
    METHOD$(void __set_prescaler_and_ocr(u16 const prescaler, u8 const ocr)) {
        TCNT0 = 0; // Reset timer
        TCCR0A = 1 << COM0A0; // It means TOGGLE on Compare Match
        OCR0A = ocr; // Compare Match value

        // WGM02 means CTC mode
        if (prescaler == 1) {
            TCCR0B = (0 << CS02) | (0 << CS01) | (1 << CS00) | (1 << WGM02); // Prescaler 1 and CTC
        } else if (prescaler == 8) {
            TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00) | (1 << WGM02); // Prescaler 8 and CTC
        } else if (prescaler == 64) {
            TCCR0B = (0 << CS02) | (1 << CS01) | (1 << CS00) | (1 << WGM02); // Prescaler 64 and CTC
        } else if (prescaler == 256) {
            TCCR0B = (1 << CS02) | (0 << CS01) | (0 << CS00) | (1 << WGM02); // Prescaler 256 and CTC
        } else if (prescaler == 1024) {
            TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00) | (1 << WGM02); // Prescaler 1024 and CTC
        } else {
            X_FATAL_ERROR$("Buzzer '${oname}': Unknown prescaler value in buzzer");
        }
    }

    METHOD$(void set_freq(u16 const freq)) {
        u8 const prescaler = ${oname}__get_prescaler(freq);
        ${oname}.__set_prescaler_and_ocr(prescaler, akat_cpu_freq_hz() / 2 / prescaler / freq - 1);
    }
}
