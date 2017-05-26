class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["decl"],
                           body = True,
                           allow_nesting = True,
                           keywords = ["inline", "ignore_dup", "no_inline"],
                           required_enclosing_macros = ["OBJECT"])

        decl = ctx.decl

        method_type, method_name = decl.split("(", 1)[0].strip().rsplit(" ")
        ret_type = method_type.strip()
        method_args = decl.split("(", 1)[1].rsplit(")", 1)[0].strip()

        if ctx.OBJECT.has_method(method_name):
            if ctx.ignore_dup:
                return ""
            else:
                akat.fatal_error("Method with name ", STRESS(method_name), " is already defined!")

        extra_f_attrs = []
        if ctx.inline: extra_f_attrs.append("inline")
        if ctx.no_inline: extra_f_attrs.append("no_inline")

        render_context = {
            "extra_f_attrs": (len(extra_f_attrs) > 0 and (", " + ", ".join(extra_f_attrs)) or ""),
            "name": method_name,
            "ret_type": ret_type,
            "args": method_args,
            "impl_name": method_name + "__impl",
            "body": inv.body
        }

        render_context["body"] = akat.render(self, **render_context)

        ctx.OBJECT.add_method(Struct(**render_context))

        return ""
