HOST=avr

CC = ${HOST}-gcc
OBJDUMP = ${HOST}-objdump
OBJCOPY = ${HOST}-objcopy
SIZE = ${HOST}-size
NM = ${HOST}-nm
READELF = readelf
AKATPP = ${AKAT_DIR}/akatpp/akatpp
AKATV = ${AKAT_DIR}/akatv/akatv
AKATPP_OPTS = -param MCU=${MCU} -dir ${AKAT_DIR}/akatpp-x

CFLAGS=\
		-fverbose-asm \
		-fno-exceptions \
		-Wmisspelled-isr \
		-Werror \
		-Wextra \
		-Wnonnull \
		-fstack-reuse=all \
		-Wall \
		-Wl,--gc-sections \
		-Wl,--relax \
		-fdata-sections \
		-ffunction-sections \
		-fdevirtualize-speculatively \
		-fdevirtualize-at-ltrans \
		-ffast-math \
		-ffreestanding \
		-fipa-pta \
		-fipa-icf \
		-fivopts \
		-fmerge-all-constants \
		-flto \
		-fgcse-sm \
		-fgcse-las \
		-flto-partition=one \
		-fno-strict-aliasing \
		-fomit-frame-pointer \
		-fpack-struct \
		-frename-registers \
		-fshort-enums \
		-ftree-loop-ivcanon \
		-funsigned-bitfields \
		-funsigned-char \
		-fwhole-program \
		-maccumulate-args \
		-mno-call-prologues \
		-mmcu=${MCU} \
		-mrelax \
		-nodevicelib \
		-std=gnu11 \
		-freorder-blocks-algorithm=stc \
		--param max-crossjump-edges=400000000000 \
		--param min-crossjump-insns=1 \
		--param max-gcse-memory=100000000000 \
		--param large-function-insns=10000000000 \
		--param dse-max-object-size=50000000 \
		--param scev-max-expr-size=10000000 \
		--param max-cse-path-length=100000000000 \
		--param max-reload-search-insns=100000000000 \
		--param max-cselib-memory-locations=100000000000 \
		--param sccvn-max-alias-queries-per-access=10000000000 \
		--param sccvn-max-scc-size=100000000000 \
		--param max-vartrack-size=0 \
		--param max-vartrack-expr-depth=10000000000 \
		--param ipa-cp-value-list-size=10000000000 \
		--param ipa-max-aa-steps=100000000000 \
		--param max-slsr-cand-scan=999999 \
		--param max-inline-insns-auto=5

AKAT_SRCS=${AKAT_DIR}/src/akat.h \
		  ${AKAT_DIR}/src/akat_x_button.h \
		  ${AKAT_DIR}/src/akat_x_tm1637.h \
		  ${AKAT_DIR}/src/akat_x_timestamp.h \
		  ${AKAT_DIR}/src/akat_x_buzzer.h \
		  ${AKAT_DIR}/src/akat_x_button.c \
		  ${AKAT_DIR}/src/akat_x_tm1637.c \
