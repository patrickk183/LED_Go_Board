/**
 * Send arbitrary number of bits at whatever clock rate (tested at 500 KHZ and 500 HZ).
 * This script will capture the SPI bytes, when a '\n' is recieved it will then output
 * the captured byte stream via the serial.
 */
 
#include <SPI.h>
#include "pins_arduino.h"

//volatile boolean process_it;

void setup (void)
{
  Serial.begin (115200);
 
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // turn on interrupts
  SPCR |= _BV(SPIE);
  
  // get ready for an interrupt 
  //process_it = false;
 
  // now turn on interrupts
  SPI.attachInterrupt();
  
}  // end of setup
 
 
// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte command = SPDR;  // grab byte from SPI Data Register
  switch (command) {
    case 1:
      SPDR = map(analogRead(A0), 0, 1023, 0, 255);
      break;
    case 2:
      SPDR = map(analogRead(A1), 0, 1023, 0, 255);
      break;
    case 3:
      SPDR = map(analogRead(A2), 0, 1023, 0, 255);
      break;
    case 4:
      SPDR = map(analogRead(A3), 0, 1023, 0, 255);
      break;
    case 5:
      SPDR = map(analogRead(A4), 0, 1023, 0, 255);
      break;
    case 6:
      SPDR = map(analogRead(A5), 0, 1023, 0, 255);
      break;
    default:
      SPDR = 127;
      break;
    }
    //Serial.write(SPDR);
    //process_it = true;
    
}  // end of interrupt routine SPI_STC_vect
 
// main loop - wait for flag set in interrupt routine
void loop (void)
{
  /*
  if (process_it)
    {
      
      process_it = false;
    }  // end of flag set
  */
    
}  // end of loop
