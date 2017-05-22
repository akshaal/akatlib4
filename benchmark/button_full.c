#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/button_full);
X_CPU$(cpu_freq = 8000000);

X_BUTTON_FULL$(button, D2) {
    METHOD$(void on_press()) {
        BENCH;
    }

    METHOD$(void on_release()) {
        BENCH;
        BENCH_EXIT;
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;
    BENCH;
}
