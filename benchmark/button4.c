#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/button4);
X_CPU$(cpu_freq = 8000000);

USE_REG$(check__sum)

FUNCTION$(void check(u8 x)) {
    STATIC_VAR$(u8 sum);

    BENCH;

    sum += x;
    if (sum == 15) {
        BENCH_EXIT;
    }
}

X_BUTTON$(button1, D0) { check(1); }
X_BUTTON$(button2, D1) { check(2); }
X_BUTTON$(button3, D2) { check(4); }
X_BUTTON$(button4, D3) { check(8); }

// Main
X_MAIN$() {
    BENCH_INIT;
    BENCH;
}
