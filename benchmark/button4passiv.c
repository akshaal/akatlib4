#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/button4passiv);
X_CPU$(cpu_freq = 8000000);

GLOBAL$() {
    STATIC_VAR$(u32 sum);
}

X_BUTTON$(button1, D0) { sum += 100000L; }
X_BUTTON$(button2, D1) { sum += 200000L; }
X_BUTTON$(button3, D2) { sum += 400000L; }
X_BUTTON$(button4, D3) { sum += 800000L; }

RUNNABLE$(checker) {
    if (sum == 1508000) {
        BENCH;
        BENCH_EXIT;
    }
    sum++;
}

// Main
X_MAIN$() {
    BENCH_INIT;
    BENCH;
}
