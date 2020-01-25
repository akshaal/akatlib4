class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["object_name", "pin"])
        return akat.transform(akat.render(self, object_name = ctx.object_name, pin = ctx.pin))
