class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], body = True, allow_nesting = True)

        body = inv.body

        if akat.get_enclosing_macro_or_none("GLOBAL") == None:
            body = "GLOBAL$(" + ctx.name + ") {\n" + inv.body + "\n}\n"

        return akat.transform(body)
