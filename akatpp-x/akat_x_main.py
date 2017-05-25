import akat_static_var

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
            "inits": inits,
            "start_reg_n": akat_static_var.START_REG_N,
            "last_reg_n": akat_static_var.next_reg_n - 1,
            "start_low_reg_n": akat_static_var.START_LOW_REG_N,
            "last_low_reg_n": akat_static_var.next_low_reg_n - 1,
            "reg_to_var": akat_static_var.reg_to_var
        }

        args.add_into(render_context)
        return prerender + "\n" + akat.transform(akat.render(self, **render_context))
