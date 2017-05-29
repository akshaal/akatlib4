class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["pin_name"])
        return akat.transform(akat.render(self, pin_name = ctx.pin_name))
