FROM debian:buster-slim

ARG PREFIX=/akat

RUN apt-get update
RUN apt-get install -y --no-install-recommends ca-certificates wget make gcc bzip2 libc6-dev libisl-dev libgmp3-dev libmpfr-dev libmpc-dev g++

RUN mkdir /akat

# -------------------------------------------
ARG BINUTILS_V=2.33.1

RUN cd /tmp \
    && wget https://gnuftp.uib.no/binutils/binutils-$BINUTILS_V.tar.bz2 \
    && tar jxf binutils-$BINUTILS_V.tar.bz2

RUN mkdir /tmp/binutils-$BINUTILS_V/obj-avr \
    && cd /tmp/binutils-$BINUTILS_V/obj-avr \
    && ../configure --prefix=$PREFIX --target=avr --disable-nls \
    && make \
    && make install

# -------------------------------------------
ARG GCC_V=9.2.0

RUN cd /tmp \
    && wget ftp://ftp.mirrorservice.org/sites/sourceware.org/pub/gcc/releases/gcc-$GCC_V/gcc-$GCC_V.tar.gz \
    && tar zxf gcc-$GCC_V.tar.gz

RUN mkdir /tmp/gcc-$GCC_V/obj-avr \
    && cd /tmp/gcc-$GCC_V/obj-avr \
    && ../configure --prefix=$PREFIX --with-isl --target=avr --enable-languages=c,c++ --disable-nls --disable-libssp --with-dwarf2 \
    && make \
    && make install

# -------------------------------------------
ARG AVRLIBC_V=2.0.0

ENV PATH=/akat/bin:$PATH

RUN cd /tmp \
    && wget https://download.savannah.gnu.org/releases/avr-libc/avr-libc-$AVRLIBC_V.tar.bz2 \
    && tar jxf avr-libc-$AVRLIBC_V.tar.bz2

RUN cd /tmp/avr-libc-$AVRLIBC_V \
    && CC=avr-gcc ./configure --prefix=$PREFIX --host=avr  \
    && make \
    && make install \
    || cat config.log

