#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/main);
X_CPU$(cpu_freq = 8000000);

// Main
X_MAIN$() {
    BENCH_INIT;
    BENCH;
    BENCH_EXIT;
}
