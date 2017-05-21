next_code = 0
handler_is_defined = False
codes = []

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"])

        global next_code
        next_code += 1

        codes.append(STRESS(next_code) + " - " + ctx.name)

        return akat.transform(akat.render(self, code = next_code))

    def postvalidate():
        if not handler_is_defined and next_code != 0:
            akat.fatal_error("Please define a fatal error handler. Use FATAL_ERROR_HANDLER$() macro.")

        if next_code != 0:
            akat.print_sep()
            akat.print_info("The following fatal error codes are defined:")
            for code in codes:
                akat.print_info("    " + code)
