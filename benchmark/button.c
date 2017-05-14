#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/button);

X_BUTTON$(button, D2) {
    BENCH;
    BENCH_EXIT;
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
    BENCH;
}
