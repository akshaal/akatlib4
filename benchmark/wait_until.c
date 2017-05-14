#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/wait_until);

GLOBAL$() {
    STATIC_VAR$(u8 i);
}

// Thread1
THREAD$(thread1) {
    WAIT_UNTIL$(i == 10);
    BENCH;
    BENCH_EXIT;
}

// Thread2
THREAD$(thread2) {
    while(1) {
        BENCH;
        i++;
        YIELD$();
    }
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
}
