class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_enclosing_macros = ["COROUTINE"])

        label, state = ctx.COROUTINE.alloc_label_and_state()
        return_value = ctx.COROUTINE.get_return_value()

        return akat.render(self, label = label, state = state, return_value = return_value)
