GLOBAL$() {
    STATIC_VAR$(u8 akat_clock_started__${oname});
}

OBJECT$(${oname}) {
    ${body}

    METHOD$(u8 is_started(), inline) {
        return akat_clock_started__${oname};
    }

    METHOD$(void start(), inline) {
        akat_clock_started__${oname} = 1;
    }

    METHOD$(void stop(), inline) {
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
