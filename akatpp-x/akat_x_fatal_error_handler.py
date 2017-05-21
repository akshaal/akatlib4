import akat_x_fatal_error

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, body = True)

        if akat_x_fatal_error.handler_is_defined:
            akat.fatal_errlr("Error handler is already defined!")

        akat_x_fatal_error.handler_is_defined = True

        return akat.transform(akat.render(self, body = inv.body))
