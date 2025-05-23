#include <lpc213x.h>
#include <stdint.h>
uint16_t value;
uint8_t i;
uint16_t sin_wave[42] = { 512,591,665,742,808,873,926,968,998,1017,1023,1017,998,968,926,873,808,742,665,591,512,436,359,282,216,211,151,97,55,25,6,0,6,25,55,97,151,211,216,282,359,436 };
void delay_us(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<9; x++);   /* loop to generate 1 microsecond delay with Cclk = 60MHz */
	}
}
	
void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

int main (void)
{
 
	i = 0;
	PINSEL1 = 0x00080000;	/* P0.25 as DAC output */
	IO0DIR =  0xFFFFF0FF ; /* Input pins for switch. P0.8 sine, P0.9 triangular, P0.10 sawtooth, P0.11 square */

while(1)
	{		
		if ( IO0PIN & (1<<8) )	/* If switch for sine wave is pressed */
		{
				while(i !=42)
				{
					value = sin_wave[i];
					DACR = ( (1<<16) | (value<<6) );
					delay_ms(1);
					i++;
				}
				i = 0;
		}
		else if ( IO0PIN & (1<<9) )	/* If switch for triangular wave is pressed */
		{
				value = 0;
				while ( value != 1023 )
				{
					DACR = ( (1<<16) | (value<<6) );
					delay_us(10);
					value++;
				}	
				while ( value != 0 )
				{
					DACR = ( (1<<16) | (value<<6) );
					delay_us(10);
					value--;
				}
		}
		else if ( IO0PIN & (1<<10) )	/* If switch for sawtooth wave is pressed */
		{

				value = 0;
				while ( value != 1023 )
				{
					DACR = ( (1<<16) | (value<<6) );
					delay_us(10);
					value++;
				}
		}
		else if ( IO0PIN & (1<<11) )	/* If switch for square wave is pressed */
		{
				value = 1023;
				DACR = ( (1<<16) | (value<<6) );
				delay_ms(100);
				value = 0;
				DACR = ( (1<<16) | (value<<6) );
				delay_ms(100);
		}
		else	/* If no switch is pressed, 3.3V DC */
		{
			value = 1023;
			DACR = ( (1<<16) | (value<<6) );
		}
	}
}
