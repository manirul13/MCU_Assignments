#include<xc.h>

void init_adc(void)
{
	/*starting the adc module*/ 
	ADON = 1;   

	/*selecting right justification*/
	ADFM = 1;
}

unsigned short read_adc(void)
{
	unsigned short adc_reg_val;

	/*start the adc conversion*/
	GO = 1;

	/*wait for the conversion to complete*/
	while(nDONE);

	adc_reg_val = ((ADRESH<<8) | ADRESL);

	return adc_reg_val;
}
