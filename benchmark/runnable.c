#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/runnable);

USE_REG$(r2__i);

RUNNABLE$(r1) {
    BENCH;
}

RUNNABLE$(r2) {
    STATIC_VAR$(u8 i);
    if (i++ == 10) {
        BENCH_EXIT;
    }
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
}
