FUNCTION$(AKAT_NO_RETURN void main(), not_static) {
    % for r in regs:
        ${reg_to_var[r]} = ${initials[reg_to_var[r]]};
    % endfor

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
