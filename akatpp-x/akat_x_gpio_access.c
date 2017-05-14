OBJECT$(${object_name}) {
    METHOD$(void set(u8 state), inline) {
        if (state) {
            ${reg_name} |= 1 << ${pin_idx};
        } else {
            ${reg_name} &= ~(1 << ${pin_idx});
        }
    }

    METHOD$(u8 is_set(), inline) {
        return ${reg_name} & (1 << ${pin_idx});
    }
}
