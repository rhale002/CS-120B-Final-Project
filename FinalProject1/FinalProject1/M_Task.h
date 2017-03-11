#ifndef M_TASK_H
#define M_TASK_H
//Initialize Joystick Task states and period
enum M_States {M_Start, M_Init, M_Base} M_State;
unsigned long M_Period = 50;

//Output from Joystick (Which direction is being input)
//NO INPUT: J_Direction == 0x00
//UP:		J_Direction == 0x01
//RIGHT:	J_Direction == 0x02
//DOWN:		J_Direction == 0x03
//LEFT:		J_Direction == 0x04
extern unsigned char J_Direction;

extern Player player;

//Initialize M_Task Tick Function
int M_Tick(int currentState)
{	
	switch(currentState)
	{
		case M_Start:
		{
			currentState = M_Init;
		}
		break;
		case M_Init:
		{
			currentState = M_Base;
		}
		break;
		case M_Base:
		{
			currentState = M_Base;
		}
		break;
		default:
		break;
	}//transitions

	switch(currentState)
	{		
		case M_Start:
		break;
		case M_Init:
		{
			player.xPosition = 30;
			player.yPosition = 7;
		}
		break;
		case M_Base:
		{
			if(J_Direction == 0x01)			//If UP
			{
				if(player.yPosition < 14)
					++player.yPosition;
			}
			else if(J_Direction == 0x02)	//If RIGHT (Flipped)
			{
				if(player.xPosition > 0)
					--player.xPosition;
				
			}
			else if(J_Direction == 0x03)	//If DOWN
			{
				if(player.yPosition > 0)
					--player.yPosition;
			}
			else if(J_Direction == 0x04)	//If LEFT (Flipped)
			{
				if(player.xPosition < 30)
					++player.xPosition;
			}
		}
		break;
		default:
		break;
	}//actions
	
	return currentState;
}

#endif