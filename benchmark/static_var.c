#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/static_var);

GLOBAL$() {
    STATIC_VAR$(u8 zzzzz);

    static void hello() {
        SCOPE$(s1) {
            STATIC_VAR$(u8 x);

            x = 3;

            SCOPE$(s2, restore) {
                STATIC_VAR$(u8 y);

                y = 4;

                if (x == 3 && y == 4 && zzzzz == 100) {
                    BENCH;
                    BENCH_EXIT;
                }
            }
        }
    }
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;

    zzzzz = 100;

    hello();
}
