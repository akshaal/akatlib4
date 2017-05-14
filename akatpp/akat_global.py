class Macro:
    def __init__(self):
        self.__global_codes = []

    def add_global_code(self, code):
        self.__global_codes.append(code)

    def render(self, inv):
        ctx = akat.prepare(inv, body = True)

        body = akat.transform(inv.body)

        return akat.render(self, global_codes = self.__global_codes, body = body)
