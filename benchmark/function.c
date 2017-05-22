#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/function);
X_CPU$(cpu_freq = 8000000);

FUNCTION$(void hello(u8 x)) {
    STATIC_VAR$(u8 y);

    FUNCTION$(void hello2(u8 x)) {
        if ((x + y) == 13) {
            BENCH;
        }
    }

    y = 10;

    hello2(x);
}

FUNCTION$(void hello2()) {
    BENCH_EXIT;
}

// Main
X_MAIN$() {
    BENCH_INIT;
    hello(3);
    hello2();
}
