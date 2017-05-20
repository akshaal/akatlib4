static AKAT_UNUSED AKAT_PURE u8 ${oname}__get_prescaler(u16 const freq);

OBJECT$(${oname}) {
    METHOD$(void __set_prescaler_and_ocr(u8 const prescaler, u8 const ocr)) {
        if prescaler == "0":               cs02, cs01, cs00 = 0, 0, 0
                            elif prescaler == "1":             cs02, cs01, cs00 = 0, 0, 1
                            elif prescaler == "8":             cs02, cs01, cs00 = 0, 1, 0
                            elif prescaler == "64":            cs02, cs01, cs00 = 0, 1, 1
                            elif prescaler == "256":           cs02, cs01, cs00 = 1, 0, 0
                            elif prescaler == "1024":          cs02, cs01, cs00 = 1, 0, 1
                            elif prescaler == "T1_falling ":   cs02, cs01, cs00 = 1, 1, 0
                            elif prescaler == "T1_rising":     cs02, cs01, cs00 = 1, 1, 1
            else:
                // TODO call global error handler
    }

    METHOD$(void set_freq(u16 const freq)) {
        u8 const prescaler = ${oname}__get_prescaler(freq);
        ${oname}.__set_prescaler_and_ocr(prescaler, akat_cpu_freq_hz() / 2 / prescaler / freq);
    }
}
