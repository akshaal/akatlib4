GLOBAL$() {
    STATIC_VAR$(u8 akat_clock_started__${oname});
}

OBJECT$(${oname}) {
    ${body}

    METHOD$(u8 is_started(), inline) {
        return akat_clock_started__${oname};
    }

    METHOD$(void start(), inline) {
        akat_clock_started__${oname} = AKAT_TRUE;
    }

    METHOD$(void stop(), inline) {
        akat_clock_started__${oname} = AKAT_FALSE;
    }

    METHOD$(void on_overflow(), inline, ignore_dup) {
    }
}

X_EVERY_DECISECOND$(clock_dechandler__${oname}) {
    if (akat_clock_started__${oname}) {
        if (${tname}.inc_deciseconds(1)) {
            ${oname}.on_overflow();
        }
    }
}
