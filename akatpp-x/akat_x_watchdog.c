#include <avr/wdt.h>

X_INIT$(watchdog_init) {
    wdt_enable(WDTO_${interval});
}

RUNNABLE$(watchdog_reset) {
    wdt_reset();
}
