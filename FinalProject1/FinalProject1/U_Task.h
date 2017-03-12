#ifndef U_TASK_H
#define U_TASK_H

//Initialize USART Task states and period
enum U_States {U_Init, U_Start, U_Base} U_State;
unsigned long U_Period = 1;

//Create extern variables for all bytes to be sent
extern Player player;
Obstacle obstacles[8];

//Initialize U_Task Tick Function
int U_Tick(int currentState)
{
	static unsigned char USART_Index;
	static unsigned char obstacleIndex;
	
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
			obstacleIndex = 0;
			USART_Flush(0);
		}
		break;
		case U_Base:
		{
			if(USART_IsSendReady(0) && USART_Index == 0)			//Send byte over USART for player x-position
			{
				USART_Send(player.xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 1)		//Send byte over USART for player y-position
			{
				USART_Send(player.yPosition, 0);
				++USART_Index;
				USART_Index = 0;
			}
			/*
			else if(USART_IsSendReady(0) && USART_Index == 2)		//Send byte over USART for obstacle 0 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 3)		//Send byte over USART for obstacle 0 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 4)		//Send byte over USART for obstacle 1 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 5)		//Send byte over USART for obstacle 1 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 6)		//Send byte over USART for obstacle 2 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 7)		//Send byte over USART for obstacle 2 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 8)		//Send byte over USART for obstacle 3 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 9)		//Send byte over USART for obstacle 3 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 10)		//Send byte over USART for obstacle 4 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 11)		//Send byte over USART for obstacle 4 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 12)		//Send byte over USART for obstacle 5 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 13)		//Send byte over USART for obstacle 5 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 14)		//Send byte over USART for obstacle 6 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 15)		//Send byte over USART for obstacle 6 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				++USART_Index;
				++obstacleIndex;
			}
			else if(USART_IsSendReady(0) && USART_Index == 16)		//Send byte over USART for obstacle 7 x-position
			{
				USART_Send(obstacles[obstacleIndex].xPosition, 0);
				++USART_Index;
			}
			else if(USART_IsSendReady(0) && USART_Index == 17)		//Send byte over USART for obstacle 7 y-position
			{
				USART_Send(obstacles[obstacleIndex].yPosition, 0);
				USART_Index = 0;
				obstacleIndex = 0;
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