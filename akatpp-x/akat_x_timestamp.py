# list per object name
callbacks = {}

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"])

        callbacks[ctx.name] = []

        return akat.transform(akat.render(self, oname = ctx.name))

    def postvalidate():
        for name in callbacks:
            def def_cbk_caller(kind):
                print("\nstatic void akat_timestamp_on_new_" + kind + "__" + name + "() {")
                for obj in callbacks[name]:
                    print("    " + obj + ".on_new_" + kind + "();")
                    print("    " + obj + ".on_new(AKAT_X_TIMESTAMP_LEVEL_" + kind.upper() + ");")
                print("}")

            def_cbk_caller("decisecond")
            def_cbk_caller("second")
            def_cbk_caller("minute")
            def_cbk_caller("hour")
