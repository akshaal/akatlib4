#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/gpio_output);

X_GPIO_OUTPUT$(error_led, B0);

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
    BENCH;

    BENCH;
    error_led.set(0);
    BENCH;
    error_led.set(1);
    BENCH;
    error_led.set(0);
    BENCH;
    error_led.set(1);
    BENCH;

    BENCH_EXIT;
}
