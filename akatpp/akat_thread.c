RUNNABLE$(${thread_name}) {
    COROUTINE$() {
        ${body}
    }

    akat_coroutine_state = AKAT_COROUTINE_S_END;
akat_coroutine_l_end:
    return;
}
