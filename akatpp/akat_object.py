class Macro:
    def __init__(self):
        self.__methods = []
        self.__method_names = []

    def add_method(self, m):
        self.__methods.append(m)
        self.__method_names.append(m.name)

    def has_method(self, name):
        return name in self.__method_names

    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], body = True, allow_nesting = True)

        body_tr = akat.transform(inv.body).replace("\n", "").strip()
        if body_tr != "":
            akat.fatal_error("Body of the object produced strange code: ", STRESS(body_tr))

        object_name = ctx.name
        ns_object_name = akat.add_namespace(object_name)

        render_context = {
            "object_name": object_name,
            "ns_object_name": ns_object_name,
            "methods": self.__methods
        }

        rendered_code = akat.render(self, **render_context)
        return akat.transform(rendered_code)
