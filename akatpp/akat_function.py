class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["decl"], keywords = ["inline"], body = True, allow_nesting = True)

        function_name = ctx.decl.split("(", 1)[0].strip().rsplit(" ", 1)[1]

        def code_in_namespace():
            rendered_body = akat.transform(inv.body)

            render_context = {
                "rendered_body": rendered_body,
                "function_name": function_name
            }

            return akat.transform(akat.render(self, **render_context))

        return akat.run_with_namespace(code_in_namespace, function_name, "function")
