#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_w_kbd_tm1637_f1);

USE_REG$(akat_clock_current_decisecond);
//USE_REG$(akat_clock_current_second_h);
//USE_REG$(akat_clock_current_minute_h);
//USE_REG$(akat_clock_current_hour_h);
//USE_REG$(akat_clock_current_second_l);
//USE_REG$(akat_clock_current_minute_l);
//USE_REG$(akat_clock_current_hour_l);

X_TM1637$(tm1637, clk = B3, dio = B4);

X_CLOCK$(tm1637_clock) {
    METHOD$(void on_new_minute_h(), inline) {
        tm1637.set_digit_pos_1(tm1637_clock.get_current_minute_h(), 0);
    }

    METHOD$(void on_new_minute_l(), inline) {
        tm1637.set_digit_pos_2(tm1637_clock.get_current_minute_l(), 1);
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
