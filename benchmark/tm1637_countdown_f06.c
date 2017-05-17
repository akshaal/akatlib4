#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/tm1637_countdown_f06);

X_TM1637$(tm1637, clk = B3, dio = B4);

X_TIMESTAMP$(t);

X_COUNTDOWN$(c, t) {
    METHOD$(void on_finish(), inline) {
        BENCH;
        BENCH_EXIT;
    }
}

X_TM1637_TIME$(tm1637_time, t, tm1637, condition = c.is_started()) {
}

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
    }
}


// Main
X_MAIN$(cpu_freq = 600000) {
    BENCH_INIT;
    t.reset();
    t.set_seconds(1, 1);
    c.start();
    sei();
}
