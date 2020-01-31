class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["object_name"],
                           required_kvs = ["uart"],
                           optional_kvs = {"rx_buf_size": 32})

        return akat.transform(akat.render(self,
                                          object_name = ctx.object_name,
                                          uart = ctx.uart,
                                          rx_buf_size = ctx.rx_buf_size))
