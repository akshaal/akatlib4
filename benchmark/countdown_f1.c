#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/countdown_f1);

X_COUNTDOWN$(c1) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
    }

    METHOD$(void on_new_second_l(), inline) {
        BENCH;
    }

    METHOD$(void on_new_minute_l(), inline) {
        BENCH;
    }

    METHOD$(void on_new_hour_l(), inline) {
        BENCH;
    }
}

// Main
X_MAIN$(cpu_freq = 1000000) {
    BENCH_INIT;
    sei();
}
