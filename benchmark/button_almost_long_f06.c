#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/button_almost_long_f06);
X_CPU$(cpu_freq = 600000);

X_BUTTON_LONG$(button, D2) {
    METHOD$(void on_long_press()) {
        x: goto x; // It's wrong to be here....
    }

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
    sei();
}
