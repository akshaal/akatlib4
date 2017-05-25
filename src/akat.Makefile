HOST=avr

CC = ${HOST}-gcc
OBJDUMP = ${HOST}-objdump
OBJCOPY = ${HOST}-objcopy
SIZE = ${HOST}-size
READELF = readelf
AKATPP = ${AKAT_DIR}/akatpp/akatpp
AKATV = ${AKAT_DIR}/akatv/akatv
AKATPP_OPTS = -param MCU=${MCU} -dir ${AKAT_DIR}/akatpp-x

CFLAGS=\
		-fverbose-asm \
		-fno-exceptions \
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
		-freorder-blocks-algorithm=stc 

AKAT_SRCS=${AKAT_DIR}/src/akat.h \
		  ${AKAT_DIR}/src/akat_x_button.h \
		  ${AKAT_DIR}/src/akat_x_tm1637.h \
		  ${AKAT_DIR}/src/akat_x_timestamp.h \
		  ${AKAT_DIR}/src/akat_x_buzzer.h \
		  ${AKAT_DIR}/src/akat_x_button.c \
		  ${AKAT_DIR}/src/akat_x_tm1637.c \
