inits = []
runnables = []

class Macro:
    def render(self, inv):
        args = akat.prepare(inv, optional_kvs = {"unroll": 1}, required_kvs = ["cpu_freq"], body = True)
        body = akat.transform(inv.body)

        render_context = {
            "body": body,
            "runnables": runnables,
            "inits": inits
        }

        args.add_into(render_context)

        return akat.transform(akat.render(self, **render_context))
