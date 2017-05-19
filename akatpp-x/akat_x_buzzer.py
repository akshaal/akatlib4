import akat_x_main

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], required_kvs = ["min_freq", "max_freq"])
        self.__ctx = ctx

        akat_x_main.add_prerender_hook(self.__main_prerender_hook)

        return ""

    def __main_prerender_hook(self):
        freq = akat_x_main.cpu_freq

        return ""
