class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, body = True, keywords = ["need_return"], allow_nesting = True)
        self.__goto_cases = []
        self.__next_state = 2
        self.__need_return = ctx.need_return

        # We have to do it in 2 steps because goto cases are populated during transformation

        rendered_code = akat.transform(akat.render(self, body = inv.body))
        goto_cases = "\n".join(self.__goto_cases)

        return rendered_code.replace("__AKAT_GOTO_CASES__", goto_cases)

    def get_return_value(self):
        if self.__need_return:
            return "akat_coroutine_state"
        else:
            return ""

    def alloc_label_and_state(self):
        state = str(self.__next_state)
        label = "akat_coroutine_l_" + state

        self.__goto_cases.append("case " + state + ": goto " + label + ";")

        self.__next_state += 1

        return label, state
