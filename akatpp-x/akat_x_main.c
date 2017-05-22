AKAT_NO_RETURN void main() {
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
