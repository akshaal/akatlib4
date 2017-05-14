#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/sub);

// Thread1
THREAD$(thread1) {
    SUB$(sub1) {
        YIELD$();
        BENCH;
    }

    CALL$(sub1);
    CALL$(sub1);
    CALL$(sub1);
    CALL$(sub1);
    CALL$(sub1);
    CALL$(sub1);

    BENCH_EXIT;
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
}
