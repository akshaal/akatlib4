inits = []
runnables = []
cpu_freq = None
prerender_hooks = []

def add_prerender_hook(hook):
    prerender_hooks.append(hook)

class Macro:
    def render(self, inv):
        args = akat.prepare(inv, optional_kvs = {"unroll": 1}, required_kvs = ["cpu_freq"], body = True)
        body = akat.transform(inv.body)

        # Setup some global info
        global cpu_freq
        cpu_freq = int(args.cpu_freq)

        # Run some hooks that might depend on cpu_freq and stuff
        prerender = "\n".join([prerender_hook() for prerender_hook in prerender_hooks])

        # Return result
        render_context = {
            "body": body,
            "runnables": runnables,
            "inits": inits
        }


        args.add_into(render_context)
        return prerender + "\n" + akat.transform(akat.render(self, **render_context))
