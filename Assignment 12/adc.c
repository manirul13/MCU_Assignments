#include <xc.h>

#define _XTAL_FREQ 20000000  // 20 MHz crystal

void init_adc(void)
{
    ADFM = 1;       // Right justified
    PCFG0 = 0;      // Vref+ = Vdd
    PCFG1 = 0;      // Vref- = Vss
    ADON = 1;       // Enable ADC
}


unsigned short read_adc(unsigned char channel)
{
    unsigned short adc_reg_val;

    ADCON0 = (ADCON0 & 0xC7) | (channel << 3); // Select channel
    __delay_us(5);  // Acquisition time
    GO = 1;
    while (nDONE);

    adc_reg_val = (ADRESH << 8) | ADRESL;
    return adc_reg_val;
}
