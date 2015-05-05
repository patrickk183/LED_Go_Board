#include <bcm2835.h>
#include <stdio.h>

// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//

enum controller { Left, Right, Up, Down, Select, Nothing };

//returns input number, mapped from 0=0V to 1000=5V
//chan 0 = P1 X
//chan 1 = P1 Y
//chan 2 = P1 S
//chan 3 = P2 X
//chan 4 = P2 Y
//chan 5 = P2 S
//chan 6 = UNDEFINED
//chan 7 - UNDEFINED

int controllerInit() {
	if (!bcm2835_init()) {
        return 1;
    }
}

int controllerCleanup() {
	bcm2835_spi_end();
    bcm2835_close();
}

int Read(int chan) {

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default


    int a2dVal = 0;
    int a2dChannel = chan;

    char data_buffer[3];
    data_buffer[0] = 0b00000001;  //  first byte transmitted -> start bit
    data_buffer[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    data_buffer[2] = 0b00000000; // third byte transmitted....don't care
/*
    printf("\nBefore Transfer: ");
    int i;
    for (i = 0; i < 3; i++)
                  printf("%02X ", data_buffer[i]);
*/

    bcm2835_spi_transfern(data_buffer, sizeof(data_buffer));

/*
    printf("\nAfter Transfer: ");
    for (i = 0; i < 3; i++)
                  printf("%02X ", data_buffer[i]);
*/

    a2dVal = 0;
    a2dVal = (data_buffer[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
    a2dVal |=  (data_buffer[2] & 0xff);

    //printf("\nThe Result is: %d\n", a2dVal);

    return a2dVal;
}

bool isSelected(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 2;
			break;
		case 2:
			channel = 5;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
    if (Read(channel) < 100) 
    	return true;
    else
    	return false;
}

bool isNotSelected(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 2;
			break;
		case 2:
			channel = 5;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
    if (Read(channel) > 900) 
    	return true;
    else
    	return false;
}

bool isUp(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 1;
			break;
		case 2:
			channel = 4;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
    if (Read(channel) > 900) 
    	return true;
    else
    	return false;
}

bool isDown(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 1;
			break;
		case 2:
			channel = 4;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
    if (Read(channel) < 100) 
    	return true;
    else
    	return false;
}


bool isRight(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 0;
			break;
		case 2:
			channel = 3;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
    if (Read(channel) > 900) 
    	return true;
    else
    	return false;
}

bool isLeft(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 0;
			break;
		case 2:
			channel = 3;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
    if (Read(channel) < 100) 
    	return true;
    else
    	return false;
}

controller ReadPlayer(int player) {
        if (isSelected(player))
                return Select;
        else if (isUp(player))
                return Up;
        else if (isDown(player))
                return Down;
        else if (isRight(player))
                return Right;
        else if (isLeft(player))
                return Left;
        else
                return Nothing;
}

