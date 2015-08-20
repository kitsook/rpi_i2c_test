#!/usr/bin/env python

# Testing I2C on Raspbery Pi
# Send a byte to slave and request a byte back
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

while True:
    try:
        var = int(raw_input("Enter a number between 0 to 255: "))
        if var < 0 or var > 255:
            continue
        print "Sending ", var
        writeNumber(var)
    except ValueError:
        continue
    # sleep before requesting reply from slave
    time.sleep(0.05)
    readin = readNumber()
    print "Received ", readin

