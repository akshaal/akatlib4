import akat_x_timestamp

idx = 0

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], body = True)

        global idx
        idx += 1

        if ctx.name not in akat_x_timestamp.callbacks:
            akat.fatal_error("No timestamp defined with name ", STRESS(ctx.name))

        akat_x_timestamp.callbacks[ctx.name].append(ctx.name + "__" + str(idx))

        return akat.transform(akat.render(self, body = inv.body, oname = ctx.name, idx = idx))
