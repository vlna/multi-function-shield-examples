// Inspired by "Simple" example from DallasTemperature library by Miles Burton

// Copyright (c) 2018, Vladimir Navrat
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

// include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ShiftDisplay.h> // latest git version of library is needed, 3.6.1 is not enough
#include <TimerOne.h>

#define ONE_WIRE_BUS A4 // data wire is plugged into port A4

OneWire oneWire(ONE_WIRE_BUS); // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass our oneWire reference to DallasTemperature

ShiftDisplay display(4, 7, 8, COMMON_ANODE, 4, true); // setup shield's display

float temperature; // variable to keep temperature

void setup(void) { // setup all devices
  Serial.begin(9600); // start serial port
  Serial.println("Dallas 18B20 + 7segment display demo");

  sensors.begin(); // start up the OneWire library

  Timer1.initialize(14000); // every 14ms
  Timer1.attachInterrupt(show); // call routine to display
}

void loop(void) { // main program loop
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // send the command to get temperatures
  Serial.println("DONE");

  temperature = sensors.getTempCByIndex(0); // get temperature in deg Celsius

  noInterrupts(); // prevent interrupt to avoid incomplete change
  display.set(temperature, 2, false); // set value to display
  interrupts();

  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(temperature);
}

void show() { // display preset value to 7seg
    display.update(); // show value
    display.update();
    display.update(); // three times to avoid blinking
    display.clear();  // clear to do not have last digit brighter
}
