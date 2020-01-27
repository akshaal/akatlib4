import akat_x_every_decisecond
import akat_x_main

object_names = []

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv, required_args = ["object_name", "pin"])

        object_names.append(ctx.object_name)

        first_time = len(object_names) == 1
        if first_time:
            # Add hook that will be called before 'main' function is rendered by 'akat_x_main'
            akat_x_main.add_prerender_hook(self.__main_prerender_hook)

            # Run 'ds18b20_ticker' every 0.1 second.
            akat_x_every_decisecond.funcs.append("ds18b20_ticker")

        return akat.transform(akat.render(self, object_name = ctx.object_name, pin = ctx.pin, first_time = first_time))

    def __main_prerender_hook(self):
        # This is executed by 'akat_x_main' and our output is added right before 'main' function
        # We use it too add thread which will handle temperature measurements for
        # structures declared in our own 'render' function.

        return akat.transform(akat.render("akat_x_ds18b20_thread.c", object_names = object_names))
