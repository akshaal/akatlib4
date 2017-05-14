class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["global_name", "local_name"], keywords = ["ignore_dups"], required_enclosing_macros = ["SCOPE"])
        ctx.SCOPE.map_as(ctx.global_name, ctx.local_name, ignore_dups = ctx.ignore_dups)

        return ""
