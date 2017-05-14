class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["object_name", "reg_name", "pin_name"])

        reg_name = ctx.reg_name + ctx.pin_name[0]
        pin_idx = ctx.pin_name[1:]

        return akat.transform(akat.render(self, object_name = ctx.object_name, pin_name = ctx.pin_name, reg_name = reg_name, pin_idx = pin_idx))
