class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["bname", "oname"], required_kvs = ["sounds"])

        sounds = []
        for ts in ctx.sounds.replace("(", "").replace(")", "").split(","):
            dur, freq = ts.strip().split("@")
            dur = int(dur)

            prescaler = ctx.bname + "__get_prescaler(" + freq + ")"
            ocr = "1"

            sounds.append(Struct(deciseconds = dur, prescaler = prescaler, ocr = ocr))

        return akat.transform(akat.render(self, sounds = sounds, oname = ctx.oname))
