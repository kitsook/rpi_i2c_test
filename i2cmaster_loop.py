#!/usr/bin/env python

# Testing I2C on Raspbery Pi
# Loop sending and receiving bytes on I2C
#
# Created by Clarence Ho 2015

import smbus
import time
# for RPI rev 1...
bus = smbus.SMBus(0)
# ...for other revisions
#bus = smbus.SMBus(1)

# i2c address
address = 0x60

def writeNumber(value):
    bus.write_byte(address, value)

def readNumber():
    number = bus.read_byte(address)
    return number

var = 0
while True:
    try:
        print "Sending", var,
        writeNumber(var)
    except ValueError:
        continue
    # sleep before requesting reply from slave
    time.sleep(0.05)
    readin = readNumber()
    print "Received", readin,
    if not var == readin:
        print "MISMATCH!!"
        break
    else:
        print ""
    var += 1
    var %= 256
    time.sleep(0.05)

