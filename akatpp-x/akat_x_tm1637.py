class Macro:
    name = "X_TM1637"

    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["object_name"], required_kvs = ["clk", "dio"], optional_kvs = {"delay_us": 5})

        # Parse arguments
        object_name = ctx.object_name
        clk_pin = ctx.clk
        dio_pin = ctx.dio
        delay_us = int(ctx.delay_us)

        if clk_pin == None:
            akat.fatal_error("Please provide ", STRESS_COLOR, "clk", RESET_COLOR, " argument")

        if dio_pin == None:
            akat.fatal_error("Please provide ", STRESS_COLOR, "dio", RESET_COLOR, " argument")

        # --------------------------- RENDER

        def code_in_namespace():
            ctx = {
                "object_name": object_name,
                "clk_pin": clk_pin,
                "dio_pin": dio_pin,
                "delay_us": delay_us
            }

            return akat.transform(akat.render("akat_x_tm1637.c", **ctx))

        return akat.run_with_namespace(code_in_namespace, object_name, "tm1637")
