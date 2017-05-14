class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["global_name", "local_name"], keywords = ["ignore_dups", "allow_no_scope"])

        scope_m = akat.get_enclosing_macro_or_none("SCOPE")
        if scope_m == None:
            if not ctx.allow_no_scope:
                akat.fatal_error("No scope!")
        else:
            scope_m.map_as(ctx.global_name, ctx.local_name, ignore_dups = ctx.ignore_dups)

        return ""
