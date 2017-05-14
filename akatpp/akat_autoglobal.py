class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, body = True, allow_nesting = True)

        body = inv.body

        if akat.get_enclosing_macro_or_none("GLOBAL") == None:
            body = "GLOBAL$() {\n" + inv.body + "\n}\n"

        return akat.transform(body)
