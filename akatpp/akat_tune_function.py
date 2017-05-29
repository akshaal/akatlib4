import akat_function

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], keywords = akat_function.KEYWORDS)

        akat_function.tune(ctx)

        return "/* TUning function " + ctx.name +  " */";
