X_GPIO_ACCESS$(${object_name}__port, PORT, ${pin_name})
X_GPIO_ACCESS$(${object_name}__ddr, DDR, ${pin_name})
X_GPIO_ACCESS$(${object_name}__pin, PIN, ${pin_name})

X_INIT$(${object_name}__init) {
    ${object_name}__ddr.set(0);
    ${object_name}__port.set(1);
}

OBJECT$(${object_name}) {
    METHOD$(u8 is_set(), inline) {
        return ${object_name}__pin.is_set();
    }
}
