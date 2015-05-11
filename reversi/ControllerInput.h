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
    else {
	return 0;
    }
}

void controllerCleanup() {
    bcm2835_close();
}

int Read(int chan) {

	if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    uint8_t send_data = chan;
    //printf("chan: %d\n", chan);
    //printf("send_data: %u\n", send_data);
    uint8_t read_data = bcm2835_spi_transfer(send_data);
    read_data = bcm2835_spi_transfer(send_data);
    //printf("read_data: %u\n", read_data);
	bcm2835_spi_end();
	bcm2835_close();
    return (int) read_data;
}

bool isSelected(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 3;
			break;
		case 2:
			channel = 6;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}
	int val = Read(channel);
    if (val < 50) {
    	// std::cout << val << " " << std::endl;
    	return true;
    }
    else {
    	// std::cout << val << " " << std::endl;
    	return false;
    }
}

bool isNotSelected(int player) {
	int channel;
	switch (player) {
		case 1:
			channel = 3;
			break;
		case 2:
			channel = 6;
			break;
		default:
		    printf("Select Player 1 or 2");
			exit(1);
			break;
	}

	int val = Read(channel);
    if (val > 220) {
    	// std::cout << val << " " << std::endl;
    	return true;
    }
    else {
    	// std::cout << val << " " << std::endl;
    	return false;
    }
}

bool isUp(int player) {
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

	int val = Read(channel);
    if (val > 200) {
    	// std::cout << val << " " << std::endl;
    	return true;
    }
    else
    	// std::cout << val << " " << std::endl;
    	return false;
}

bool isDown(int player) {
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

	int val = Read(channel);
    if (val < 50) {
    	return true;
   		// std::cout << val << " " << std::endl;
   	}
    else {
    	// std::cout << val << " " << std::endl;
    	return false;
    }
}


bool isRight(int player) {
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

	int val = Read(channel);
    if (val > 200) {
    	// std::cout << val << " " << std::endl;
    	return true;
    }
    else {
    	// std::cout << val << " " <<std::endl;
    	return false;
    }
}

bool isLeft(int player) {
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

	int val = Read(channel);
    if (val < 50) {
    	// std::cout << val << " " << std::endl;
    	return true;
    }
    else {
    	// std::cout << val << " " << std::endl;
    	return false;
    }
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

