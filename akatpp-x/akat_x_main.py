inits = []
runnables = []

class Macro:
    def render(self, inv):
        body = akat.transform(inv.body)

        # ----------------------- Parse arguments

        unroll = 1
        tick_period_us = 0
        cpu_freq = None

        for arg in inv.args:
            k, v = arg.split("=", 1)
            k = k.strip()
            if k == "unroll": unroll = int(v.strip())
            elif k == "cpu_freq": cpu_freq = int(v.strip())
            elif k == "tick_period_us": tick_period_us = int(v.strip())
            else: akat.fatal_error("Unknown argument: ", STRESS_COLOR, k)

        if cpu_freq == None:
            akat.fatal_error("cpu_freq is required argument!")

        # ----------------------- Configure tick (Timer0)

        cycles_per_us = cpu_freq / 1000000
        tick_prescaler = tick_period_us * cycles_per_us

        if tick_period_us == 0:      cs02, cs01, cs00 = 0, 0, 0
        elif tick_prescaler == 1:    cs02, cs01, cs00 = 0, 0, 1
        elif tick_prescaler == 8:    cs02, cs01, cs00 = 0, 1, 0
        elif tick_prescaler == 64:   cs02, cs01, cs00 = 0, 1, 1
        elif tick_prescaler == 256:  cs02, cs01, cs00 = 1, 0, 0
        elif tick_prescaler == 1024: cs02, cs01, cs00 = 1, 0, 1
        else:
            akat.fatal_error(
                "Unable to calculate Timer0 configuration for the given cpu_freq and time_period_us. Calculated tick perscaler is ",
                STRESS_COLOR, tick_prescaler, RESET_COLOR,
                ". While this one can be one of these: ",
                STRESS_COLOR, "1", RESET_COLOR, ", ",
                STRESS_COLOR, "8", RESET_COLOR, ", ",
                STRESS_COLOR, "64", RESET_COLOR, ", ",
                STRESS_COLOR, "256", RESET_COLOR, ", ",
                STRESS_COLOR, "1024", RESET_COLOR, ", "
            )

        # ----------------------- Render

        render_context = {
            "cpu_freq": cpu_freq,
            "tick_period_us": tick_period_us,
            "tick_prescaler": tick_prescaler,
            "body": body,
            "runnables": runnables,
            "inits": inits,
            "unroll": unroll,
            "cs00": cs00,
            "cs01": cs01,
            "cs02": cs02
        }

        return akat.transform(akat.render("akat_x_main.c", **render_context))
