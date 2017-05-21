import akat_x_main

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["oname"], required_kvs = ["min_freq", "max_freq"])
        self.__ctx = ctx

        akat_x_main.add_prerender_hook(self.__main_prerender_hook)

        mcu = akat.get_param("MCU")
        if mcu == "attiny2313":
            pin = "B2"
        elif mcu == "attiny85":
            pin = "B0"
        elif mcu == "atmega16":
            pin = "B3"
        elif mcu == "atmega32":
            pin = "B3"
        else:
            akat.fatal_error("Please fix ", STRESS("akat_x_buzzer"), " to add support for this platform: ", STRESS(mcu))

        render_ctx = {"pin": pin}
        self.__ctx.add_into(render_ctx)

        return akat.transform(akat.render(self, **render_ctx))

    def __main_prerender_hook(self):
        cpu_freq = akat_x_main.cpu_freq

        def find_prescaler(f):
            variants = [int(prescaler) for prescaler in [1., 8., 64., 256., 1024.] if cpu_freq/2/prescaler/f < 254 and cpu_freq/2/prescaler/f > 1]

            if len(variants) == 0:
                akat.fatal_error("Unable to find prescaler for frequency ", STRESS(cpu_freq), " such that it is possible to buzz on ", STRESS(f))

            return variants[0]

        splits = []
        prev_presc = None
        for f in range(int(self.__ctx.min_freq), int(self.__ctx.max_freq)):
            presc = find_prescaler(f)
            if presc != prev_presc:
                splits.append((f, presc))
            prev_presc = presc

        render_ctx = {}
        self.__ctx.add_into(render_ctx)

        return akat.transform(akat.render("akat_x_buzzer_freq.c", splits = splits, **render_ctx))
