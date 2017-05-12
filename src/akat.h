///////////////////////////////////////////////////////////////////
// Useful functions for rapid development for AVR microcontrollers.
// 2017 (C) Akshaal, Apache License
///////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define AKAT_FORCE_INLINE    __attribute__((always_inline)) inline
#define AKAT_NO_INLINE       __attribute__((noinline))
#define AKAT_UNUSED          __attribute__((unused))
#define AKAT_NO_RETURN       __ATTR_NORETURN__
#define AKAT_CONST           __ATTR_CONST__
#define AKAT_PURE            __ATTR_PURE__
#define AKAT_ERROR(msg)      __attribute__((error(msg))) extern void

#define AKAT_INC_REG(reg) asm ("inc %0" : "+r" (reg));
#define AKAT_DEC_REG(reg) asm ("dec %0" : "+r" (reg));

#define AKAT_CONCAT(a, b)     a##b
#define AKAT_FORCE_CONCAT(a, b)     AKAT_CONCAT(a, b)

#define AKAT_HOT_CODE        AKAT_FORCE_CONCAT(akat_hot_code__, __COUNTER__): __attribute__((hot, unused));
#define AKAT_COLD_CODE       AKAT_FORCE_CONCAT(akat_cold_code__, __COUNTER__): __attribute__((cold, unused));

#define AKAT_COROUTINE_S_START   0
#define AKAT_COROUTINE_S_END     255

static AKAT_FORCE_INLINE AKAT_CONST AKAT_PURE uint32_t akat_cpu_freq_hz();

static AKAT_FORCE_INLINE AKAT_UNUSED uint8_t akat_tick_period_us();

static AKAT_FORCE_INLINE AKAT_UNUSED uint8_t akat_get_tick();

AKAT_ERROR("Given delay is too long!") akat_sleep_too_long();
AKAT_ERROR("Given delay is not a constant value!") akat_sleep_not_constant();

AKAT_ERROR("tick_period_us is not set in MAIN macro!") akat_sleep_no_tick_us();

// ============================================================================================================================
// DELAY

// Delay. Delay function is non atomic!
// Routines are borrowed from avr-lib
__attribute__((error("akat_delay_us and akat_delay_us must be used with -O compiler flag and constant argument!")))
extern void akat_delay_us_error_nc__();

__attribute__((error("akat_delay_us and akat_delay_us can't perform such a small delay!")))
extern void akat_delay_us_error_delay__();

__attribute__((error("akat_delay_us and akat_delay_us can't perform such a long delay!")))
extern void akat_delay_us_error_bdelay__();

__attribute__((error("use DELAY macro instead!")))
extern void akat_delay_us_error_bdelay2__();

static AKAT_FORCE_INLINE void akat_delay_us(uint32_t us) {
    if (!__builtin_constant_p(us)) {
        akat_delay_us_error_nc__ ();
    }

    if (us > 30) {
        akat_delay_us_error_bdelay2__();
    }

    uint64_t cycles = (uint64_t)us * (uint64_t)akat_cpu_freq_hz () / (uint64_t)1000000L;

    if (cycles / 3 == 0) {
        akat_delay_us_error_delay__ ();
    } else if (cycles / 3 < 256) {
        uint8_t __count = cycles / 3;

    __asm__ volatile (
        "1: dec %0" "\n\t"
        "brne 1b"
        : "=r" (__count)
        : "0" (__count)
    );
    } else if (cycles / 4 > 65535) {
        akat_delay_us_error_bdelay__ ();
    } else {
        uint16_t __count = cycles / 4;

    __asm__ volatile (
        "1: sbiw %0,1" "\n\t"
        "brne 1b"
        : "=w" (__count)
        : "0" (__count)
    );
    }
}
