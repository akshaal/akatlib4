import akat_x_main
import akat_x_cpu

funcs = []

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], body = True)

        funcs.append(ctx.name)

        first_time = len(funcs) == 1
        if first_time:
            akat_x_main.add_prerender_hook(self.__main_prerender_hook)

        return akat.transform(akat.render(self, body = inv.body, fname = ctx.name, first_time = first_time))

    def __main_prerender_hook(self):
        lines = "".join(["    " + func + "();\n" for func in funcs])
        every_dec_f = "\nstatic AKAT_FORCE_INLINE void akat_on_every_decisecond() {\n" + lines + "\n}\n"

        prescaler, compare_val = akat_x_cpu.get_prescaler_and_ocr_for_freq(freq = 10, max_ocr = 65535, info = "Setup for Timer1 for decisecond run")

        timer1_init = akat.transform("\nX_TIMER1_INIT$(prescaler = " + str(prescaler) + ", compare_a = " + str(compare_val) + ", ctc, interrupt_a);\n")

        return every_dec_f + timer1_init
