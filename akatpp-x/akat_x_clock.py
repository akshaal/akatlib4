objs = []

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], body = True)

        objs.append(ctx.name)

        first_time = len(objs) == 1

        return akat.transform(akat.render(self, body = inv.body, oname = ctx.name, first_time = first_time))

    def postvalidate():
        def dump_def(kind):
            print("\nstatic AKAT_FORCE_INLINE void akat_call_on_new_" + kind + "() {")
            for obj in objs:
                print("    " + obj + ".on_new_" + kind + "();")
            print("}")

        dump_def("decisecond")
        dump_def("second_l")
        dump_def("second_h")
        dump_def("minute_l")
        dump_def("minute_h")
        dump_def("hour_l")
        dump_def("hour_h")
