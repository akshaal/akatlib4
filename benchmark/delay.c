#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/delay);

// Main
X_MAIN$(cpu_freq = 8000000) {
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
