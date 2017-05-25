class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["gpio_name"])
        return akat.transform(akat.render(self, gpio_name = ctx.gpio_name))
