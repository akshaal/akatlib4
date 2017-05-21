static AKAT_UNUSED AKAT_PURE u16 ${oname}__get_prescaler(u16 const freq);

X_GPIO_OUTPUT$(${oname}__Pin, ${pin});

OBJECT$(${oname}) {
    METHOD$(void __set_prescaler_and_ocr(u16 const prescaler, u8 const ocr)) {
        TCNT0 = 0; // Reset timer
        TCCR0A = 1 << COM0A0 | (1 << WGM01); // It means TOGGLE on Compare Match and CTC
        OCR0A = ocr; // Compare Match value

        // WGM02 means CTC mode
        if (prescaler == 1) {
            TCCR0B = (0 << CS02) | (0 << CS01) | (1 << CS00); // Prescaler 1
        } else if (prescaler == 8) {
            TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00); // Prescaler 8
        } else if (prescaler == 64) {
            TCCR0B = (0 << CS02) | (1 << CS01) | (1 << CS00); // Prescaler 64
        } else if (prescaler == 256) {
            TCCR0B = (1 << CS02) | (0 << CS01) | (0 << CS00); // Prescaler 256
        } else if (prescaler == 1024) {
            TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00); // Prescaler 1024
        } else {
            X_FATAL_ERROR$("Buzzer '${oname}': Unknown prescaler value in buzzer");
        }
    }

    METHOD$(void off()) {
        TCCR0B = 0;
    }

    METHOD$(void set_freq(u16 const freq)) {
        u8 const prescaler = ${oname}__get_prescaler(freq);
        ${oname}.__set_prescaler_and_ocr(prescaler, akat_cpu_freq_hz() / 2 / prescaler / freq - 1);
    }
}
