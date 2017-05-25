class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["decl"], keywords = ["inline", "not_static", "no_return"], body = True, allow_nesting = True)

        decl = ctx.decl

        function_rettype, function_name = decl.split("(", 1)[0].strip().rsplit(" ", 1)
        function_args = "(" + decl.split("(", 1)[1]

        full_name = akat.add_namespace(function_name)

        decl = function_rettype + " " + full_name + function_args

        extra_attrs = []
        if not ctx.not_static:
            extra_attrs.append("static")

        if ctx.inline:
            extra_attrs.append("AKAT_FORCE_INLINE")

        if ctx.no_return:
            extra_attrs.append("AKAT_NO_RETURN")

        extra_attrs = " ".join(extra_attrs)

        scope_m = akat.get_enclosing_macro_or_none("SCOPE")
        if scope_m != None:
            scope_m.map_as(full_name, function_name)

        render_context = {
            "body": inv.body,
            "function_name": function_name,
            "decl": decl,
            "extra_attrs": extra_attrs
        }

        return akat.transform(akat.render(self, **render_context))
