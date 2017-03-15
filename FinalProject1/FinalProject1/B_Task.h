#ifndef B_TASK_H
#define B_TASK_H

//Initialize Board task states and period
enum B_States {B_Start, B_Init, B_Base} B_State;
unsigned long B_Period = 1;

//Create extern variable for board array
extern unsigned char board[32][32];

//Track how many spaces need to be filled
extern unsigned short requiredSpaces;

//Create extern variable for tracking player position
extern Player player;

extern unsigned char sendEndGameBad;

extern unsigned char sendEndGameGood;

extern unsigned char incrementScore;

//Fills a line in the board array with 1s to track red/treaded areas
void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
	unsigned char temp;
	if(x1 > x2)
	{
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if(y1 > y2)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	for(unsigned char i = x1; i <= x2; i++)
	{
		for(unsigned char j = y1; j <= y2; j++)
		{
			board[i][j] = 0x01;
			requiredSpaces--;
		}
	}
}

void clearBoard()
{
	for(unsigned char i = 0; i < 32; i++)
	{
		for(unsigned char j = 0; j < 32; j++)
		{
			board[i][j] = 0x00;
		}
	}
}

void fillboardWinTest()
{
	drawLine(31, 5, 31, 31);
	drawLine(30, 0, 30, 31);
	drawLine(29, 0, 29, 31);
	drawLine(28, 0, 28, 31);
	drawLine(27, 0, 27, 31);
	drawLine(26, 0, 26, 31);
	drawLine(25, 0, 25, 31);
	drawLine(24, 0, 24, 31);
	drawLine(23, 0, 23, 31);
	drawLine(22, 0, 22, 31);
	drawLine(21, 0, 21, 31);
	drawLine(20, 0, 20, 31);
	drawLine(19, 0, 19, 31);
	drawLine(18, 0, 18, 31);
	drawLine(17, 0, 17, 31);
	drawLine(16, 0, 16, 31);
	drawLine(15, 0, 15, 31);
	drawLine(14, 0, 14, 31);
	drawLine(13, 0, 13, 31);
	drawLine(12, 0, 12, 31);
	drawLine(11, 0, 11, 31);
	drawLine(10, 0, 10, 31);
	drawLine(9, 0, 9, 31);
	drawLine(8, 0, 8, 31);
	drawLine(7, 0, 7, 31);
	drawLine(6, 0, 6, 31);
	drawLine(5, 0, 5, 31);
	drawLine(4, 0, 4, 31);
	drawLine(3, 0, 3, 31);
	drawLine(2, 0, 2, 31);
	drawLine(1, 0, 1, 31);
	drawLine(0, 0, 0, 31);
}

void fillBoardBasic()
{
	//Left lower corner Box
	drawLine(31, 13, 18, 13);
	drawLine(18, 13, 18, 1);
	drawLine(17, 1, 17, 14);
	drawLine(30, 0, 20, 0);
	drawLine(30, 1, 30, 11);
	drawLine(29, 1, 29, 11);
	drawLine(28, 1, 28, 11);
	drawLine(24, 13, 24, 2);
	drawLine(23, 13, 23, 2);
	drawLine(22, 13, 22, 2);
	drawLine(21, 13, 21, 2);

	//Right lower corner maze
	drawLine(18, 1, 1, 1);
	drawLine(0, 3, 15, 3);
	drawLine(1, 5, 16, 5);
	drawLine(0, 7, 15, 7);
	drawLine(1, 9, 16, 9);
	drawLine(0, 11, 15, 11);
	drawLine(1, 13, 16, 13);

	//Upper Half line
	drawLine(31, 14, 1, 14);

	//Upper right L
	drawLine(1, 17, 5, 17);
	drawLine(1, 18, 5, 18);
	drawLine(1, 19, 5, 19);
	drawLine(1, 20, 11, 20);
	drawLine(1, 21, 11, 21);
	drawLine(1, 22, 11, 22);
	drawLine(1, 23, 11, 23);
	drawLine(1, 24, 11, 24);
	drawLine(1, 25, 11, 25);

	//Upper right top bar
	drawLine(1, 28, 18, 28);
	drawLine(1, 29, 18, 29);
	drawLine(1, 30, 18, 30);

	//Upper right lopsided bar
	drawLine(7, 16, 23, 16);
	drawLine(7, 17, 23, 17);
	drawLine(7, 18, 12, 18);
	drawLine(20, 18, 23, 18);
	drawLine(20, 19, 23, 19);

	//Upper right block
	drawLine(14, 19, 18, 19);
	drawLine(14, 20, 18, 20);
	drawLine(14, 21, 18, 21);
	drawLine(14, 22, 18, 22);
	drawLine(14, 23, 18, 23);
	drawLine(14, 24, 18, 24);
	drawLine(14, 25, 18, 25);

	//Upper left bottom left block
	drawLine(26, 16, 30, 16);
	drawLine(26, 17, 30, 17);
	drawLine(26, 18, 30, 18);
	drawLine(30, 19, 30, 25);
	drawLine(29, 25, 25, 25);

	//Upper left middle block
	drawLine(25, 20, 28, 20);
	drawLine(21, 21, 28, 21);
	drawLine(21, 22, 28, 22);
	drawLine(21, 23, 28, 23);

	//Upper left upper right block
	drawLine(21, 26, 23, 26);
	drawLine(21, 27, 23, 27);
	drawLine(21, 28, 23, 28);
	drawLine(21, 29, 23, 29);
	drawLine(21, 30, 23, 30);

	//Upper left upper left block
	drawLine(26, 27, 30, 27);
	drawLine(26, 28, 30, 28);
	drawLine(26, 29, 30, 29);
	drawLine(26, 30, 30, 30);
}

//Initialize B_Task Tick Function
int B_Tick(int currentState)
{
	switch(currentState)
	{
		case B_Start:
		{
			currentState = B_Init;
		}
		break;

		case B_Init:
		{
			currentState = B_Base;
		}
		break;

		case B_Base:
		{
			currentState = B_Base;
		}
		break;

		default:
		break;
	}//transitions

	switch(currentState)
	{
		case B_Start:
		break;

		case B_Init:
		{
			requiredSpaces = 1024;
			sendEndGameBad = 0x00;
			sendEndGameGood = 0x00;
			clearBoard();
			fillBoardBasic();
			//fillboardWinTest();
			requiredSpaces--;
		}
		break;

		case B_Base:
		{
			if(requiredSpaces <= 0)
			{
				sendEndGameGood = 0x01;
			}
			else if(board[player.xPosition][player.yPosition] == 0x01)
			{
				sendEndGameBad = 0x01;
			}
			else if(player.prevXPosition != player.xPosition || player.prevYPosition != player.yPosition)
			{
				board[player.prevXPosition][player.prevYPosition] = 0x01;
				player.prevXPosition = player.xPosition;
				player.prevYPosition = player.yPosition;
				requiredSpaces--;
				incrementScore = 0x01;
			}
		}
		break;

		default:
		break;
	}//actions
	
	return currentState;
}

#endif