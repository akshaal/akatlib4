#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/define_macro);
X_CPU$(cpu_freq = 8000000);

DEFINE_MACRO$(XXX, required_args = ["count"]) {
    % for i in range(int(count)):
        BENCH;
    % endfor
}

// Main
X_MAIN$() {
    BENCH_INIT;
    XXX$(4);
    BENCH_EXIT;
}
