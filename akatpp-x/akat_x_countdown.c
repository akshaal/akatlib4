GLOBAL$() {
    STATIC_VAR$(u8 akat_countdown_started__${oname});
}

OBJECT$(${oname}) {
    ${body}

    METHOD$(u8 is_started(), inline) {
        return akat_countdown_started__${oname};
    }

    METHOD$(void start(), inline) {
        akat_countdown_started__${oname} = 1;
    }

    METHOD$(void stop(), inline) {
        akat_countdown_started__${oname} = 0;
    }

    METHOD$(void on_finish(), inline, ignore_dup) {
    }
}

X_EVERY_DECISECOND$(countdown_dechandler__${oname}) {
    if (akat_countdown_started__${oname}) {
        if (${tname}.dec_deciseconds()) {
            ${tname}.reset();
            ${oname}.stop();
            ${oname}.on_finish();
        }
    }
}
