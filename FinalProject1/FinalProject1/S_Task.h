#ifndef S_TASK_H
#define S_TASK_H

//Initialize Score task states and period
enum S_States {S_Start, S_Init, S_Base, S_outputLose, S_outputWin, S_outputWait} S_State;
unsigned long S_Period = 1;

//Tracks score
extern unsigned short score;

//Variable to keep track if we should end the game for a loss
extern unsigned char sendEndGameBad;
extern unsigned char sendEndGameGood;

//Outputs score to LCD screen
void outputScore()
{
	unsigned char scoreOutput[32] = "Score: ";
	unsigned char stringScore[32];
	utoa(score, stringScore, 10);
	unsigned char i;
	
	for(i = 0; i < 32; i++)
	{
		if(scoreOutput[i] == '\0')
			break;
	}

	for(int j = 0; i < 32; i++, j++)
	{
		scoreOutput[i] = stringScore[j];
		if(stringScore[j] == '\0')
			break;
	}

	LCD_DisplayString(1, scoreOutput);
}

//Initialize S_Task Tick Function
int S_Tick(int currentState)
{
	static unsigned short waitCount;
	static unsigned char stopOutput;

	switch(currentState)
	{
		case S_Start:
		{
			currentState = S_Init;
		}
		break;

		case S_Init:
		{
			currentState = S_Base;
		}
		break;

		case S_Base:
		{
			if(sendEndGameGood == 0x01 && stopOutput != 0x01)
				currentState = S_outputWin;
			else if(sendEndGameBad == 0x01 && stopOutput != 0x01)
				currentState = S_outputLose;
			else
				currentState = S_Base;
		}
		break;

		case S_outputLose:
		{
			currentState = S_outputWait;
		}
		break;

		case S_outputWin:
		{
			currentState = S_outputWait;
		}
		break;

		case S_outputWait:
		{
			if(waitCount >= 2000)
			{
				waitCount = 0;
				stopOutput = 0x01;
				outputScore();
				currentState = S_Base;
			}
			else
				currentState = S_outputWait;
		}
		break;

		default:
		break;
	}//transitions

	switch(currentState)
	{
		case S_Start:
		break;

		case S_Init:
		{
			score = 1;
			waitCount = 0x00;
			stopOutput = 0x00;
			incrementScore = 0x00;
			outputScore();
		}
		break;

		case S_Base:
		if(sendEndGameBad == 0x01 || sendEndGameGood == 0x01 ||stopOutput == 0x01)
		{}
		else if(incrementScore == 0x01)
		{
			score++;
			outputScore();
			incrementScore = 0x00;
		}
		break;

		case S_outputLose:
		{
			LCD_DisplayString(1, "You Lose");
		}
		break;

		case S_outputWin:
		{
			LCD_DisplayString(1, "You Win");
		}
		break;

		case S_outputWait:
		{
			waitCount++;
		}
		break;

		default:
		break;
	}//actions
	
	return currentState;
}

#endif