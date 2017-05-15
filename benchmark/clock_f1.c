#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_f1);

USE_REG$(akat_clock_current_decisecond);
USE_REG$(akat_clock_current_second);
USE_REG$(akat_clock_current_minute);
USE_REG$(akat_clock_current_hour);

X_CLOCK$(c1) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (c1.get_current_second() == 3 && c1.get_current_decisecond() == 5) {
            BENCH_EXIT;
        }
    }

    METHOD$(void on_new_second(), inline) {
        BENCH;
    }

    METHOD$(void on_new_minute(), inline) {
        BENCH;
    }

    METHOD$(void on_new_hour(), inline) {
        BENCH;
    }
}

// Main
X_MAIN$(cpu_freq = 1000000) {
    BENCH_INIT;
    sei();
}
