#include <xc.h>
#include "ssd.h"

void init_ssd(void)
{
    /* Set SSD data line as Output */
    SSD_DATA_PORT_DDR = 0x00;
    
    /* Set SSD control lines as Output (RA5 - RA2) */
    SSD_CONTROL_PORT_DDR &= 0x03;
    
    /* Turn OFF all SSDs initially */
    SSD_CONTROL_PORT &= 0x03;
}

void display(unsigned char data[])
{
    unsigned char digit;
    
    for (digit = 0; digit < MAX_SSD_CNT; digit++)
    {
        SSD_DATA_PORT = data[digit];
        SSD_CONTROL_PORT = (SSD_CONTROL_PORT & 0x03) | (0x04 << digit);
        
        for (unsigned long int wait = 400; wait--; );
    }
}
