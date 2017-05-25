FUNCTION$(AKAT_NO_RETURN void main(), not_static) {
    % for r in regs:
        % if reg_to_var[r] != "__akat_one__" and initials[reg_to_var[r]].strip() == "1":
            ${reg_to_var[r]} = __akat_one__;
        % else:
            ${reg_to_var[r]} = ${initials[reg_to_var[r]]};
        % endif
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
