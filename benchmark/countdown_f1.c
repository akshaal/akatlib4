#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/countdown_f1);

USE_REG$(akat_countdown_started__c1);
USE_REG$(akat_timestamp_decisecond__t);
USE_REG$(akat_timestamp_second_h__t);
USE_REG$(akat_timestamp_second_l__t);
USE_REG$(akat_timestamp_minute_h__t);

X_TIMESTAMP$(t);

X_COUNTDOWN$(c1, t) {
    METHOD$(void on_finish(), inline) {
        BENCH;
        BENCH_EXIT;
    }
}

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_second_l(), inline) {
        BENCH;
    }
}

// Main
X_MAIN$(cpu_freq = 1000000) {
    BENCH_INIT;
    t.reset();
    t.set_seconds(0, 5);
    c1.start();
    sei();
}
