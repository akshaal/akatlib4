#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_f1);

USE_REG$(akat_clock_started__c1);
USE_REG$(akat_timestamp_decisecond__t);
USE_REG$(akat_timestamp_second_h__t);
USE_REG$(akat_timestamp_second_l__t);
USE_REG$(akat_timestamp_minute_h__t);

X_TIMESTAMP$(t);

X_CLOCK$(c1, t);

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (t.get_seconds_l() == 3 && t.get_deciseconds() == 5) {
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
    c1.start();
    sei();
}
