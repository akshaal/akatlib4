class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["decl"],
                           body = True,
                           allow_nesting = True,
                           keywords = ["inline"],
                           required_enclosing_macros = ["OBJECT"])

        decl = ctx.decl

        method_type, method_name = decl.split("(", 1)[0].strip().rsplit(" ")
        ret_type = method_type.strip()
        method_args = decl.split("(", 1)[1].rsplit(")", 1)[0].strip()

        render_context = {
            "extra_f_attrs": (ctx.inline and ", inline" or ""),
            "name": method_name,
            "ret_type": ret_type,
            "args": method_args,
            "impl_name": method_name + "__impl",
            "body": inv.body
        }

        render_context["body"] = akat.render(self, **render_context)

        ctx.OBJECT.add_method(Struct(**render_context))

        return ""
