GLOBAL$() {
    STATIC_VAR$(u8 akat_clock_started__${oname});
}

OBJECT$(${oname}) {
    ${body}

    METHOD$(void start()) {
        akat_clock_started__${oname} = 1;
    }

    METHOD$(void stop()) {
        akat_clock_started__${oname} = 0;
    }

    METHOD$(void on_overflow(), inline, ignore_dup) {
    }
}

X_EVERY_DECISECOND$(clock_dechandler__${oname}) {
    if (akat_clock_started__${oname}) {
        if (${tname}.inc_deciseconds()) {
            ${oname}.on_overflow();
        }
    }
}
