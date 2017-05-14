X_GPIO_ACCESS$(${object_name}__port, PORT, ${pin_name})
X_GPIO_ACCESS$(${object_name}__ddr, DDR, ${pin_name})
X_GPIO_ACCESS$(${object_name}__pin, PIN, ${pin_name})

OBJECT$(${object_name}) {
    METHOD$(void set_input_mode(), inline) {
        ${object_name}__ddr.set(0);
        ${object_name}__port.set(1);
    }

    METHOD$(void set_output_mode(), inline) {
        ${object_name}__ddr.set(1);
    }

    METHOD$(u8 is_set(), inline) {
        return ${object_name}__pin.is_set();
    }

    METHOD$(void set(u8 state), inline) {
        ${object_name}__port.set(state);
    }
}
