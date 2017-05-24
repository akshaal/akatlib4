FUNCTION$(AKAT_NO_RETURN void main(), not_static) {
    // TODO: INIT ALL FIXED REGS TO ZERO!!!!!!!

    asm volatile("inc r3" : "=r" (__akat_one__));

    % for init in inits:
        ${init}();
    % endfor

    // Init
    ${body}

    // Endless loop with threads, tasks and such
    while(1) {
        % for i in range(unroll):
            % for runnable in runnables:
                ${runnable}();
            % endfor
        % endfor
    }
}
