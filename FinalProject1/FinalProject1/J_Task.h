#ifndef J_TASK_H
#define J_TASK_H
//Initialize Joystick Task states and period
enum J_States {J_Base} J_State;
unsigned long J_Period = 1;

//Keeps track of output of joystick (which direction is being input)
//NO INPUT: J_Output == 0x00
//UP:		J_Output == 0x01
//RIGHT:	J_Output == 0x02
//DOWN:		J_Output == 0x03
//LEFT:		J_Output == 0x04
unsigned char J_Direction = 0x00;

//Initialize J_Task Tick Function
int J_Tick(int currentState)
{
	//Variable for x and y axis of joystick
	int xJoy;
	int yJoy;
	
	switch(currentState)
	{
		case J_Base:
		{
			currentState = J_Base;
		}
		break;
			
		default:
		break;
	}//transitions

	switch(currentState)
	{
		case J_Base:
		{
			xJoy = readadc(0);      //Read ADC value from A0 (Joystick x axis)
			yJoy = readadc(1);      //Read ADC value from A1 (Joystick y axis)
			xJoy = xJoy - 512;		//Move values for easier checking
			yJoy = yJoy - 512;		//Move values for easier checking
			
			//Temporary joystick testing
			if(abs(yJoy) >= abs(xJoy) && yJoy > 75)			//If up
			{
				J_Direction = 0x01;
				PORTC = 0x01;
			}
			else if(abs(xJoy) > abs(yJoy) && xJoy > 75)		//If right
			{
				J_Direction = 0x02;
				PORTC = 0x02;
			}
			else if(abs(yJoy) >= abs(xJoy) && yJoy < -75)	// If down
			{
				J_Direction = 0x03;
				PORTC = 0x04;
			}
			else if(abs(xJoy) > abs(yJoy) && xJoy < -75)	//If left
			{
				J_Direction = 0x04;
				PORTC = 0x08;
			}
			else 											//If no input
			{
				J_Direction = 0x00;
				PORTC = 0x00;
			}
		}
		break;
		
		default:
		break;
	}//actions
		
	return currentState;
}

#endif