#ifndef U_TASK_H
#define U_TASK_H

//Initialize USART Task states and period
enum U_States {U_Start, U_Init, U_Base} U_State;
unsigned long U_Period = 1;

//Variable to track player position
extern Player player;

//Variable to keep track if we should end the game for a loss
extern unsigned char sendEndGameBad;

//Variable to keep track if we should end the game for a win
extern unsigned char sendEndGameGood;

extern unsigned char resetGame;

//Initialize U_Task Tick Function
int U_Tick(int currentState)
{
	static unsigned char USART_Index;
	
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
			USART_Flush(0);
		}
		break;
		
		case U_Base:
		{
			if(USART_Index == 0 && USART_IsSendReady(0))			//Send byte over USART for player x-position
			{
				USART_Send(player.xPosition, 0);
				++USART_Index;
			}
			else if(USART_Index == 1 && USART_IsSendReady(0))		//Send byte over USART for player y-position
			{
				USART_Send(player.yPosition, 0);
				++USART_Index;
			}
			else if(USART_Index == 2 && USART_IsSendReady(0))		//If game should be ended with a loss
			{
				USART_Send(sendEndGameBad, 0);
				++USART_Index;
			}
			else if(USART_Index == 3 && USART_IsSendReady(0))		//If game should be ended with a win
			{
				USART_Send(sendEndGameGood, 0);
				++USART_Index;
			}
			else if(USART_Index == 4 && USART_IsSendReady(0))		//If game should be ended with a win
			{
				USART_Send(sendResetGame, 0);
				if(sendResetGame == 0x01)
					resetGame = 0x01;
				USART_Index = 0;
			}
		}
		break;
		
		default:
		break;
	}//actions
	
	return currentState;
}

#endif