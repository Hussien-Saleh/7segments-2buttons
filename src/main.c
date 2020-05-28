/*
   a program to control a 7-segment display using two push buttons
   requirements:
   - the two buttons are connected to pin0 and pin1 in PORTA
   - both buttons use pull-down configuration
   - the 7 segment is connected to the first 4 pins of PORTD
   conditions:
   - if switch1 is pressed, increment the number in the 7-segment display
   - if switch2 is pressed, decrement the number in the 7-segment display
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	uint8_t number = 0;
    DDRA &= (~(0x03<<PA0)); //configure pin0 & pin1 of PORTA as input pins
	DDRD |= (0x0F<<PD0); // configure the first four pins of PORTD as output pins
	
	// initialize the 7-segment display as zero
    PORTD &= ~(0x0F<<PD0);	
    
    for(;;)
    {
		if(PINA & (1<<PA0)) // check if the first push button is pressed
		{
			_delay_ms(30); // debounce

			if(PINA & (1<<PA0))
			{
					if((PORTD & 0x0F) != 9)
					{
						number++;
						PORTD = (PORTD & 0xF0) | (number & 0x0F);
					}
			}
			while(PINA & (1<<PA0)){} // wait until the push button is released
		}
		
        // check if the second push button is pressed
		else if(PINA & (1<<PA1))
		{
			_delay_ms(30);

			if(PINA & (1<<PA1))
			{
					if((PORTD & 0x0F) != 0)
					{
						number--;
						PORTD = (PORTD & 0xF0) | (num & 0x0F);
					}
			}
			while(PINA & (1<<PA1)){}
		}				       
    }
}
