OBJECT$(${oname}__${idx}) {
    ${body}

    METHOD$(void on_new(AKAT_UNUSED akat_x_timestamp_level_t level), inline, ignore_dup) {}

    METHOD$(void on_new_decisecond(), inline, ignore_dup) {}
    METHOD$(void on_new_minute(), inline, ignore_dup) {}
    METHOD$(void on_new_second(), inline, ignore_dup) {}
    METHOD$(void on_new_hour(), inline, ignore_dup) {}
}
