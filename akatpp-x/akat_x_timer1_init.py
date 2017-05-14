ctx = None

class Macro:
    def render(self, inv):
        global ctx

        if ctx != None:
            akat.fatal_error("Timer1 can't be initialized several times!")

        ctx = akat.prepare(inv,
                           required_kvs = ["prescaler"],
                           optional_kvs = {"compare_a": 0, "compare_b": 0},
                           keywords = ["ctc", "interrupt_a", "interrupt_b"])

        prescaler = ctx.prescaler

        if prescaler == "0":               cs12, cs11, cs10 = 0, 0, 0
        elif prescaler == "1":             cs12, cs11, cs10 = 0, 0, 1
        elif prescaler == "8":             cs12, cs11, cs10 = 0, 1, 0
        elif prescaler == "64":            cs12, cs11, cs10 = 0, 1, 1
        elif prescaler == "256":           cs12, cs11, cs10 = 1, 0, 0
        elif prescaler == "1024":          cs12, cs11, cs10 = 1, 0, 1
        elif prescaler == "T1_falling ":   cs12, cs11, cs10 = 1, 1, 0
        elif prescaler == "T1_rising":     cs12, cs11, cs10 = 1, 1, 1
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
                STRESS("T1_falling"), ", ",
                STRESS("T1_rising")
            )

        if ctx.ctc:
            wgm12 = 1
        else:
            wgm12 = 0

        render_context = {
            "cs10": cs10,
            "cs11": cs11,
            "cs12": cs12,
            "prescaler": prescaler,
            "wgm12": wgm12,
            "ocr_a": ctx.compare_a,
            "ocr_b": ctx.compare_b,
            "ocie1a": (ctx.interrupt_a and 1 or 0),
            "ocie1b": (ctx.interrupt_b and 1 or 0),
        }

        return akat.transform(akat.render(self, **render_context))
