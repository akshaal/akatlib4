#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/gpio_input);
X_CPU$(cpu_freq = 8000000);

X_GPIO_INPUT$(key1, D2);
X_GPIO_OUTPUT$(error_led, B0);

// Main
X_MAIN$() {
    BENCH_INIT;
    BENCH;

    BENCH;
    error_led.set(key1.is_set());
    BENCH;
    error_led.set(key1.is_set());
    BENCH;
    error_led.set(key1.is_set());
    BENCH;
    error_led.set(key1.is_set());
    BENCH;

    BENCH_EXIT;
}
