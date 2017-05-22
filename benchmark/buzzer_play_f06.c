#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/buzzer_play_f06);
X_CPU$(cpu_freq = 600000);

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

X_BUZZER_SOUNDS$(b, melody, sounds = (3@1000, 2@1500))

// Main
X_MAIN$() {
    BENCH_INIT;
    sei();
    b.play(melody);
}
