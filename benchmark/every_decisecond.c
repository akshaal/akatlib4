#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/every_decisecond);

USE_REG$(counter__i);

X_EVERY_DECISECOND$(counter) {
    STATIC_VAR$(u8 i);

    i++;
    if (i == 6) {
        BENCH_EXIT;
    }
}

X_EVERY_DECISECOND$(bench) {
    BENCH;
}


// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;

    sei();
}
