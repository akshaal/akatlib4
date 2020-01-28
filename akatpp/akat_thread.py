class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["thread_name"], optional_kvs = { "state_type": "u8"}, body = True)
        return akat.transform(akat.render(self, body = inv.body, thread_name = ctx.thread_name, state_type = ctx.state_type))
