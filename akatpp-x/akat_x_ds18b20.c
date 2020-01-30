// Read temperature from DS18B20.
// DS18B20 is supposed to be connected to the given port and must be properly powered.
// (parasitic powering mode is not supported/tested).
// DS18B20 must be the only device connected to the pin because we use SKIP-ROM command.

% if first_time:
static void ds18b20_ticker();
% endif

X_GPIO_INPUT_OUTPUT$(${object_name}__pin, ${pin});

X_INIT$(${object_name}__init) {
    // Safe state - input
    ${object_name}__pin.set_input_mode();
}

// Static variable for communication between our thread and other parts of code
GLOBAL$() {
    // Whether reset procedure detect presence pulse or not
    STATIC_VAR$(u8 ${object_name}__connected, initial = 0);

    // Last received byte
    STATIC_VAR$(u8 ${object_name}__received_byte, initial = 0);

    // Last scratchpad
    STATIC_VAR$(u8 ${object_name}__scratchpad[9], initial = {});

    // Statistics
    STATIC_VAR$(u8 ${object_name}__updated_deciseconds_ago, initial = 255);
    STATIC_VAR$(u8 ${object_name}__crc_errors, initial = 0);
    STATIC_VAR$(u8 ${object_name}__disconnects, initial = 0);

    // Temperature (must be divided by 16 to convert to degrees)
    STATIC_VAR$(u16 ${object_name}__temperatureX16, initial = 0);
}

X_EVERY_DECISECOND$(${object_name}__ticker) {
    // Maintain freshness
    ${object_name}__updated_deciseconds_ago += AKAT_ONE;
    if (!${object_name}__updated_deciseconds_ago) {
        // We can't go beyond 255
        ${object_name}__updated_deciseconds_ago -= AKAT_ONE;
    }
}

OBJECT$(${object_name}) {
    METHOD$(u8 get_updated_deciseconds_ago(), inline) {
        return ${object_name}__updated_deciseconds_ago;
    }

    METHOD$(u8 get_disconnects(), inline) {
        return ${object_name}__disconnects;
    }

    METHOD$(u8 get_crc_errors(), inline) {
        return ${object_name}__crc_errors;
    }

    METHOD$(u16 get_temperatureX16(), inline) {
        return ${object_name}__temperatureX16;
    }
}
