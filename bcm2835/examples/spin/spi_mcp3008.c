Skip to content
 This repository
Explore
Gist
Blog
Help
@sweaver2494 sweaver2494
 
 Unwatch 4
  Star 0
  Fork 0
patrickk183/LED_Go_Board
 branch: master  LED_Go_Board/bcm2835/examples/spi/spi.c
@sweaver2494sweaver2494 3 hours ago wiringPi
1 contributor
RawBlameHistory     63 lines (53 sloc)  2.168 kb
// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);

      if (!bcm2835_init())
	return 1;

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    // Send a byte to the slave and simultaneously read a byte back from the slave
    // If you tie MISO to MOSI, you should read back what was sent
    //uint8_t send_data = 0x23;
    //uint8_t read_data = bcm2835_spi_transfer(send_data);
    //printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data, read_data);
    //if (send_data != read_data)
      //printf("Do you have the loopback from MOSI to MISO connected?\n");

    int a2dVal = 0; 
    int a2dChannel = 0;        
        
    char data_buffer[3];   
    data_buffer[0] = 0b00000001;  //  first byte transmitted -> start bit
    data_buffer[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    data_buffer[2] = 0b00000000; // third byte transmitted....don't care

    printf("\nBefore Transfer: ");
    for (int i = 0; i < 3; i++)
		  printf("%02X ", data_buffer[i]);
      
    bcm2835_spi_transfern(data_buffer, sizeof(data_buffer));
    
    printf("\nAfter Transfer: ");
    for (int i = 0; i < 3; i++)
		  printf("%02X ", data_buffer[i]);
      
    a2dVal = 0;
    a2dVal = (data_buffer[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
    a2dVal |=  (data_buffer[2] & 0xff);

    printf("\nThe Result is: %d\n", a2dVal);

    
    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}

Status API Training Shop Blog About
© 2015 GitHub, Inc. Terms Privacy Security Contact
