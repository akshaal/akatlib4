FUNCTION$(AKAT_NO_RETURN void main(), not_static) {
    // TODO: INIT ALL FIXED REGS TO ZERO!!!!!!!

    // TODO: Play a bit more here and see if wee benefit from having it like __akat__one__ = 1 or like this...
    __akat_one__++;

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
