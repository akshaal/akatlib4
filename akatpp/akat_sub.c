FUNCTION$(u8 ${sub_name}()) {
    COROUTINE$(need_return, state_type = ${state_type}) {
        ${body}
    }

    akat_coroutine_state = AKAT_COROUTINE_S_START;
akat_coroutine_l_end:
    return akat_coroutine_state;
}
