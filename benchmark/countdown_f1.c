#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/countdown_f1);
X_CPU$(cpu_freq = 1000000);

USE_REG$(akat_countdown_started__c1);
USE_REG$(akat_timestamp_decisecond__t);
USE_REG$(akat_timestamp_second__t);
USE_REG$(akat_timestamp_minute__t);

X_TIMESTAMP$(t);

X_COUNTDOWN$(c1, t) {
    METHOD$(void on_finish(), inline) {
        BENCH;
        BENCH_EXIT;
    }
}

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_second(), inline) {
        BENCH;
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;
    t.reset();
    t.set_bcd_seconds(AKAT_BCD(0, 5));
    c1.start();
    sei();
}
