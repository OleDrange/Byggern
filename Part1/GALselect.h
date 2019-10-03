/*
 * GalSelect.h
 *
 * Created: 05.09.2019 16:49:28
 *  Author: oledr
 */ 



enum output {Sram, LCD1, LCD2, ADC};


void SetGAL(enum output select)
{
	
		DDRC = 0x0E;
		PORTC = 0x00;

		switch (select)
		{
			case ADC:
			PORTC = 0x04;  // pin 18 på gal
			break;
			
			case LCD1:
			PORTC = 0x03;  // pin 17 på gal
			break;
			
			case  LCD2:    // pin 16 på gal
			PORTC =0x02;
			break;
			
			case  Sram:   // pin 19 på gal
			PORTC = 0x08;
			break;
		}

}
