import akat_x_cpu

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

        cs_expr = akat_x_cpu.get_cs_expr_for_prescaler(prescaler, cs = "CS1")

        if ctx.ctc:
            wgm12 = 1
        else:
            wgm12 = 0

        render_context = {
            "cs_expr": cs_expr,
            "prescaler": prescaler,
            "wgm12": wgm12,
            "ocr_a": ctx.compare_a,
            "ocr_b": ctx.compare_b,
            "ocie1a": (ctx.interrupt_a and 1 or 0),
            "ocie1b": (ctx.interrupt_b and 1 or 0),
        }

        return akat.transform(akat.render(self, **render_context))
