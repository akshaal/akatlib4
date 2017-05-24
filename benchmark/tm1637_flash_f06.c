#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/tm1637_flash_f06);
X_CPU$(cpu_freq = 600000);

USE_REG$(tm1637__dirty);

X_TM1637$(tm1637, clk = B3, dio = B4);

X_TM1637_FLASH$(tm1637_flash, tm1637);

GLOBAL$() {
    STATIC_VAR$(u8 x);
}

X_EVERY_DECISECOND$(thread) {
    BENCH;

    if (x == 10) {
        tm1637_flash.stop_pos_1();
        tm1637_flash.stop_pos_3();
        tm1637_flash.start_pos_2();
        tm1637_flash.start_pos_4();
    }

    if (x == 15) {
        tm1637_flash.stop_pos_2();
        tm1637_flash.stop_pos_4();
    }

    if (x++ == 30) {
        BENCH_EXIT;
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;

    tm1637.set_digit_pos_1(1, 0);
    tm1637.set_digit_pos_2(2, 0);
    tm1637.set_digit_pos_3(3, 0);
    tm1637.set_digit_pos_4(4, 0);

    tm1637_flash.start_pos_1();
    tm1637_flash.start_pos_3();

    sei();
}
