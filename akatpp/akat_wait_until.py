class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["cond"], keywords = ["likely", "unlikely"], required_enclosing_macros = ["COROUTINE"])

        if ctx.likely and ctx.unlikely:
            akat.fatal_error("It can't be both likely and unlikely!")

        label, state = ctx.COROUTINE.alloc_label_and_state()
        return_value = ctx.COROUTINE.get_return_value()

        return akat.render(self, label = label, state = state, return_value = return_value, cond = ctx.cond, likely = ctx.likely, unlikely = ctx.unlikely)
