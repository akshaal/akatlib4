class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["oname", "dname"])

        render_ctx = {}
        ctx.add_into(render_ctx)

        return akat.transform(akat.render(self, body = inv.body, **render_ctx))
