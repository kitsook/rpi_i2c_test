# rpi_i2c_test
Testing I2C connections between Raspberry Pi and Arduino.

For this example, Raspberry Pi acts as master and sends a single byte to Arduino via I2C.

Arduino, as slave, print out whatever it received.  And when requested, send out the last byte received.

Note that:
- Arduino I2C HAS internal pullup resistors.  This could be a problem when talking with devices running 3.3v (e.g. Raspberry Pi)
- However, the Arduino pullup resistor is so weak (over 50K in Due), we can disable it in software and rely on the internal pullup resistors in Raspberry Pi instead
- Some references stated that Mega has hard-wired pullup resistors that can't be disabled via software
- By disabling the Arduino pullup resistors, although not ideal, it does allow Raspberry Pi to be connected to Arduino via I2C directly without a level shifter

References:

* https://learn.adafruit.com/adafruits-raspberry-pi-lesson-4-gpio-setup/configuring-i2c
* http://playground.arduino.cc/Main/I2CBi-directionalLevelShifter
* http://www.varesano.net/blog/fabio/how-disable-internal-arduino-atmega-pullups-sda-and-scl-i2c-bus
