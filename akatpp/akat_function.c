AUTOGLOBAL$() {
    IN_GLOBAL$() {
        ${extra_attrs} ${decl} {
            SCOPE$(${function_name}) {
                ${body}
            }
        }
    }
}
