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
        every_dec_f = "\nstatic AKAT_FORCE_INLINE void akat_on_every_minute() {\n" + lines + "\n}\n"

        return every_dec_f
