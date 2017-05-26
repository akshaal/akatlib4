#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "benchmark.h"

WRITE_CFLAGS$(build/timestamp);
X_CPU$(cpu_freq = 8000000);

USE_REG$(akat_timestamp_decisecond__t);
USE_REG$(akat_timestamp_second__t);
USE_REG$(akat_timestamp_minute__t);
USE_REG$(akat_timestamp_hour__t);

X_TIMESTAMP$(t_unused);
X_TIMESTAMP$(t);

X_TIMESTAMP_CALLBACKS$(t) {
    METHOD$(void on_new_decisecond(), inline) {
    }

    METHOD$(void on_new_second(), inline) {
    }

    METHOD$(void on_new_minute(), inline) {
    }

    METHOD$(void on_new_hour(), inline) {
        BENCH;
    }
}

// Main
X_MAIN$() {
    BENCH_INIT;

    t.reset();

    t.set_bcd_hours(AKAT_BCD(1, 8));

    // Current time is 18:0:0.0, if we do 216000 then we will go back to this time with the overflow flag
    u8 rc = 0;
    for (u32 ticks = 216000; ticks; ticks--) {
        if (rc) {
            x: goto x; // halt, unexpected stuff
        }

        rc = t.inc_deciseconds();
    }

    // Test
    if (rc == 0 || t.get_hours_h() != 0 || t.get_hours_l() != 0 || t.get_deciseconds() != 0 || t.get_minutes_h() != 0 || t.get_minutes_l() != 0 || t.get_seconds_h() != 0 || t.get_seconds_l() != 0) {
        y: goto y; // halt, unexpected stuff
    }

    // Countdown 15 minutes
    t.set_bcd_minutes(AKAT_BCD(1, 5));
    rc = 0;
    for (u16 ticks = 9001; ticks; ticks--) {
        if (rc) {
            z: goto z; // halt, unexpected stuff
        }

        rc = t.dec_deciseconds();
    }

    // Test
    if (rc == 0 || t.get_deciseconds() != 9 || t.get_hours_h() != 2 || t.get_hours_l() != 3 || t.get_minutes_h() != 5 || t.get_minutes_l() != 9 || t.get_seconds_h() != 5 || t.get_seconds_l() != 9) {
        m: goto m;
    }

    BENCH_EXIT;
}
