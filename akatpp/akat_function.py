class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["decl"], keywords = ["inline"], body = True, allow_nesting = True)

        function_name = ctx.decl.split("(", 1)[0].strip().rsplit(" ", 1)[1]

        extra_attrs = []
        if ctx.inline:
            extra_attrs.append("AKAT_FORCE_INLINE")
        extra_attrs = " ".join(extra_attrs)

        def code_in_namespace():
            render_context = {
                "body": inv.body,
                "function_name": function_name,
                "decl": ctx.decl,
                "extra_attrs": extra_attrs
            }

            return akat.transform(akat.render(self, **render_context))

        return akat.run_with_namespace(code_in_namespace, function_name, "function")
