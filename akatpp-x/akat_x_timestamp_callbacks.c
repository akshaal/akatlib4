OBJECT$(${oname}__${idx}) {
    ${body}

    METHOD$(void on_new(AKAT_UNUSED akat_x_timestamp_level_t level), inline, ignore_dup) {}

    METHOD$(void on_new_decisecond(), inline, ignore_dup) {}

    METHOD$(void on_new_second_l(), inline, ignore_dup) {}
    METHOD$(void on_new_minute_l(), inline, ignore_dup) {}
    METHOD$(void on_new_hour_l(), inline, ignore_dup) {}

    METHOD$(void on_new_second_h(), inline, ignore_dup) {}
    METHOD$(void on_new_minute_h(), inline, ignore_dup) {}
    METHOD$(void on_new_hour_h(), inline, ignore_dup) {}
}
