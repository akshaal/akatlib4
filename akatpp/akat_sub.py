class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["sub_name"], body = True)
        return akat.transform(akat.render(self, body = inv.body, sub_name = ctx.sub_name))
