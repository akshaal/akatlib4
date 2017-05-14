do {
    akat_coroutine_state = ${state};
${label}:
    if (${sub_name}() != AKAT_COROUTINE_S_START) {
        return ${return_value};
    }
} while(0);
