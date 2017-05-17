OBJECT$(${oname}) {
    ${body}
}

X_EVERY_DECISECOND$(clock_dechandler__${oname}) {
    ${tname}.inc_deciseconds();
}
