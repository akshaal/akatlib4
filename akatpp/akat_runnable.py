import akat_x_main

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], body = True)

        akat_x_main.runnables.append(ctx.name)

        return akat.transform(akat.render(self, body = inv.body, f_name = ctx.name))
