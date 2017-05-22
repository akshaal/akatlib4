import akat_x_cpu

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["oname"], required_kvs = ["sounds"], optional_kvs = {"on_finish": None})

        sounds = []
        for ts in ctx.sounds.replace("(", "").replace(")", "").split(","):
            dur, freq = ts.strip().split("@")
            dur = int(dur.strip())
            freq = int(freq.strip())

            prescaler, ocr = akat_x_cpu.get_prescaler_and_ocr_for_freq(freq = freq * 2, max_ocr = 255, info = ctx.oname + ": " + ts.strip())
            cs = akat_x_cpu.get_cs_expr_for_prescaler(prescaler, "CS0")

            sounds.append(Struct(deciseconds = dur, cs = cs, ocr = ocr))

        return akat.transform(akat.render(self, sounds = sounds, oname = ctx.oname))
