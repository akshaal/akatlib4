# ABC means Automatic Baseline Correction

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["object_name"],
                           required_kvs = ["uart"],
                           optional_kvs = {"rx_buf_size": 32, "use_abc": 0, "debug": None})

        return akat.transform(akat.render(self,
                                          object_name = ctx.object_name,
                                          uart = ctx.uart,
                                          rx_buf_size = ctx.rx_buf_size,
                                          use_abc = ctx.use_abc,
                                          debug = ctx.debug))
