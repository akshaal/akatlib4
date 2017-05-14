#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/scope);

static void hello() {
    int x = 3;
    int x2 = 4;

    SCOPE$(s1) {
        MAP_IN_SCOPE$(x, x5);

        SCOPE$(s2, restore) {
            MAP_IN_SCOPE$(x, x2);

            if (x2 == 3 && x5 == 3) {
                BENCH;
            }

            BENCH;
        }

        if (x5 == 3) {
            BENCH;
        }
    }

    if (x2 == 4) {
        BENCH;
        BENCH_EXIT;
    }
}

// Main
X_MAIN$(cpu_freq = 8000000) {
    BENCH_INIT;
    hello();
}
