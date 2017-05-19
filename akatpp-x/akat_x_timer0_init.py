ctx = None

class Macro:
    def render(self, inv):
        global ctx

        if ctx != None:
            akat.fatal_error("Timer0 can't be initialized several times!")

        ctx = akat.prepare(inv,
                           required_kvs = ["prescaler"],
                           optional_kvs = {"compare_a": 0, "compare_b": 0},
                           keywords = ["ctc", "interrupt_a", "interrupt_b"])

        prescaler = ctx.prescaler

        if prescaler == "0":               cs02, cs01, cs00 = 0, 0, 0
        elif prescaler == "1":             cs02, cs01, cs00 = 0, 0, 1
        elif prescaler == "8":             cs02, cs01, cs00 = 0, 1, 0
        elif prescaler == "64":            cs02, cs01, cs00 = 0, 1, 1
        elif prescaler == "256":           cs02, cs01, cs00 = 1, 0, 0
        elif prescaler == "1024":          cs02, cs01, cs00 = 1, 0, 1
        elif prescaler == "T1_falling ":   cs02, cs01, cs00 = 1, 1, 0
        elif prescaler == "T1_rising":     cs02, cs01, cs00 = 1, 1, 1
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
                STRESS("T0_falling"), ", ",
                STRESS("T0_rising")
            )

        if ctx.ctc:
            wgm02 = 1
        else:
            wgm02 = 0

        render_context = {
            "cs00": cs00,
            "cs01": cs01,
            "cs02": cs02,
            "prescaler": prescaler,
            "wgm02": wgm02,
            "ocr_a": ctx.compare_a,
            "ocr_b": ctx.compare_b,
            "ocie0a": (ctx.interrupt_a and 1 or 0),
            "ocie0b": (ctx.interrupt_b and 1 or 0),
        }

        return akat.transform(akat.render(self, **render_context))
