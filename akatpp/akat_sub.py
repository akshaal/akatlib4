class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["sub_name"], optional_kvs = { "state_type": "u8"}, body = True, allow_nesting = True)
        return akat.transform(akat.render(self, body = inv.body, sub_name = ctx.sub_name, state_type = ctx.state_type))
