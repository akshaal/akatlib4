AKAT_DIR=$(PWD)/$({0%/*})

include ${AKAT_DIR}/src/akat.Makefile

all: clean OsO3

distclean: clean

PARTS  = main scope global autoglobal static_var function object object2 runnable thread thread_object sub subsub subp wait_until
PARTS += gpio_output gpio_input button button4 button4passiv tm1637 delay every_decisecond timestamp clock_f1 clock_w_kbd_tm1637_f1 countdown_f1
PARTS  = clock_f1

OsO3: ${patsubst %, build/%-O3.avr, ${PARTS}} ${patsubst %, build/%-Os.avr, ${PARTS}}
	mkdir -p results/${MCU}
	for name in `echo ${PARTS} | sed 's/ /\n/g'`; do \
	  ./benchmark.py ${MCU} Os $${name} || true; \
	  ./benchmark.py ${MCU} O3 $${name} || true; \
	done

build/%.cflags build/%.c.tmp.c: %.c ${AKAT_SRCS}
	mkdir -p build
	${AKATPP} ${AKATPP_OPTS} ${AKAT_SRCS} "$<" > build/"$<.tmp.c"

build/%-Os.avr: build/%.c.tmp.c build/%.cflags
	XX=`cat build/"$*.cflags"` && ${CC} -Os ${CFLAGS} ${CFLAGS_$*} -I. $$XX "$<" -DAKAT_DEBUG_OFF -save-temps=obj -o $@
	${OBJDUMP} -d $@ > $@.s
	${SIZE} $@
	${READELF} -S $@ > $@.info

build/%-O3.avr: build/%.c.tmp.c build/%.cflags
	XX=`cat build/"$*.cflags"` && ${CC} -O3 ${CFLAGS} ${CFLAGS_$*} -I. $$XX "$<" -DAKAT_DEBUG_OFF -save-temps=obj -o $@
	${OBJDUMP} -d $@ > $@.s
	${SIZE} $@
	${READELF} -S $@ > $@.info

clean:
	rm -rf build

.PRECIOUS: build/%.c.tmp.c build/%.cflags
