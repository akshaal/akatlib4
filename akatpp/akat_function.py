KEYWORDS = ["inline", "not_static", "no_return", "unused", "no_inline", "const", "pure"]

tuning = {}
defined_functions = []

def tune(ctx):
    tuning[ctx.name] = ctx

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["decl"],
                           keywords = KEYWORDS,
                           body = True,
                           allow_nesting = True)

        decl = ctx.decl

        function_rettype, function_name = decl.split("(", 1)[0].strip().rsplit(" ", 1)
        function_args = "(" + decl.split("(", 1)[1]

        full_name = akat.add_namespace(function_name)

        if full_name in defined_functions:
            akat.fatal_error("This function is already defined: ", STRESS(full_name))

        defined_functions.append(full_name)

        decl = function_rettype + " " + full_name + function_args

        if full_name in tuning:
            attr_ctx = tuning[full_name]
        else:
            attr_ctx = ctx

        extra_attrs = []
        if not attr_ctx.not_static:
            extra_attrs.append("static")

        if attr_ctx.const:
            extra_attrs.append("AKAT_CONST")

        if attr_ctx.pure:
            extra_attrs.append("AKAT_PURE")

        if attr_ctx.inline:
            extra_attrs.append("AKAT_FORCE_INLINE")

        if attr_ctx.no_return:
            extra_attrs.append("AKAT_NO_RETURN")

        if attr_ctx.no_inline:
            extra_attrs.append("AKAT_NO_INLINE")

        if attr_ctx.unused:
            extra_attrs.append("AKAT_UNUSED")

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

    def postvalidate():
        # Unused tunings
        shown_unused_header = False
        for v in tuning:
            if v not in defined_functions:
                if not shown_unused_header:
                    akat.print_sep()
                    akat.print_error("Following functions are tuned but we can't find such functions! Are you sure your TUNE_FUNCTION$ goes BEFORE parts that declare the function?..")
                    shown_unused_header = True

                akat.print_error("    ", STRESS_COLOR, v)

        if shown_unused_header:
            akat.fatal_error("Please fix it!")
