class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, body = True, required_enclosing_macros = ["GLOBAL"], allow_nesting = True)

        ctx.GLOBAL.add_global_code(akat.transform(inv.body))

        return ""
