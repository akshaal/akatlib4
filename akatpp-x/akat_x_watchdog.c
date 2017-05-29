#include <avr/wdt.h>

X_INIT$(watchdog) {
    wdt_enable(WDTO_${interval});
}

RUNNABLE$(watchdog_reset) {
    wdt_reset();
}
