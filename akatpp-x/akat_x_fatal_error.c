IN_GLOBAL$() {
    % if first:
    static AKAT_NO_RETURN void akat_x__fatal_error__(u8 const code);
    % endif
}

akat_x__fatal_error__(${code});
