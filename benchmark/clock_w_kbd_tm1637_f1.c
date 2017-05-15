#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_w_kbd_tm1637_f1);

USE_REG$(tm1637__dirty);
USE_REG$(akat_clock_current_decisecond);
USE_REG$(akat_clock_current_second_l);
//USE_REG$(akat_clock_current_second_h);
//USE_REG$(akat_clock_current_minute_l);
//USE_REG$(akat_clock_current_minute_h);
//USE_REG$(akat_clock_current_hour_h, low);
//USE_REG$(akat_clock_current_hour_l, low);

X_TM1637$(tm1637, clk = B3, dio = B4);

GLOBAL$() {
    STATIC_VAR$(u32 sum);
}

X_BUTTON$(button1, D0) { sum += 100000L; }
X_BUTTON$(button2, D1) { sum += 200000L; }
X_BUTTON$(button3, D2) { sum += 400000L; }
X_BUTTON$(button4, D3) { sum += 800000L; }

X_CLOCK$(tm1637_clock) {
    METHOD$(void on_new_minute_h(), inline) {
        tm1637.set_digit_pos_1(tm1637_clock.get_current_minute_h(), 0);
    }

    METHOD$(void on_new_minute_l(), inline) {
        tm1637.set_digit_pos_2(tm1637_clock.get_current_minute_l(), sum == 150000);
    }

    METHOD$(void on_new_second_h(), inline) {
        tm1637.set_digit_pos_3(tm1637_clock.get_current_second_h(), 0);
    }

    METHOD$(void on_new_second_l(), inline) {
        tm1637.set_digit_pos_4(tm1637_clock.get_current_second_l(), 0);
    }
}

X_CLOCK$(c1) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (c1.get_current_second_l() == 3 && c1.get_current_decisecond() == 5) {
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
    sei();
}
