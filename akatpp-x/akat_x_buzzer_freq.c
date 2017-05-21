static AKAT_UNUSED AKAT_PURE u16 ${oname}__get_prescaler(u16 const freq) {
    % if len(splits) == 1:
    return ${splits[1]};
    % endif

    % if len(splits) > 1:
        % for f, presc in splits[::-1]:
            if (freq >= ${f}) {
                return ${presc};
            }
        % endfor
    % endif

    X_FATAL_ERROR$("Buzzer '${oname}': Unexpected frequency that is not between ${min_freq} and ${max_freq}");
}
