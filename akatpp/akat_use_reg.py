import akat_static_var

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], keywords = ["low"])
        return "/* Using register " + akat_static_var.configure_as_reg(ctx.name, low = ctx.low) + " for " + ctx.name + " */";
