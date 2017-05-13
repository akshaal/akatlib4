class Macro:
    def __init__(self):
        self.__global_codes = []

    def add_global_code(self, code):
        self.__global_codes.append(code)

    def render(self, inv):
        akat.prepare(inv, body = True)
        return akat.render(self, body = akat.transform(inv.body), global_codes = self.__global_codes)
