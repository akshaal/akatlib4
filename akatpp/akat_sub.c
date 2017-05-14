FUNCTION$(u8 ${sub_name}()) {
    COROUTINE$(need_return) {
        ${body}
    }

    akat_coroutine_state = AKAT_COROUTINE_S_START;
akat_coroutine_l_end:
    return akat_coroutine_state;
}
