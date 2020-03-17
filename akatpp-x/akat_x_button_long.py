class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["object_name", "pin_name"], optional_kvs = {"long_press_deciseconds": 10}, body = True)
        return akat.transform(akat.render(self, object_name = ctx.object_name, pin_name = ctx.pin_name, long_press_deciseconds = ctx.long_press_deciseconds, body = inv.body))
