#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/delay);
X_CPU$(cpu_freq = 8000000);

// Main
X_MAIN$() {
    BENCH_INIT;
    BENCH;
    akat_delay_us(1);
    BENCH;
    akat_delay_us(10);
    BENCH;
    akat_delay_us(20);
    BENCH;
    akat_delay_us(20);
    BENCH;
    akat_delay_us(20);
    BENCH;
    BENCH_EXIT;
}
