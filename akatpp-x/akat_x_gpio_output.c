X_GPIO_ACCESS$(${object_name}__port, PORT, ${pin_name})
X_GPIO_ACCESS$(${object_name}__ddr, DDR, ${pin_name})

X_INIT$(${object_name}__init) {
    ${object_name}__ddr.set(1); // Init ${pin_name} as output
}

OBJECT$(${object_name}) {
    METHOD$(void set(u8 state), inline) {
        ${object_name}__port.set(state);
    }
}
