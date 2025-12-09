#include <xc.h>
#include "ssd.h"

void init_ssd(void)
{
    /* Data lines as output */
    SSD_DATA_PORT_DDR = 0x00;
    /* Control lines RA2-RA5 as output */
    SSD_CONTROL_PORT_DDR &= 0x03;
    SSD_CONTROL_PORT &= 0x03;
}

void display(unsigned char data[])
{
    for (unsigned char digit = 0; digit < MAX_SSD_CNT; digit++)
    {
        SSD_DATA_PORT = data[digit];
        SSD_CONTROL_PORT = (SSD_CONTROL_PORT & 0x03) | (0x04 << digit);
        
        for (unsigned int wait = 300; wait--; ); // Short delay for multiplexing
    }
}
