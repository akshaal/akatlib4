AUTOGLOBAL$(${function_name}) {
    IN_GLOBAL$() {
        ${extra_attrs} static ${decl} {
            SCOPE$(${function_name}__f) {
                ${body}
            }
        }
    }
}
