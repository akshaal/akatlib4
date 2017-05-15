#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_f1);

USE_REG$(akat_clock_current_decisecond);
USE_REG$(akat_clock_current_second_h);
USE_REG$(akat_clock_current_minute_h);
USE_REG$(akat_clock_current_hour_h);
USE_REG$(akat_clock_current_second_l);
USE_REG$(akat_clock_current_minute_l);
USE_REG$(akat_clock_current_hour_l);

X_CLOCK$(c1) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (c1.get_current_second_l() == 3 && c1.get_current_decisecond() == 5) {
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
