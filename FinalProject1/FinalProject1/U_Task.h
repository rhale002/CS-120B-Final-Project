#ifndef U_TASK_H
#define U_TASK_H

//Initialize USART Task states and period
enum U_States {U_Start, U_Init, U_Base} U_State;
unsigned long U_Period = 1;

//Variable to track player position
extern Player player;

//Maps Info previous
extern unsigned char group;
extern unsigned char bottomLeftCorner;
extern unsigned char bottomRightCorner;
extern unsigned char topRightCorner;
extern unsigned char topLeftCorner;

//Variable to keep track if we should end the game for a loss
extern unsigned char sendEndGameBad;

//Variable to keep track if we should end the game for a win
extern unsigned char sendEndGameGood;

//Tracks whether to reset the game
extern unsigned char resetGame;

//Variable to keep track of sending reset signal to arduino
extern unsigned char sendResetGame;

//Tracks whether to reset to win demo
extern unsigned char resetGameWinDemo;

//Variable to track if sending reset to win demo
extern unsigned char sendResetWinDemo;

//Initialize U_Task Tick Function
int U_Tick(int currentState)
{
	static unsigned char resetCounter;
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
			resetCounter = 0;
			USART_Flush(0);
		}
		break;
		
		case U_Base:
		{
			if(USART_Index == 0 && USART_IsSendReady(0))			
			{
				USART_Send(group, 0);
				if(sendResetGame == 0x01 || sendResetWinDemo == 0x01)
					resetCounter++;
				++USART_Index;
			}
			else if(USART_Index == 1 && USART_IsSendReady(0))		
			{
				USART_Send(bottomLeftCorner, 0);
				if(sendResetGame == 0x01 || sendResetWinDemo == 0x01)
					resetCounter++;
				++USART_Index;
			}
			else if(USART_Index == 2 && USART_IsSendReady(0))		
			{
				USART_Send(bottomRightCorner, 0);
				if(sendResetGame == 0x01 || sendResetWinDemo == 0x01)
					resetCounter++;
				++USART_Index;
			}
			else if(USART_Index == 3 && USART_IsSendReady(0))		
			{
				USART_Send(topLeftCorner, 0);
				if(sendResetGame == 0x01 || sendResetWinDemo == 0x01)
					resetCounter++;
				++USART_Index;
			}
			else if(USART_Index == 4 && USART_IsSendReady(0))
			{
				USART_Send(topRightCorner, 0);
				if(sendResetGame == 0x01 || sendResetWinDemo == 0x01)
					resetCounter++;
				++USART_Index;
			}
			else if(USART_Index == 5 && USART_IsSendReady(0))			//Send byte over USART for player x-position
			{
				USART_Send(player.xPosition, 0);
				++USART_Index;
			}
			else if(USART_Index == 6 && USART_IsSendReady(0))		//Send byte over USART for player y-position
			{
				USART_Send(player.yPosition, 0);
				++USART_Index;
			}
			else if(USART_Index == 7 && USART_IsSendReady(0))		//If game should be ended with a loss
			{
				USART_Send(sendEndGameBad, 0);
				++USART_Index;
			}
			else if(USART_Index == 8 && USART_IsSendReady(0))		//If game should be ended with a win
			{
				USART_Send(sendEndGameGood, 0);
				++USART_Index;
			}
			else if(USART_Index == 9 && USART_IsSendReady(0))		//If game should be reset
			{
				if(sendResetGame == 0x01 && resetCounter >= 5)
					resetGame = 0x01;
				USART_Send(resetGame, 0);
				++USART_Index;
			}
			else if(USART_Index == 10 && USART_IsSendReady(0))		//If game should be reset
			{
				if(sendResetWinDemo == 0x01 && resetCounter >= 5)
					resetGameWinDemo = 0x01;
				USART_Send(resetGameWinDemo, 0);
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