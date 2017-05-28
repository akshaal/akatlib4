GLOBAL$() {
    STATIC_VAR$(u8 akat_countdown_started__${oname});
}

OBJECT$(${oname}) {
    ${body}

    METHOD$(u8 is_started(), inline) {
        return akat_countdown_started__${oname};
    }

    METHOD$(void start(), inline) {
        akat_countdown_started__${oname} = AKAT_TRUE;
    }

    METHOD$(void stop(), inline) {
        akat_countdown_started__${oname} = AKAT_FALSE;
    }

    METHOD$(void on_finish(), inline, ignore_dup) {
    }
}

X_EVERY_DECISECOND$(countdown_dechandler__${oname}) {
    if (akat_countdown_started__${oname}) {
        if (${tname}.dec_deciseconds(1)) {
            ${tname}.reset();
            ${oname}.stop();
            ${oname}.on_finish();
        }
    }
}
