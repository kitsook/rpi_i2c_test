// Arduino acting as I2C slave. Read in data.  When requested, reply the last byte.
// Based on example from the Wire library
// 
// Created by Clarence Ho 2015

#include <Wire.h>

#define SLAVE_ADDR 0x60

// for disabling internal pullup of i2c pins.
// This code was tested with Raspberry Pi as I2C master,
// which has interal pullup resistors connected to 3.3v
// Reference:
// http://www.varesano.net/blog/fabio/how-disable-internal-arduino-atmega-pullups-sda-and-scl-i2c-bus
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

int last = 0;

void setup()
{
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #8
  
  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
    // deactivate internal pull-ups for twi
    // as per note from atmega8 manual pg167
    cbi(PORTC, 4);
    cbi(PORTC, 5);
  #else
    // deactivate internal pull-ups for twi
    // as per note from atmega128 manual pg204
    cbi(PORTD, 0);
    cbi(PORTD, 1);
  #endif
  
  Wire.onReceive(receiveEvent); // register receive event
  Wire.onRequest(requestEvent); // register request event
  
  Serial.begin(9600);           // start serial for output
  Serial.println("Ready...");
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  Serial.print("Received: ");
  while (1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  last = Wire.read();    // receive byte as an integer
  Serial.println(last);         // print the integer
}

// when received a request, return the last byte we got
// this function is registered as an event, see setup()
void requestEvent() {
  Serial.print("Request received. Sending ");
  Serial.println(last);
  Wire.write((byte)last);
}



