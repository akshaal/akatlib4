class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["interval"])

        intervals = ["15ms", "30ms", "60ms", "120ms", "250ms", "500ms", "1s", "2s", "4s", "8s"]

        interval = ctx.interval

        if interval not in intervals:
            akat.fatal_error("Unknown interval: ", STRESS(interval), " Allowed intervals are: ", ", ".join(intervals))

        interval = interval.upper()

        return akat.transform(akat.render(self, interval = interval))
