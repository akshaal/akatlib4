X_BUZZER_SOUNDS$(
    ${oname},
    sounds = (
        % for sound in sounds:
            ${sound}${not loop.last and "," or ""}
        % endfor
    )
);
