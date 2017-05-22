#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/tm1637);
X_CPU$(cpu_freq = 8000000);

X_TM1637$(tm1637, clk = B3, dio = B4);

FUNCTION$(void check(u8 x)) {
    STATIC_VAR$(u8 sum);
    sum += x;

    if (sum == 15) {
        tm1637.set_digit_pos_1(1, 0);
        tm1637.set_digit_pos_2(2, 1);
        tm1637.set_digit_pos_3(3, 0);
        tm1637.set_digit_pos_4(4, 0);
    }
}

X_BUTTON$(button1, D0) { check(1); }
X_BUTTON$(button2, D1) { check(2); }
X_BUTTON$(button3, D2) { check(4); }
X_BUTTON$(button4, D3) { check(8); }

THREAD$(thread) {
    while(1) {
        BENCH;
        YIELD$();
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;
}
