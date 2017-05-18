#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/button_repeat_f06);

X_BUTTON_REPEAT$(button, D2) {
    METHOD$(void on_press()) {
        BENCH;
    }

    METHOD$(void on_repeat()) {
        BENCH;
        BENCH;
    }

    METHOD$(void on_release()) {
        BENCH;
        BENCH_EXIT;
    }
}

// Main
X_MAIN$(cpu_freq = 600000) {
    BENCH_INIT;
    BENCH;
    sei();
}
