Multi BitBang I2C library<br>
Copyright (c) 2019 BitBank Software, Inc.<br>
Written by Larry Bank (bitbank@pobox.com)<br>
Project started 1/1/2018<br>
<br>
The purpose of this code is to provide a simple C library which can bit-bang
the I2C protocol on multiple GPIO pins on any system. The I2C protocol doesn't
require any special functionality of the pins beyond standard GPIO features.
The reason I wrote it was for getting easy access to I2C devices on
various microcontrollers that don't necessarily have exposed I2C interfaces.
This has come in handy on a variety of projects including AVR, ESP32, and nRF5
micrcontrollers.<br>
<br>
The pin access functions can be wrapper functions for the native versions (e.g. on the nRF5 SDK)
On AVR micros, the digitalWrite/digitalRead/pinMode functions are somewhat
slow because they check the pin numbers against tables and do other tasks.
This library includes logic to speed that up. By specifying pin numbers as the
port name + bit, the library will run considerably faster on AVR
microcontrollers. For example, On the Arduino Uno (ATmega328P), I/O pin 9 is
actually I/O Port B, bit 1. To use the direct pin method, you would specify
the pin number as 0xB1.<br>
<br>
Usage:<br>
-----<br>
Start by initializing the library with the desired pin numbers for SDA/SCL
along with the desired clock frequency. These are passed as lists (one set
for each I2C bus). The SCL (clock) lines can be shared, so for example, 4
unique I2C buses can be created from only 5 GPIO Pins. Frequencies above
400Khz are possible, but not necessarily accurate. Luckily I2C devices don't
really care about the exact clock frequency, only that the signals are stable
within the given periods.<br>

Instead of exposing functions to start and stop I2C transactions, I decided
to make it simpler by providing composite functions that hide the details of
I2C protocol. For scanning the I2C bus for devices, I provide the
Multi_I2CScan() function which returns a bitmap (16 bytes x 8 bits) with a bit
set for every device it finds. Call it like this:<br>
<br>
unsigned char ucMap[16];<br>
uint8_t bus;<br>
<br>
// scan 4 buses<br>
for (bus=0; bus<4; bus++)<br>
{<br>
  Multi_I2CScan(iBus, ucMap);<br>
  //display found devices from map<br>
}<br>
<br>
For reading and writing data to the I2C device, use the following functions:<br>
<br>

Multi_I2CRead(uint8_t bus, uint8_t addr, uint8_t *pu8Data, int iLength);<br>
Multi_I2CReadRegister(uint8_t bus, uint8_t addr, uint8_t u8Register, uint8_t *pData, int iLen);<br>
Multi_I2CWrite(uint8_t bus, uint8_t addr, uint8_t *pData, int iLen);<br>
<br>

If you find this code useful, please consider buying me a cup of coffee<br>
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=SR4F44J2UR8S4)

