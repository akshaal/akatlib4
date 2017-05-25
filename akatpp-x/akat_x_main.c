FUNCTION$(AKAT_NO_RETURN void main(), not_static) {
    % for i in range(start_low_reg_n, last_low_reg_n + 1):
        ${reg_to_var["r" + str(i)]} = 0;
    % endfor

    % for i in range(start_reg_n, last_reg_n + 1):
        ${reg_to_var["r" + str(i)]} = 0;
    % endfor

    __akat_one__++; // Set it to one

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
