from mako.template import Template

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], allow_any_optional = True, body = True)

        prep_args = {}
        ctx.add_into(prep_args)
        del prep_args["name"]
        template = Template(inv.body)

        for k in prep_args:
            prep_args[k] = eval(prep_args[k])

        class NewMacro:
            def render(self, inv):
                print(prep_args)
                ctx = akat.prepare(inv, **prep_args)

                render_ctx = {}
                ctx.add_into(render_ctx)

                return akat.transform(template.render(**render_ctx))

        name = inv.args[0]
        NewMacro.name = name

        akat.add_macro(name, NewMacro)

        return "/* Defined new macro with name " + name + "  */"
