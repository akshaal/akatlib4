#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/buzzer_notes_f06);
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

X_BUZZER$(b);

X_BUZZER_SOUNDS$(
    melody,
    sounds = (
        1 @ C8,
        2 @ GS2,
        1 @ B3))

// Main
X_MAIN$() {
    FUNCTION$(void on_finish(u8 AKAT_UNUSED interrupted)) {
        BENCH;
        BENCH_EXIT;
    }

    BENCH_INIT;
    BENCH;
    sei();
    b.play(melody, on_finish);
}
