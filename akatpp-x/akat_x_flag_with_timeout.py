class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["name"], required_kvs = ["timeout", "unit"])

        unit = ctx.unit
        if unit == "deciseconds" or unit == "decisecond":
            unit = "DECISECOND"
        elif unit == "seconds" or unit == "second":
            unit = "SECOND"
        elif unit == "minutes" or unit == "minute":
            unit = "MINUTE"
        elif unit == "hours" or unit == "hour":
            unit = "HOUR"
        else:
            akat.fatal_error("Unknown unit ", STRESS(unit), "... Known units are ", STRESS("(deci)second(s), minute(s), hour(s)"), "!")

        return akat.transform(akat.render(self, oname = ctx.name, unit = unit, timeout = ctx.timeout))
