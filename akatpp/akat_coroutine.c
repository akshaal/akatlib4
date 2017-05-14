STATIC_VAR$(u8 akat_coroutine_state);

AKAT_HOT_CODE;

switch(akat_coroutine_state) {
case AKAT_COROUTINE_S_START: goto akat_coroutine_l_start;
case AKAT_COROUTINE_S_END: goto akat_coroutine_l_end;
    __AKAT_GOTO_CASES__
}

akat_coroutine_l_start:

AKAT_COLD_CODE;

do {
    ${body}
} while(0);

AKAT_COLD_CODE;

