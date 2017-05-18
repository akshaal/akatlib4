class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["dname"], optional_kvs = {"condition1": "0", "condition2": "0", "condition3": "0", "condition4": "0"})

        render_ctx = {}
        ctx.add_into(render_ctx)

        return akat.transform(akat.render(self, body = inv.body, **render_ctx))
