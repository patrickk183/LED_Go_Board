#include "mcp3008Spi.h"
 
using namespace std;

void read_input(int a2dChannel)
{
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 10000, 8);
    int a2dVal = 0;
    unsigned char data[3];
    
   data[0] = 0b00000001;  //  first byte transmitted -> start bit
    data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    data[2] = 0; // third byte transmitted....don't care

    a2d.spiWriteRead(data, sizeof(data) );

    a2dVal = 0;
    a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
    a2dVal |=  (data[2] & 0xff);
    cout << "The Result is: " << a2dVal << endl;
}


int main(void)
{
    int i = 20;
 
    while(i > 0)
    {
        read_input(0);
        sleep(1);
        i--;    
    }
    return 0;
}
