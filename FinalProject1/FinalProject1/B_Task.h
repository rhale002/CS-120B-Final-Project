#ifndef B_TASK_H
#define B_TASK_H

//Initialize Board task states and period
enum B_States {B_Start, B_Init, B_Base} B_State;
unsigned long B_Period = 1;

//Create extern variable for board array
extern unsigned char board[32][32];

//Random board variables
extern unsigned char group;
extern unsigned char bottomLeftCorner;
extern unsigned char bottomRightCorner;
extern unsigned char topRightCorner;
extern unsigned char topLeftCorner;

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

//Test win board
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

//Test Board
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

//Fill bottom left corner square with random grid
void bottomLeftCornerRandFill()
{
	if(bottomLeftCorner == 0)
	{
		//top left box
		drawLine(31, 15, 29, 15);
		drawLine(31, 14, 29, 14);
		drawLine(31, 13, 29, 13);

		//top middle box
		drawLine(25, 15, 24, 15);
		drawLine(25, 14, 24, 14);
		drawLine(25, 13, 24, 13);

		//top middle right box
		drawLine(22, 14, 21, 14);
		drawLine(22, 13, 21, 13);
		drawLine(22, 12, 21, 12);
		
		//top right box
		drawLine(19, 15, 16, 15);
		drawLine(19, 14, 16, 14);
		drawLine(19, 13, 18, 13);

		//top left L
		drawLine(30, 11, 28, 11);
		drawLine(27, 11, 27, 14);

		//spec next to L
		drawLine(24, 11, 23, 11);

		//spec below L
		drawLine(30, 8, 30, 7);

		//right of below L spec
		drawLine(28, 9, 28, 6);

		//Line below spec
		drawLine(31, 5, 31, 3);

		//Line Right of left line
		drawLine(29, 4, 27, 4);

		//Dot below line
		drawLine(28, 2, 28, 2);

		//Lower left L
		drawLine(30, 1, 30, 0);
		drawLine(29, 0, 27, 0);

		//Line right of dot
		drawLine(25, 5, 25, 1);

		//Odd right of line
		drawLine(23, 6, 21, 6);
		drawLine(22, 7, 21, 7);

		//Rect right of line
		drawLine(23, 1, 21, 1);
		drawLine(23, 0, 21, 0);

		//rect above rect
		drawLine(22, 4, 20, 4);
		drawLine(22, 3, 20, 3);

		//tall rect right of rect
		drawLine(18, 0, 18, 6);
		drawLine(17, 0, 17, 6);

		//Rect above tall rect
		drawLine(17, 8, 17, 10);
		drawLine(16, 8, 16, 10);

		//square above line
		drawLine(25, 9, 24, 9);
		drawLine(25, 8, 24, 8);

		//Square right of square
		drawLine(21, 10, 20, 10);
		drawLine(21, 9, 20, 9);
	}
	else if(bottomLeftCorner == 1)
	{
		//lower left small line
		drawLine(30, 0, 30, 1);

		//Odd Right of small line
		drawLine(28, 1, 28, 3);
		drawLine(31, 3, 29, 3);
		drawLine(31, 4, 30, 4);

		//big odd right of odd
		drawLine(28, 5, 25, 5);
		drawLine(26, 4, 25, 4);
		drawLine(26, 3, 25, 3);
		drawLine(26, 2, 25, 2);
		drawLine(26, 1, 22, 1);
		drawLine(26, 0, 22, 0);
		drawLine(21, 0, 21, 10);

		//Spec inside big odd crevice
		drawLine(23, 3, 23, 4);

		//odd L above big odd
		drawLine(24, 6, 24, 7);
		drawLine(24, 8, 30, 8);
		drawLine(30, 9, 29, 9);
		drawLine(30, 10, 29, 10);

		// fat base L above odd L
		drawLine(31, 12, 29, 12);
		drawLine(31, 13, 29, 13);
		drawLine(31, 14, 29, 14);
		drawLine(31, 15, 24, 15);

		//Side S below odd L
		drawLine(27, 13, 23, 13);
		drawLine(22, 13, 22, 14);
		drawLine(27, 12, 26, 12);
		drawLine(27, 11, 26, 11);

		//Square below side S
		drawLine(24, 11, 23, 11);
		drawLine(24, 10, 23, 10);

		//Right of side S
		drawLine(20, 13, 20, 15);
		drawLine(19, 14, 18, 14);
		drawLine(19, 15, 18, 15);

		//Line below object above
		drawLine(19, 11, 19, 8);

		//Box below above line
		drawLine(20, 6, 17, 6);
		drawLine(20, 5, 17, 5);
		drawLine(20, 4, 17, 4);

		//Line spec left below box
		drawLine(19, 2, 19, 1);

		//Spec right of spec
		drawLine(17, 1, 17, 0);
	}
	else if(bottomLeftCorner == 2)
	{
		//lower left rect
		drawLine(29, 1, 25, 1);
		drawLine(29, 2, 25, 2);

		//rect above rect
		drawLine(30, 4, 27, 4);
		drawLine(30, 5, 27, 5);

		//Rect of left middle
		drawLine(31, 7, 28, 7);
		drawLine(31, 8, 28, 8);

		//odd above left middle rect
		drawLine(26, 9, 24, 9);
		drawLine(30, 10, 24, 10);
		drawLine(30, 11, 24, 11);
		drawLine(30, 12, 27, 12);
		drawLine(28, 13, 27, 13);
		drawLine(28, 14, 27, 14);

		//square above odd
		drawLine(31, 14, 30, 14);
		drawLine(31, 15, 30, 15);

		//Square right of odd
		drawLine(25, 15, 23, 15);
		drawLine(25, 14, 23, 14);
		drawLine(25, 13, 23, 13);

		//Big square to the right
		drawLine(21, 14, 19, 14);
		drawLine(21, 13, 17, 13);
		drawLine(21, 12, 17, 12);
		drawLine(21, 11, 17, 11);
		drawLine(21, 10, 17, 10);

		//Sqaure below big square
		drawLine(19, 8, 16, 8);
		drawLine(19, 7, 16, 7);
		drawLine(19, 6, 19, 6);

		//Big odd below square
		drawLine(23, 0, 21, 0);
		drawLine(23, 1, 21, 1);
		drawLine(23, 2, 17, 2);
		drawLine(23, 3, 17, 3);
		drawLine(24, 4, 17, 4);
		drawLine(17, 5, 17, 5);

		//Middle
		drawLine(25, 6, 22, 6);
		drawLine(25, 7, 22, 7);
		drawLine(22, 8, 22, 8);
	}
	else if(bottomLeftCorner == 3)
	{
		//Big bottom left square
		drawLine(30, 0, 28, 0);
		drawLine(30, 1, 28, 1);
		drawLine(30, 2, 28, 2);
		drawLine(30, 3, 28, 3);
		drawLine(30, 4, 28, 4);
		drawLine(30, 5, 28, 5);

		//Odd right of bottom left square
		drawLine(26, 1, 24, 1);
		drawLine(26, 2, 24, 2);
		drawLine(26, 3, 24, 3);
		drawLine(26, 4, 24, 4);
		drawLine(26, 5, 24, 5);
		drawLine(26, 6, 24, 6);
		drawLine(30, 7, 24, 7);
		drawLine(31, 7, 31, 13);
		drawLine(31, 14, 28, 14);

		//Square in odd crevice
		drawLine(26, 13, 26, 13);
		drawLine(29, 12, 26, 12);
		drawLine(29, 11, 26, 11);
		drawLine(29, 10, 26, 10);
		drawLine(29, 9, 26, 9);

		//spec near odd
		drawLine(24, 10, 23, 10);

		//Square above spec
		drawLine(23, 12, 22, 12);
		drawLine(23, 13, 22, 13);

		//Line to right of square
		drawLine(20, 14, 20, 10);

		//Line right of line
		drawLine(18, 13, 18, 6);
		drawLine(19, 8, 19, 6);

		//line left of line
		drawLine(22, 8, 22, 5);

		//box below line
		drawLine(20, 4, 19, 4);
		drawLine(21, 3, 19, 3);
		drawLine(21, 2, 19, 2);
		drawLine(21, 1, 19, 1);

		//Top mess up line
		drawLine(31, 15, 16, 15);

		//right line below mess up
		drawLine(17, 13, 17, 8);

		//spec below line
		drawLine(16, 6, 16, 5);

		//Left of line verticle line
		drawLine(18, 3, 18, 1);

		//Fix line
		drawLine(16, 4, 18, 4);
	}
}

//Fill bottom right corner with random grid
void bottomRightCornerRandFill()
{
	if(bottomRightCorner == 0)
	{
		//bottom right rect
		drawLine(3, 2, 1, 2);
		drawLine(3, 3, 1, 3);
		drawLine(3, 4, 1, 4);
		drawLine(3, 5, 1, 5);
		drawLine(3, 6, 1, 6);

		//Bottom right S
		drawLine(4, 0, 2, 0);
		drawLine(5, 0, 5, 4);
		drawLine(7, 5, 5, 5);

		//Left of S
		drawLine(8, 3, 7, 3);
		drawLine(10, 2, 7, 2);
		drawLine(10, 1, 7, 1);

		//Left of box
		drawLine(15, 1, 13, 1);
		drawLine(15, 2, 13, 2);

		//Big box above
		drawLine(14, 4, 10, 4);
		drawLine(14, 5, 10, 5);
		drawLine(14, 6, 10, 6);

		//long odd above
		drawLine(15, 13, 15, 8);
		drawLine(14, 13, 14, 8);
		drawLine(13, 8, 9, 8);
		drawLine(10, 9, 9, 9);
		drawLine(10, 10, 3, 10);
		drawLine(4, 9, 3, 9);

		//Spec inside odd long
		drawLine(6, 8, 7, 8);

		//top right big odd
		drawLine(0, 8, 0, 14);
		drawLine(1, 8, 1, 12);
		drawLine(6, 12, 2, 12);
		drawLine(6, 13, 5, 13);

		//Above right big odd
		drawLine(2, 14, 3, 14);
		drawLine(2, 15, 9, 15);
		drawLine(8, 14, 9, 14);
		drawLine(8, 13, 9, 13);

		//Left of that shit
		drawLine(11, 14, 11, 12);
		drawLine(12, 14, 12, 10);
	}
	else if(bottomRightCorner == 1)
	{
		//Bottom right oddball
		drawLine(0, 0, 0, 11);
		drawLine(1, 11, 4, 11);
		drawLine(1, 0, 4, 0);
		drawLine(1, 1, 4, 1);

		//Inside crevice
		drawLine(2, 3, 2, 9);
		drawLine(3, 3, 3, 9);
		drawLine(4, 9, 5, 9);

		//middle bottom
		drawLine(6, 1, 6, 6);
		drawLine(7, 1, 7, 6);
		drawLine(8, 5, 8, 6);
		drawLine(9, 5, 9, 6);

		//Bottom left
		drawLine(9, 0, 13, 0);
		drawLine(9, 1, 13, 1);
		drawLine(9, 2, 11, 2);
		drawLine(9, 3, 11, 3);

		//little up bottom left
		drawLine(15, 1, 15, 4);
		drawLine(14, 3, 14, 4);
		drawLine(13, 3, 13, 4);

		//above that shit
		drawLine(14, 6, 11, 6);
		drawLine(14, 7, 11, 7);
		drawLine(14, 8, 13, 8);
		drawLine(14, 9, 13, 9);

		//box above the left middle box
		drawLine(11, 9, 9, 9);
		drawLine(11, 10, 9, 10);

		//Big ass shit above
		drawLine(7, 11, 7, 8);
		drawLine(14, 12, 7, 12);
		drawLine(14, 13, 7, 13);
		drawLine(14, 14, 7, 14);

		//top right line
		drawLine(1, 13, 5, 13);
	}
	else if(bottomRightCorner == 2)
	{
		//bottom right L
		drawLine(0, 0, 0, 5);
		drawLine(2, 5, 1, 5);

		//bottom right rect
		drawLine(2, 1, 3, 1);
		drawLine(2, 2, 3, 2);
		drawLine(2, 3, 3, 3);

		//Fat Butt L
		drawLine(5, 0, 5, 6);
		drawLine(6, 5, 8, 5);
		drawLine(6, 6, 8, 6);

		//Under dat booty
		drawLine(7, 1, 7, 3);
		drawLine(8, 2, 8, 3);
		drawLine(9, 2, 9, 3);

		//Left of da booty
		drawLine(10, 4, 10, 5);
		drawLine(11, 4, 11, 5);
		drawLine(12, 4, 12, 5);

		//Bottom left corner box
		drawLine(9, 0, 13, 0);
		drawLine(11, 1, 13, 1);
		drawLine(11, 2, 13, 2);

		//Bottom left line
		drawLine(15, 1, 15, 3);

		//Bottom Left L
		drawLine(14, 5, 14, 7);
		drawLine(13, 7, 11, 7);

		//Above the L
		drawLine(15, 9, 12, 9);

		//Big top left corner box
		drawLine(14, 11, 9, 11);
		drawLine(14, 12, 9, 12);
		drawLine(14, 13, 9, 13);
		drawLine(10, 14, 9, 14);

		//top right box
		drawLine(7, 15, 1, 15);
		drawLine(7, 14, 1, 14);
		drawLine(7, 13, 6, 13);

		//Top right little lower box
		drawLine(0, 12, 4, 12);
		drawLine(0, 11, 6, 11);

		//middle long box
		drawLine(1, 9, 9, 9);
		drawLine(1, 8, 9, 8);
		drawLine(1, 7, 3, 7);

		//top right line
		drawLine(15, 15, 12, 15);
	}
	else if(bottomRightCorner == 3)
	{
		//Bottom right box
		drawLine(1, 1, 4, 1);
		drawLine(1, 2, 3, 2);
		drawLine(1, 3, 3, 3);

		//bottom middle box
		drawLine(7, 1, 7, 3);
		drawLine(8, 1, 8, 3);

		//above L
		drawLine(5, 3, 5, 5);
		drawLine(6, 5, 7, 5);

		//Bottom left block
		drawLine(10, 4, 14, 4);
		drawLine(10, 3, 14, 3);
		drawLine(10, 2, 11, 2);

		//Bottom left line
		drawLine(13, 1, 15, 1);

		//Left middle weird
		drawLine(15, 6, 9, 6);
		drawLine(15, 7, 14, 7);
		drawLine(15, 8, 14, 8);
		drawLine(15, 9, 14, 9);
		drawLine(15, 10, 11, 10);

		//Crevice L
		drawLine(12, 8, 9, 8);
		drawLine(9, 9, 9, 11);

		//Top left box
		drawLine(12, 12, 14, 12);
		drawLine(12, 13, 14, 13);
		drawLine(12, 14, 14, 14);

		//Top middle box
		drawLine(10, 15, 8, 15);
		drawLine(10, 14, 8, 14);
		drawLine(10, 13, 8, 13);

		//Top middle L
		drawLine(6, 14, 6, 12);
		drawLine(5, 12, 3, 12);

		//Top right box
		drawLine(4, 15, 1, 15);
		drawLine(4, 14, 2, 14);

		//top right spec
		drawLine(0, 13, 0, 12);

		//middle box
		drawLine(1, 10, 7, 10);
		drawLine(4, 9, 7, 9);
		drawLine(4, 8, 7, 8);
		drawLine(4, 7, 7, 7);

		//Middle Right box
		drawLine(0, 5, 0, 8);
		drawLine(1, 5, 1, 8);
		drawLine(2, 5, 2, 8);
	}
}

//Fill top left corner with random grid
void topLeftCornerRandFill()
{
	if(topLeftCorner == 0)
	{
		//Top Left box
		drawLine(31, 31, 26, 31);
		drawLine(26, 30, 26, 24);
		drawLine(27, 30, 27, 24);

		//Top Left left box
		drawLine(30, 29, 30, 23);
		drawLine(29, 29, 29, 23);

		//bottom left L
		drawLine(30, 20, 30, 17);
		drawLine(29, 17, 25, 17);

		//Bottom left box
		drawLine(28, 21, 28, 19);
		drawLine(27, 21, 27, 19);
		drawLine(26, 21, 26, 19);

		//bottom middle box
		drawLine(23, 16, 23, 18);
		drawLine(22, 16, 22, 18);

		//Bottom right box
		drawLine(20, 17, 17, 17);
		drawLine(17, 18, 17, 20);
		drawLine(18, 18, 18, 20);
		drawLine(19, 20, 23, 20);

		//right middle box
		drawLine(18, 22, 24, 22);
		drawLine(18, 23, 18, 26);
		drawLine(19, 23, 19, 26);
		drawLine(20, 23, 20, 26);

		//Middle box
		drawLine(22, 24, 22, 27);
		drawLine(23, 24, 23, 27);

		//Top middle box
		drawLine(24, 29, 22, 29);
		drawLine(24, 30, 22, 30);

		//top right box
		drawLine(18, 31, 18, 28);
		drawLine(19, 31, 19, 28);
		drawLine(20, 31, 20, 28);

		//Top Right Line
		drawLine(16, 30, 16, 27);
	}
	else if(topLeftCorner == 1)
	{
		//big top left box
		drawLine(30, 30, 18, 30);
		drawLine(30, 29, 26, 29);
		drawLine(30, 28, 26, 28);
		drawLine(30, 27, 26, 27);

		//big middle left box
		drawLine(31, 25, 26, 25);
		drawLine(31, 24, 26, 24);
		drawLine(31, 23, 29, 23);
		drawLine(31, 22, 29, 22);
		drawLine(31, 21, 29, 21);
		drawLine(31, 20, 29, 20);

		//bottom left box
		drawLine(30, 18, 28, 18);
		drawLine(30, 17, 28, 17);

		//bottom middle box
		drawLine(26, 16, 26, 21);
		drawLine(25, 16, 25, 21);
		drawLine(24, 16, 24, 21);
		drawLine(23, 21, 22, 21);

		//Bottom right mid block
		drawLine(21, 17, 21, 19);
		drawLine(22, 17, 22, 19);

		//Bottom Right block
		drawLine(17, 17, 17, 19);
		drawLine(18, 17, 18, 19);

		//Right middle block
		drawLine(18, 21, 18, 23);
		drawLine(19, 21, 19, 23);

		//middle box
		drawLine(21, 23, 24, 23);
		drawLine(21, 24, 24, 24);

		//top right box
		drawLine(17, 26, 17, 25);
		drawLine(18, 26, 18, 25);

		// top right middle box
		drawLine(19, 28, 24, 28);
		drawLine(20, 27, 24, 27);
		drawLine(20, 26, 24, 26);

		//Top right line
		drawLine(16, 30, 16, 28);
	}
	else if(topLeftCorner == 2)
	{
		//top left box
		drawLine(30, 30, 26, 30);
		drawLine(30, 29, 26, 29);
		drawLine(30, 28, 26, 28);
		drawLine(30, 27, 28, 27);
		drawLine(30, 26, 28, 26);

		//Bottom left box
		drawLine(30, 24, 30, 17);
		drawLine(29, 24, 29, 17);

		//bottom left box
		drawLine(27, 18, 26, 18);
		drawLine(27, 19, 26, 19);
		drawLine(27, 20, 24, 20);

		//bottom middle block
		drawLine(24, 17, 23, 17);
		drawLine(24, 18, 23, 18);

		//above spec
		drawLine(22, 20, 22, 21);

		//Bottom right box
		drawLine(19, 16, 19, 18);
		drawLine(20, 16, 20, 18);
		drawLine(21, 16, 21, 18);

		//Bottom right line
		drawLine(17, 17, 17, 19);

		//Bottom right mid box
		drawLine(16, 21, 20, 21);
		drawLine(16, 22, 20, 22);

		//right mid box
		drawLine(17, 24, 17, 25);
		drawLine(18, 24, 18, 25);

		//right top box
		drawLine(17, 31, 19, 31);
		drawLine(17, 30, 19, 30);
		drawLine(17, 29, 19, 29);
		drawLine(17, 28, 19, 28);

		//Top middle box
		drawLine(20, 26, 20, 25);
		drawLine(21, 30, 21, 25);
		drawLine(22, 30, 22, 25);
		drawLine(23, 30, 23, 25);

		//Middle block
		drawLine(25, 24, 25, 26);
		drawLine(26, 24, 26, 26);
	}
	else if(topLeftCorner == 3)
	{
		//Top left line
		drawLine(31, 31, 24, 31);

		//top left 2nd low line
		drawLine(31, 29, 25, 29);

		//below 2nd line
		drawLine(30, 27, 24, 27);
		drawLine(28, 26, 27, 26);
		drawLine(28, 25, 27, 25);

		//Left mid block
		drawLine(31, 25, 31, 22);
		drawLine(30, 25, 30, 22);
		drawLine(29, 23, 29, 22);
		drawLine(28, 23, 28, 22);

		//Bottom left block
		drawLine(31, 19, 31, 16);
		drawLine(30, 19, 30, 16);

		//bottom left tetris block
		drawLine(28, 17, 28, 20);
		drawLine(27, 17, 27, 20);
		drawLine(26, 19, 26, 22);
		drawLine(25, 19, 25, 22);
		drawLine(24, 19, 24, 22);

		//Bottom mid block
		drawLine(25, 16, 24, 16);
		drawLine(25, 17, 24, 17);

		//Bottom right block
		drawLine(17, 17, 22, 17);
		drawLine(17, 18, 22, 18);

		//Bottom right line
		drawLine(19, 20, 22, 20);

		//Big top right block
		drawLine(17, 22, 17, 27);
		drawLine(18, 22, 18, 27);
		drawLine(19, 22, 19, 27);
		drawLine(20, 22, 20, 31);
		drawLine(21, 22, 21, 31);

		//Top right box
		drawLine(16, 30, 18, 30);
		drawLine(16, 29, 18, 29);

		//middle box
		drawLine(23, 25, 25, 25);
		drawLine(23, 24, 25, 24);
	}
}

//Fill top right corner with random grid
void topRightCornerRandFill()
{
	if(topRightCorner == 0)
	{
		//Top right box
		drawLine(0, 31, 0, 25);
		drawLine(1, 31, 1, 30);
		drawLine(2, 31, 2, 30);
		drawLine(3, 31, 3, 30);
		drawLine(1, 26, 1, 25);
		drawLine(2, 26, 2, 25);

		//Weird middle right box
		drawLine(2, 28, 4, 28);
		drawLine(4, 27, 4, 24);
		drawLine(5, 23, 1, 23);
		drawLine(5, 22, 1, 22);
		drawLine(5, 21, 1, 21);

		//line to the left
		drawLine(6, 29, 6, 25);

		//Bottom right sqaure
		drawLine(0, 19, 1, 19);
		drawLine(0, 18, 1, 18);

		//Bottom left little middle box
		drawLine(4, 19, 4, 17);
		drawLine(5, 19, 5, 17);

		//bottom middle line
		drawLine(7, 18, 7, 16);

		//bottom left middle box
		drawLine(10, 18, 10, 19);
		drawLine(11, 18, 11, 19);

		//bottom left L
		drawLine(13, 18, 13, 17);
		drawLine(14, 17, 14, 17);

		//bottom left up mid box
		drawLine(15, 19, 15, 21);
		drawLine(14, 20, 14, 21);

		//mid left box
		drawLine(12, 21, 11, 21);
		drawLine(12, 22, 11, 22);
		drawLine(14, 23, 11, 23);

		//Mid left spec
		drawLine(13, 25, 12, 25);

		//middle long box
		drawLine(9, 22, 9, 30);
		drawLine(8, 22, 8, 30);

		//bottom spec
		drawLine(8, 20, 7, 20);

		// top left Brace
		drawLine(14, 27, 12, 27);
		drawLine(11, 27, 11, 31);
		drawLine(14, 31, 12, 31);

		//Top left line
		drawLine(15, 29, 13, 29);
	}
	else if(topRightCorner == 1)
	{
		//top right box
		drawLine(1, 30, 1, 23);
		drawLine(2, 30, 2, 27);
		drawLine(3, 30, 3, 27);
		drawLine(3, 23, 2, 23);

		//spec in crevice
		drawLine(3, 25, 4, 25);

		//middle weird thing
		drawLine(7, 28, 9, 28);
		drawLine(8, 27, 8, 24);
		drawLine(9, 27, 9, 20);
		drawLine(7, 24, 6, 24);

		//top middle box
		drawLine(6, 26, 5, 26);
		drawLine(5, 27, 5, 31);
		drawLine(9, 30, 6, 30);
		drawLine(9, 31, 6, 31);

		//bottom up middle block
		drawLine(0, 21, 0, 18);
		drawLine(1, 21, 1, 18);

		//Bottom right line
		drawLine(1, 16, 4, 16);

		//L left of block
		drawLine(3, 20, 3, 19);
		drawLine(4, 20, 5, 20);

		//L left of L
		drawLine(7, 21, 7, 22);
		drawLine(6, 22, 5, 22);

		//bottom mid block
		drawLine(6, 17, 8, 17);
		drawLine(5, 18, 8, 18);

		//bottom left line
		drawLine(11, 17, 14, 17);

		//Bottom left mid line
		drawLine(12, 19, 15, 19);

		//Mid left block
		drawLine(11, 21, 13, 21);
		drawLine(11, 22, 13, 22);
		drawLine(14, 21, 14, 24);

		//top left block
		drawLine(12, 24, 12, 28);
		drawLine(13, 26, 13, 28);
		drawLine(14, 26, 14, 30);
		drawLine(15, 26, 15, 30);
	}
	else if(topRightCorner == 2)
	{
		//Top Right box
		drawLine(1, 30, 8, 30);
		drawLine(6, 29, 8, 29);
		drawLine(6, 28, 8, 28);

		//Top right line
		drawLine(0, 28, 4, 28);

		//Right mid box
		drawLine(1, 26, 3, 26);
		drawLine(1, 25, 3, 25);
		drawLine(1, 24, 3, 24);

		// right mid low block
		drawLine(0, 22, 2, 22);
		drawLine(0, 21, 2, 21);
		drawLine(0, 20, 0, 17);

		//block to the left
		drawLine(2, 19, 3, 19);
		drawLine(2, 18, 3, 18);

		//block to the left
		drawLine(5, 17, 5, 20);
		drawLine(6, 17, 6, 20);

		//Middle bottom S
		drawLine(6, 22, 8, 22);
		drawLine(8, 21, 8, 16);
		drawLine(9, 16, 11, 16);

		//Bottom left block
		drawLine(14, 16, 14, 18);
		drawLine(15, 16, 15, 18);

		//Bottom left duck
		drawLine(13, 20, 14, 20);
		drawLine(12, 18, 12, 20);
		drawLine(11, 18, 11, 20);
		drawLine(10, 18, 10, 23);

		//box above S
		drawLine(7, 24, 7, 26);
		drawLine(6, 24, 6, 26);
		drawLine(5, 24, 5, 26);

		//S above duck
		drawLine(15, 22, 12, 22);
		drawLine(12, 23, 12, 26);
		drawLine(11, 26, 9, 26);
		drawLine(11, 25, 9, 25);

		//Above duck S
		drawLine(14, 24, 14, 28);
		drawLine(13, 28, 10, 28);
		drawLine(10, 29, 10, 31);
		drawLine(11, 29, 11, 31);

		//Top Left line
		drawLine(13, 30, 15, 30);
	}
	else if(topRightCorner == 3)
	{
		//Top right box
		drawLine(1, 30, 1, 27);
		drawLine(2, 30, 2, 27);
		drawLine(3, 30, 3, 25);

		//top right mid box
		drawLine(0, 25, 1, 25);
		drawLine(0, 24, 1, 24);

		//bottom right box
		drawLine(0, 20, 0, 17);
		drawLine(1, 20, 1, 17);
		drawLine(2, 17, 3, 17);

		//bottom weird box
		drawLine(1, 22, 5, 22);
		drawLine(3, 21, 5, 21);
		drawLine(3, 20, 5, 20);
		drawLine(3, 19, 5, 19);
		drawLine(5, 18, 5, 16);
		drawLine(7, 16, 5, 16);

		//Bottom big block
		drawLine(9, 23, 9, 17);
		drawLine(8, 23, 8, 18);
		drawLine(7, 23, 7, 18);

		//Bottom left L
		drawLine(11, 16, 11, 19);
		drawLine(12, 16, 13, 16);

		//Bottom left block
		drawLine(13, 18, 13, 20);
		drawLine(14, 18, 14, 20);

		//left mid block
		drawLine(15, 22, 13, 22);
		drawLine(15, 23, 13, 23);

		//line above left mid block
		drawLine(14, 25, 12, 25);

		//Top left L
		drawLine(15, 27, 13, 27);
		drawLine(15, 28, 15, 30);

		//Top middle big block
		drawLine(10, 25, 10, 30);
		drawLine(9, 25, 9, 30);
		drawLine(8, 25, 8, 27);
		drawLine(7, 25, 7, 27);

		//Top Mid Block
		drawLine(5, 26, 5, 31);
		drawLine(6, 29, 6, 31);
		drawLine(7, 29, 7, 31);
	}
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
			requiredSpaces--;

			sendEndGameBad = 0x00;
			sendEndGameGood = 0x00;

			clearBoard();
			if(group == 0)
				fillboardWinTest();
			else
			{
				bottomLeftCornerRandFill();
				bottomRightCornerRandFill();
				topLeftCornerRandFill();
				topRightCornerRandFill();
			}
			//fillBoardBasic();
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