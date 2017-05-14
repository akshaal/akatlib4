do {
    akat_coroutine_state = ${state};
${label}:
    if (!(${cond})) {
        % if likely:
            AKAT_COLD_CODE;
        % endif

        % if unlikely:
            AKAT_HOT_CODE;
        % endif

        return ${return_value};
    }
} while(0);
