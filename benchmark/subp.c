#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/subp);
X_CPU$(cpu_freq = 8000000);

THREAD$(thread1) {
    SUB$(sub2) {
        BENCH;
    }

    SUB$(sub) {
        CALL$(sub2);
        CALL$(sub2);
        CALL$(sub2);
    }

    BENCH;

    CALL$(sub);
    CALL$(sub);
    CALL$(sub);

    BENCH;

    BENCH_EXIT;
}

// Main
X_MAIN$() {
    BENCH_INIT;
}
