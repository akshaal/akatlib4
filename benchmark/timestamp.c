#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/timestamp);

X_TIMESTAMP$(t_unused);
X_TIMESTAMP$(t);

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (t.get_current_second_l() == 3 && t.get_current_decisecond() == 5) {
            BENCH_EXIT;
        }
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
