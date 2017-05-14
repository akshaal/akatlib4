#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/thread);

USE_REG$(thread1__akat_coroutine_state);
USE_REG$(thread2__akat_coroutine_state);
USE_REG$(thread3__akat_coroutine_state);
USE_REG$(thread4__akat_coroutine_state);
USE_REG$(thread5__akat_coroutine_state);
USE_REG$(thread5__i);

// Thread1
THREAD$(thread1) {
    while(1) {
        BENCH;
        YIELD$();
    }
}

// Thread2
THREAD$(thread2) {
    while(1) {
        BENCH;
        YIELD$();
    }
}

// Thread3
THREAD$(thread3) {
    while(1) {
        BENCH;
        YIELD$();
    }
}

// Thread4
THREAD$(thread4) {
    while(1) {
        BENCH;
        YIELD$();
    }
}

// Thread5
THREAD$(thread5) {
    STATIC_VAR$(u8 i);

    for (i = 0; i < 5; i++) {
        YIELD$();
    }

    BENCH_EXIT;
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
}
