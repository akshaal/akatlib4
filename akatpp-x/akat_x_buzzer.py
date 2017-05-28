class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["oname"], keywords = ["no_callbacks"])

        mcu = akat.get_param("MCU")
        if mcu == "attiny2313":
            pin = "B2"
        elif mcu == "attiny85":
            pin = "B0"
        elif mcu == "atmega16":
            pin = "B3"
        elif mcu == "atmega32":
            pin = "B3"
        elif mcu == "atmega48":
            pin = "D6"
        else:
            akat.fatal_error("Please fix ", STRESS("akat_x_buzzer"), " to add support for this platform: ", STRESS(mcu))

        render_ctx = {"pin": pin}
        ctx.add_into(render_ctx)

        return akat.transform(akat.render(self, **render_ctx))
