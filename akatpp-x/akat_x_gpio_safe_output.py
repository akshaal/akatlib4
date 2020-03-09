# Like X_GPIO_OUTPUT$ but times out if state is not updated within state_timeout_deciseconds.
# If timeout happens, then the state of pin is set to 'safe_state'

class Macro:
    def render(self, inv):
        ctx = akat.prepare(inv,
                           required_args = ["object_name", "pin_name"],
                           required_kvs = ["safe_state", "state_timeout_deciseconds"])

        rendered = akat.render(self,
                               object_name = ctx.object_name,
                               pin_name = ctx.pin_name,
                               safe_state = ctx.safe_state,
                               state_timeout_deciseconds = ctx.state_timeout_deciseconds)

        return akat.transform(rendered)
