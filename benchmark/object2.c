#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/object2);
X_CPU$(cpu_freq = 8000000);

USE_REG$(obj1__inc__impl__i);

OBJECT$(obj1) {
    METHOD$(u8 add(u8 const a, u8 const b), inline) {
        return a + b + obj1.inc();
    }

    METHOD$(u8 inc(), inline) {
        STATIC_VAR$(u8 i);

        OBJECT$(obj2) {
            METHOD$(void doit(), inline) {
                i++;
            }
        }

        obj2.doit();

        if (i == 2) {
            return 10;
        } else {
            return 0;
        }
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;

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
