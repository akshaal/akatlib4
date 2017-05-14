import akat_x_main

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

        freq = akat_x_main.cpu_freq
        vars = [(int(prescaler), int(freq/prescaler/10 - 1)) for prescaler in [1., 8., 64., 256., 1024.] if freq/prescaler/10 < 65537 and (freq/prescaler) % 10 == 0]
        if len(vars) == 0:
            akat.fatal_error("Unable to find prescaler for frequency ", STRESS(freq), " such that it is possible to make decisecond timer")
        prescaler, compare_val = vars[0]

        timer1_init = akat.transform("\nX_TIMER1_INIT$(prescaler = " + str(prescaler) + ", compare_a = " + str(compare_val) + ", ctc, interrupt_a);\n")

        return every_dec_f + timer1_init
