#ifndef J_TASK_H
#define J_TASK_H
//Initialize Joystick Task states and period
enum J_States {J_Base} J_State;
unsigned long J_Period = 1;

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
				PORTC = 0x01;
			else if(abs(xJoy) > abs(yJoy) && xJoy > 75)		//If right
				PORTC = 0x02;
			else if(abs(yJoy) >= abs(xJoy) && yJoy < -75)	// If down
				PORTC = 0x04;
			else if(abs(xJoy) > abs(yJoy) && xJoy < -75)	//If left
				PORTC = 0x08;
			else 											//If no direction
				PORTC = 0x00;
		}
		break;
		
		default:
		break;
	}//actions
		
	return currentState;
}

#endif