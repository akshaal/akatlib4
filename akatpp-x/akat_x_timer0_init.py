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

        cs_expr = akat_x_cpu.get_cs_expr_for_prescaler(prescaler, cs = "CS0")

        if ctx.ctc:
            wgm01 = 1
        else:
            wgm01 = 0

        render_context = {
            "cs_expr": cs_expr,
            "prescaler": prescaler,
            "wgm01": wgm01,
            "ocr_a": ctx.compare_a,
            "ocr_b": ctx.compare_b,
            "ocie0a": (ctx.interrupt_a and 1 or 0),
            "ocie0b": (ctx.interrupt_b and 1 or 0),
        }

        return akat.transform(akat.render(self, **render_context))
