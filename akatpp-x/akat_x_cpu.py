__cpu_freq = None

class Macro:
    def render(self, inv):
        args = akat.prepare(inv, required_kvs = ["cpu_freq"])

        # Setup some global info
        global __cpu_freq
        __cpu_freq = int(args.cpu_freq)

        # Return result
        render_context = {}

        args.add_into(render_context)

        return akat.transform(akat.render(self, **render_context))
