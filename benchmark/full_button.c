#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/full_button);

X_FULL_BUTTON$(button, D2) {
    METHOD$(void on_press()) {
        BENCH;
    }

    METHOD$(void on_release()) {
        BENCH;
        BENCH_EXIT;
    }
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
    BENCH;
}
