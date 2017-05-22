#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/autoglobal);

X_CPU$(cpu_freq = 8000000);

AUTOGLOBAL$() {
    AUTOGLOBAL$() {
        static void hello() {
            BENCH;

            IN_GLOBAL$() {
                static void hello2() {
                    BENCH_EXIT;
                }
            }
        }
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;
    hello();
    hello2();
}
