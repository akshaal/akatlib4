AUTOGLOBAL$() {
    IN_GLOBAL$() {
        ${extra_attrs} static ${decl} {
            SCOPE$(${function_name}) {
                ${body}
            }
        }
    }
}
