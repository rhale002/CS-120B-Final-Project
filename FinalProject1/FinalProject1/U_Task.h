#ifndef U_TASK_H
#define U_TASK_H

//Initialize USART Task states and period
enum U_States {U_Init, U_Start, U_Base} U_State;
unsigned long U_Period = 1;

//Create extern variables for all bytes to be sent
/* 
extern unsigned char test;
*/

//Initialize U_Task Tick Function
int U_Tick(int currentState)
{
	static int USART_Index;
	
	switch(currentState)
	{
		case U_Start:
		{
			currentState = U_Init;
		}
		break;
		case U_Init:
		{
			currentState = U_Base;
		}
		break;
		case U_Base:
		{
			currentState = U_Base;
		}
		break;
		
		default:
		break;
	}//transitions

	switch(currentState)
	{
		case U_Start:
		break;
		case U_Init:
		{
			USART_Index = 0;
		}
		break;
		case U_Base:
		{
			//Example code of how USART will send bytes
			/*
			if(USART_IsSendReady(0) && USART_Index == 0)
			{
				USART_Send(test, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 1)
			{
				//Send B1
				USART_Index = 0;
			}
			*/
		}
		break;
		
		default:
		break;
	}//actions
	
	return currentState;
}

#endif