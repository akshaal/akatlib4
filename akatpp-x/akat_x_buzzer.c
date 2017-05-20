static AKAT_UNUSED AKAT_PURE u8 ${oname}__get_prescaler(u16 const freq);

OBJECT$(${oname}) {
    METHOD$(void __set_prescaler_and_ocr(u8 const prescaler, u8 const ocr)) {
    }

    METHOD$(void set_freq(u16 const freq)) {
        u8 const prescaler = ${oname}__get_prescaler(freq);
        ${oname}.__set_prescaler_and_ocr(prescaler, akat_cpu_freq_hz() / 2 / prescaler / freq);
    }
}
