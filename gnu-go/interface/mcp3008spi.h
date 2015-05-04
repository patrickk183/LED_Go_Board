/***********************************************************************
 * This header file contains the mcp3008Spi class definition. 
 * Its main purpose is to communicate with the MCP3008 chip using 
 * the userspace spidev facility. 
 * The class contains four variables:
 * mode        -> defines the SPI mode used. In our case it is SPI_MODE_0. 
 * bitsPerWord -> defines the bit width of the data transmitted. 
 *        This is normally 8. Experimentation with other values 
 *        didn't work for me
 * speed       -> Bus speed or SPI clock frequency. According to 
 *                https://projects.drogon.net/understanding-spi-on-the-raspberry-pi/
 *            It can be only 0.5, 1, 2, 4, 8, 16, 32 MHz. 
 *                Will use 1MHz for now and test it further.
 * spifd       -> file descriptor for the SPI device
 * 
 * The class contains two constructors that initialize the above 
 * variables and then open the appropriate spidev device using spiOpen().
 * The class contains one destructor that automatically closes the spidev
 * device when object is destroyed by calling spiClose().
 * The spiWriteRead() function sends the data "data" of length "length" 
 * to the spidevice and at the same time receives data of the same length. 
 * Resulting data is stored in the "data" variable after the function call.
 * ****************************************************************************/
#ifndef MCP3008SPI_H
#define MCP3008SPI_H
 
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
 
class mcp3008Spi{
 
public:
    mcp3008Spi();
    mcp3008Spi(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord);
    ~mcp3008Spi();
    int spiWriteRead( unsigned char *data, int length);
 
private:
    unsigned char mode;
    unsigned char bitsPerWord;
    unsigned int speed;
    int spifd;
 
    int spiOpen(std::string devspi);
    int spiClose();
};
 
#endif

int getControllerInput(int channel);
int mcpTest();

//Example code
/***********************************************************************
 * mcp3008SpiTest.cpp. Sample program that tests the mcp3008Spi class.
 * an mcp3008Spi class object (a2d) is created. the a2d object is instantiated
 * using the overloaded constructor. which opens the spidev0.0 device with 
 * SPI_MODE_0 (MODE 0) (defined in linux/spi/spidev.h), speed = 1MHz &
 * bitsPerWord=8.
 * 
 * call the spiWriteRead function on the a2d object 20 times. Each time make sure
 * that conversion is configured for single ended conversion on CH0
 * i.e. transmit ->  byte1 = 0b00000001 (start bit)
 *                   byte2 = 0b1000000  (SGL/DIF = 1, D2=D1=D0=0)
 *                   byte3 = 0b00000000  (Don't care)
 *      receive  ->  byte1 = junk
 *                   byte2 = junk + b8 + b9
 *                   byte3 = b7 - b0
 *     
 * after conversion must merge data[1] and data[2] to get final result 
 * 
 * 
 * 
 * *********************************************************************/
// #include "mcp3008Spi.h"
 
// using namespace std;
 
// int main(void)
// {
//     mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
//     int i = 20;
//     int a2dVal = 0;
//     int a2dChannel = 0;
//     unsigned char data[3];
 
//     while(i > 0)
//     {
//         data[0] = 1;  //  first byte transmitted -> start bit
//         data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
//         data[2] = 0; // third byte transmitted....don't care
 
//         a2d.spiWriteRead(data, sizeof(data) );
  
//         a2dVal = 0;
//         a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
//         a2dVal |=  (data[2] & 0xff);
//         sleep(1);
//         cout << "The Result is: " << a2dVal << endl;
//         i--;
//     }
//     return 0;
// }