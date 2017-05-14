#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/thread_object);

THREAD$(t) {
    OBJECT$(obj1) {
        METHOD$(u8 add(u8 const a, u8 const b), inline) {
            return a + b + obj1.inc();
        }

        METHOD$(u8 inc(), inline) {
            STATIC_VAR$(u8 i);

            i++;
            if (i == 2) {
                return 10;
            } else {
                return 0;
            }
        }
    }

    BENCH;

    if (obj1.add(1, 2) == 13) {
        BENCH;
    }

    if (obj1.add(1, 2) == 13) {
        BENCH;
    }

    if (obj1.add(1, 2) == 13) {
        BENCH;
    }

    if (obj1.add(1, 2) == 13) {
        BENCH;
    }

    if (obj1.add(1, 2) == 13) {
        BENCH;
    }

    BENCH_EXIT;
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
}
