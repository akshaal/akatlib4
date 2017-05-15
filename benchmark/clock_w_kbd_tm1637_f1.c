#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/clock_w_kbd_tm1637_f1);

USE_REG$(akat_clock_current_decisecond);
USE_REG$(akat_clock_current_second);
USE_REG$(akat_clock_current_minute);
USE_REG$(akat_clock_current_hour);

X_TM1637$(tm1637, clk = B3, dio = B4);

X_CLOCK$(tm1637_clock) {
    METHOD$(void on_new_decisecond(), inline) {
    }

    METHOD$(void on_new_second(), inline) {
        //tm1637.set_digit_pos_3(d(tm1637_clock.get_current_second()), 0);
        tm1637.set_digit_pos_4(2, 0);
    }

    METHOD$(void on_new_minute(), inline) {
        tm1637.set_digit_pos_1(3, 0);
        tm1637.set_digit_pos_2(4, 1);
    }

    METHOD$(void on_new_hour(), inline) {
    }
}

X_CLOCK$(c1) {
    METHOD$(void on_new_decisecond(), inline) {
        BENCH;
        if (c1.get_current_second() == 3 && c1.get_current_decisecond() == 5) {
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
