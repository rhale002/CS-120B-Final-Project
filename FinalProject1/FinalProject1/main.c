/*
 * FinalProject1.c
 *
 * Created: 2/28/2017 12:45:49 PM
 * Author : robyn
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "joystick.h"


int main(void)
{
	DDRA = 0x00; PORTC = 0xFF;	//Joystick input
	DDRC = 0xFF; PORTC = 0x00;	//LED Testing Output
	
	InitADC();
	
	int xJoy;
	int yJoy;
	
    /* Replace with your application code */
    while (1) 
    {
		xJoy = readadc(0);      //READ ADC VALUE FROM PA.0
		yJoy = readadc(1);      //READ ADC VALUE FROM PA.1
		xJoy = xJoy - 512;		//Move values
		yJoy = yJoy - 512;		//Move values
		
		if(abs(yJoy) >= abs(xJoy) && yJoy > 75)			//If up
			PORTC = 0x01;
		else if(abs(xJoy) > abs(yJoy) && xJoy > 75)		//If right
			PORTC = 0x02;
		else if(abs(yJoy) >= abs(xJoy) && yJoy < -75)	// If down
			PORTC = 0x04;
		else if(abs(xJoy) > abs(yJoy) && xJoy < -75)		//If left
			PORTC = 0x08;
		else 									//If direction
			PORTC = 0x00;
    }
}

