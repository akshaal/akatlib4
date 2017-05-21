#!/usr/bin/env python

from simavr import *
import unittest
import sys
import subprocess
import os

name = sys.argv [3]
mode = sys.argv [2]
mcu = sys.argv [1]

print()
print("About to run ", name)

if name.endswith("_f1"):
    freq = 1000000
elif name.endswith("_f06"):
    freq = 600000
else:
    freq = 8000000

avr_file = "build/" + name + "-" + mode + ".avr"
result_base = 'results/' + mcu + "/" + name + "-" + mode
last_result_file = result_base + "-last"
hist_result_file = result_base + "-hist"

f = open(last_result_file, 'w')

# Run
avr = AVR (filename = avr_file, mcu = mcu, freq = freq, quiet = True)

timings = list ()
timings_us = list ()
log = list()
ats = list ()
ats_us = list ()
begin = None

stop_at_tm1637_byte = 13

def on_signal (value, arg):
    if value == 0:
        global begin
        begin = avr.cycle
    elif begin != None:
        cycles = avr.cycle - begin
        timings.append(cycles)
        timings_us.append(avr.cycles_to_usec(cycles))
        ats.append(avr.cycle)
        ats_us.append(avr.cycles_to_usec(avr.cycle))

def do_finish():
    print >> f, "offset cycles = " + str(timings).replace("L", "")
    print >> f, "offset usecs  = " + str(timings_us).replace("L", "")
    print >> f, "    at cycles = " + str(ats).replace("L", "")
    print >> f, "    at usecs  = " + str(ats_us).replace("L", "")

    if len(log) > 0:
        print >> f, "\nLOG: " + " ".join(log) + "\n"

    f.close()

    os.system("avr-size " + avr_file  + " >> " + last_result_file)

    if subprocess.call(["git", "--no-pager", "diff", "--exit-code", last_result_file]):
        os.system("git checkout " + hist_result_file)
        os.system("echo >> " + hist_result_file)
        os.system("date >> " + hist_result_file)
        os.system("cat " + last_result_file + " >> " + hist_result_file)

    sys.exit(0)

def on_exit (value, arg):
    if value != 0:
        do_finish()

class TM1637:
    def __init__(self):
        self.__clk = None
        self.__dio = None
        self.__started = False
        self.__bits = 0
        self.__bytes = 0

    def on_clk(self, value, arg):
        #on_signal(1, None); on_signal(0, None)

        if self.__started and self.__clk == 0 and value == 1:
            self.__bits += 1
            if self.__bits == 9:
                self.__bits = 0
                self.__bytes += 1
                log.append("_")
            else:
                log.append(str(self.__dio))

        self.__clk = value

    def on_dio(self, value, arg):
        #on_signal(1, None); on_signal(0, None)

        if self.__clk == 1 and self.__dio == 1 and value == 0:
            log.append(str(" S"))
            self.__started = True
            self.__bits = 0

        if self.__clk == 1 and self.__dio == 0 and value == 1:
            log.append(str("E "))
            self.__started = False

            if self.__bytes == stop_at_tm1637_byte and name == "tm1637":
                on_signal(1, None); on_signal(0, None)
                do_finish()

        self.__dio = value

tm1637 = TM1637()


def b2_handler(value, arg):
    if "buzzer" in name:
        on_signal(value, arg)

def b3_handler(value, arg):
    if "buzzer" in name:
        on_signal(value, arg)
    else:
        tm1637.on_clk(value, arg)

def b4_handler(value, arg):
    if "buzzer" in name:
        on_signal(value, arg)
    else:
        tm1637.on_dio(value, arg)

avr.get_ioport_irq('B', 0).register_notify (on_signal)
avr.get_ioport_irq('B', 1).register_notify (on_exit)

avr.get_ioport_irq('B', 2).register_notify (b2_handler)

avr.get_ioport_irq('B', 3).register_notify (b3_handler)
avr.get_ioport_irq('B', 4).register_notify (b4_handler)

button1 = PinButton(avr)
button1.connect_ioport("D", 0)

button2 = PinButton(avr)
button2.connect_ioport("D", 1)

button3 = PinButton(avr)
button3.connect_ioport("D", 2)

button4 = PinButton(avr)
button4.connect_ioport("D", 3)

buttons_pressed = False
buttons_press_at_cycle = avr.usec_to_cycles(1000)

button_release_us = 20000
if name.startswith("button_repeat") or name.startswith("button_long"):
    button_release_us = 2000000

while True:
    if not buttons_pressed and avr.cycle > buttons_press_at_cycle:
        buttons_pressed = True
        button1.set_on(timeout_us = button_release_us)
        button2.set_on(timeout_us = button_release_us)
        button3.set_on(timeout_us = button_release_us)
        button4.set_on(timeout_us = button_release_us)

    avr.run_cycles(32)
