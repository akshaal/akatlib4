class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["thread_name"], body = True)
        return akat.transform(akat.render(self, body = inv.body, thread_name = ctx.thread_name))
