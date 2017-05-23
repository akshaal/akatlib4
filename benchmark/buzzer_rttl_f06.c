#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/buzzer_rttl_f06);
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

X_BUZZER_RTTL$(
    melody,
    "d=4,o=5,b=100: 2a4, 2e, 2d#, e, 8f4."
)

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
