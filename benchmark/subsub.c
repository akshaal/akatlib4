#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/subsub);
X_CPU$(cpu_freq = 8000000);

// Thread1
THREAD$(thread1) {
    SUB$(sub) {
        SUB$(sub) {
            BENCH;
        }

        CALL$(sub);
        CALL$(sub);
        CALL$(sub);
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
