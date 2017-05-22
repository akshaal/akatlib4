inits = []
runnables = []
prerender_hooks = []

def add_prerender_hook(hook):
    prerender_hooks.append(hook)

class Macro:
    def render(self, inv):
        args = akat.prepare(inv, optional_kvs = {"unroll": 1}, body = True)

        # Run some hooks that might depend on stuff
        prerender = "\n".join([prerender_hook() for prerender_hook in prerender_hooks])

        # Return result
        render_context = {
            "body": inv.body,
            "runnables": runnables,
            "inits": inits
        }

        args.add_into(render_context)
        return prerender + "\n" + akat.transform(akat.render(self, **render_context))
