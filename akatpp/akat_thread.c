RUNNABLE$(${thread_name}) {
    COROUTINE$(state_type = ${state_type}) {
        ${body}
    }

    akat_coroutine_state = AKAT_COROUTINE_S_END;
akat_coroutine_l_end:
    return;
}
