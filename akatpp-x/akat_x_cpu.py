_cpu_freq = None


# ---------------------------------------------
class Macro:
    def render(self, inv):
        args = akat.prepare(inv, required_kvs = ["cpu_freq"])

        # Setup some global info
        global _cpu_freq

        if _cpu_freq != None:
            akat.fatal_error("Seems like cpu_freq is already set to ", STRESS(_cpu_freq), "... can't set it second time to ", STRESS(args.cpu_freq), "!")

        _cpu_freq = int(args.cpu_freq)

        # Return result
        render_context = {}

        args.add_into(render_context)

        return akat.transform(akat.render(self, **render_context))


# ---------------------------------------------
def get_cpu_freq():
    if _cpu_freq == None:
        akat.fatal_error("CPU frequency is not set, use X_CPU macro to set it before use!")

    return _cpu_freq


# ---------------------------------------------
def get_prescaler_and_ocr_for_freq(freq, max_ocr, info = None, error = None):
    cpu_freq = get_cpu_freq()

    # Try to get the best stuff
    def mk_variant(prescaler):
        ocr = int(round(cpu_freq/prescaler/freq - 1))
        if ocr == -1: ocr = -0.999999999999999999
        real_freq = cpu_freq / (ocr + 1.0) / prescaler
        diff = abs(real_freq - freq)
        return (int(prescaler), ocr, diff, real_freq)

    variants = [mk_variant(prescaler) for prescaler in [1., 8., 64., 256., 1024.]]
    variants = [variant for variant in variants if variant[1] < max_ocr and variant[1] > 2]
    if len(variants) == 0:
        akat.fatal_error("Unable to find prescaler/ocr for CPU frequency ", STRESS(cpu_freq), " such that it is possible to get ", STRESS(freq), " frequency")

    variants.sort(key = lambda v: v[2]) # Sort by diff ascending
    best_diff = variants[0][2]

    if error != None and best_diff != 0:
        akat.fatal_error(error, ": unable to find prescaler/ocr for CPU frequency ", STRESS(cpu_freq), " such that it is possible to get exactly ", STRESS(freq), " frequency")

    # Get all with best diffs and select one with higher OCR
    variants = [variant for variant in variants if variant[2] == best_diff]
    variants.sort(key = lambda v: v[1]) # Sort by ocr ascending

    best_v = variants[-1]

    if info != None and best_diff != 0:
        akat.print_info(info, " : you will get frequency ", STRESS(best_v[3]), " instead of requested ", STRESS(freq))

    return (best_v[0], best_v[1])

# ---------------------------------------------
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

