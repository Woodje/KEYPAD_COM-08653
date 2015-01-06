#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <avr/delay.h>

// This is used for controlling the users input.
char input,
	 prevInput;

// Arrays of the KEYPADs columns and rows.
int KEYPADsColumns[3] = { 0, 2, 4 },
	KEYPADsRows[4] = { 1, 3, 5, 6 };

// Arrays of the KEYPADs values according to the columns and rows.
char KEYPADsValues[3][4] = { "2085", "1*74", "3#96" };

// Initializing the keypad with the necessary bits to different registers for input and output.
void InitializeKEYPAD()
{
	// For the selected DDR, set ports 1, 3, 5 and 6 as input that reads high.
	DDRD &= ~(1<<PIND1 | 1<<PIND3 | 1<<PIND5 | 1<<PIND6);
	PORTD |= 1<<PIND1 | 1<<PIND3 | 1<<PIND5 | 1<<PIND6;
		
	// For the selected DDR, set ports 0, 2 and 4 as outputting high.
	DDRD |= 1<<PIND0 | 1<<PIND2 | 1<<PIND4;
	PORTD |= 1<<PIND0 | 1<<PIND2 | 1<<PIND4;
}

// Reads the pressed value from the keypad.
char ReadKEYPAD()
{
	for (int i = 0; i < 3; i++)
	{
		// Set one of the columns output pin to low.
		PORTD &= ~(1<<KEYPADsColumns[i]);
		
		_delay_us(20);
		
		for (int x = 0; x < 4; x++)
		{
			// Check which of the rows input pin that read low.
			if (bit_is_clear(PIND, KEYPADsRows[x]))
			{
				// Set the output pin back to high.
				PORTD |= 1<<KEYPADsColumns[i];
				
				// Return the pressed key.
				return KEYPADsValues[i][x];
			}				
		}

		// Set the output pin back to high.
		PORTD |= 1<<KEYPADsColumns[i];
	}
	// Return a value that means that no keys is pressed.
	return 0;
}	

#endif