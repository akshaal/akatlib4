static AKAT_FORCE_INLINE AKAT_CONST AKAT_PURE uint32_t akat_cpu_freq_hz() {
    return ${cpu_freq};
}

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
