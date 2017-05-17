#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_w_kbd_tm1637_f1);

USE_REG$(tm1637__dirty);

X_TM1637$(tm1637, clk = B3, dio = B4);

X_TIMESTAMP$(t);

X_CLOCK$(c1, t);

GLOBAL$() {
    STATIC_VAR$(u32 sum);
}

X_BUTTON$(button1, D0) { sum += 100000L; }
X_BUTTON$(button2, D1) { sum += 200000L; }
X_BUTTON$(button3, D2) { sum += 400000L; }
X_BUTTON$(button4, D3) { sum += 800000L; }

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_minute_h(), inline) {
        tm1637.set_digit_pos_1(t.get_minutes_h(), 0);
    }

    METHOD$(void on_new_minute_l(), inline) {
        tm1637.set_digit_pos_2(t.get_minutes_l(), sum == 150000);
    }

    METHOD$(void on_new_second_h(), inline) {
        tm1637.set_digit_pos_3(t.get_seconds_h(), 0);
    }

    METHOD$(void on_new_second_l(), inline) {
        tm1637.set_digit_pos_4(t.get_seconds_l(), 0);
    }
}

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (t.get_seconds_l() == 3 && t.get_deciseconds() == 5) {
            BENCH_EXIT;
        }
    }

    METHOD$(void on_new_second(), inline) { BENCH; }
    METHOD$(void on_new_minute(), inline) { BENCH; }
    METHOD$(void on_new_hour(), inline) { BENCH; }
}

// Main
X_MAIN$(cpu_freq = 1000000) {
    BENCH_INIT;
    c1.start();
    sei();
}
