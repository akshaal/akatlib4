class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name", "tname", "dname"], required_kvs = ["condition"], body = "")
        return akat.transform(akat.render(self, body = inv.body, oname = ctx.name, tname = ctx.tname, condition = ctx.condition))
