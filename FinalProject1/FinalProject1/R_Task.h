#ifndef R_TASK_H
#define R_TASK_H

//Initialize Reset task states and period
enum R_States {R_Start, R_Init, R_Base, R_Wait} R_State;
unsigned long R_Period = 1;

//Variable to keep track of sending reset signal to arduino
extern unsigned char sendResetGame;
extern unsigned char resetGame;

//Initialize R_Task Tick Function
int R_Tick(int currentState)
{
	switch(currentState)
	{
		case R_Start:
		{
			currentState = R_Init;
		}
		break;

		case R_Init:
		{
			currentState = R_Base;
		}
		break;

		case R_Base:
		{
			//If reset button is pressed
			if((~PIND & 0x40) == 0x40)
				currentState = R_Wait;
		}
		break;

		case R_Wait:
		{
			//If reset button is pressed
			if((~PIND & 0x40) != 0x40)
			{
				sendResetGame = 0x01;
				currentState = R_Base;
			}
		}
		break;

		default:
		break;
	}//transitions

	switch(currentState)
	{
		case R_Start:
		break;

		case R_Init:
		{
			sendResetGame = 0x00;
			resetGame = 0x00;
		}
		break;

		case R_Base:
		break;

		case R_Wait:
		break;

		default:
		break;
	}//actions
	
	return currentState;
}

#endif