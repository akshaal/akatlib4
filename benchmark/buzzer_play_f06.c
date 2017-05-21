#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/buzzer_play_f06);

X_FATAL_ERROR_HANDLER$() {
    BENCH;
    akat_delay_us(10);
    BENCH;
    for (u8 i = 0; i < code; i++) {
        BENCH;
    }
    BENCH_EXIT;
    while(1) {};
}

X_BUZZER$(b, min_freq = 1000, max_freq = 15000);

static PROGMEM akat_x_buzzer_sound_t const melody[] = {{.deciseconds = 0, .prescaler = 0, .ocr = 0}};

// Main
X_MAIN$(cpu_freq = 600000) {
    BENCH_INIT;
    sei();
    b.play(melody);
}
