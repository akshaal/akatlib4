#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/buzzer);

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

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;

    b.set_freq(16000);

    sei();

    for (u8 i = 0; i < 255; i++) {
        akat_delay_us(30);
    }

    BENCH_EXIT;
}
