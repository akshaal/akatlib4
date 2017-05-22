def get_prescaler_and_ocr_for_freq(freq, max_ocr):
    cpu_freq = akat_x_main.get_cpu_freq()

    vars = [(int(prescaler), int(freq/prescaler/10 - 1)) for prescaler in [1., 8., 64., 256., 1024.] if freq/prescaler/10 < 65537 and (freq/prescaler) % 10 == 0]
        if len(vars) == 0:
            akat.fatal_error("Unable to find prescaler for frequency ", STRESS(freq), " such that it is possible to make decisecond timer")

def get_cs_expr_for_prescaler(prescaler, cs):
    prescaler = str(prescaler)

    if prescaler == "0":               cs2, cs1, cs0 = "0", "0", "0"
    elif prescaler == "1":             cs2, cs1, cs0 = "0", "0", "1"
    elif prescaler == "8":             cs2, cs1, cs0 = "0", "1", "0"
    elif prescaler == "64":            cs2, cs1, cs0 = "0", "1", "1"
    elif prescaler == "256":           cs2, cs1, cs0 = "1", "0", "0"
    elif prescaler == "1024":          cs2, cs1, cs0 = "1", "0", "1"
    elif prescaler == "T_falling":     cs2, cs1, cs0 = "1", "1", "0"
    elif prescaler == "T_rising":      cs2, cs1, cs0 = "1", "1", "1"
    else:
        akat.fatal_error(
            "Unknown value for prescaler: ",
            STRESS(prescaler),
            ". While this one can be one of these: ",
            STRESS("1"), ", ",
            STRESS("8"), ", ",
            STRESS("64"), ", ",
            STRESS("256"), ", ",
            STRESS("1024"), ", ",
            STRESS("T_falling"), ", ",
            STRESS("T_rising")
        )

    comment = "/* Prescaler " + prescaler  + " */"

    return "((" + cs2 + " << " + cs + "2) |" + "(" + cs1 + " << " + cs + "1) |" + "(" + cs0 + " << " + cs + "0) " + comment + ")"
