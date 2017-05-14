#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/global);

GLOBAL$(g1) {
    static void hello() {
        BENCH;

        IN_GLOBAL$() {
            static void hello2() {
                BENCH_EXIT;
            }
        }
    }
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
    hello();
    hello2();
}
