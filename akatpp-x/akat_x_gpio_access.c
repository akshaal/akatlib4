OBJECT$(${object_name}) {
    METHOD$(void set(u8 state), inline) {
        if (state) {
            ${reg_name} |= 1 << ${pin_idx};  // Set ${reg_name} of ${pin_name} to 1
        } else {
            ${reg_name} &= ~(1 << ${pin_idx});  // Set ${reg_name} of ${pin_name} to 0
        }
    }

    METHOD$(u8 is_set(), inline) {
        return ${reg_name} & (1 << ${pin_idx});  // Get value of ${reg_name} for ${pin_name}
    }
}
