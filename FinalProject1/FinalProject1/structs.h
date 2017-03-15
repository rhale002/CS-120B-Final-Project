#ifndef STRUCTS_H
#define STRUCTS_H

//Object for tracking player positions
typedef struct _Player
{
	unsigned char prevXPosition;
	unsigned char prevYPosition;
	unsigned char xPosition;
	unsigned char yPosition;
} Player;
Player player;

//Board which tracks where you've been/ have not yet been/cannot go to
unsigned char board[32][32]  = {{0}};
	
//Variable to keep track if we should end the game for a loss
unsigned char sendEndGameBad;

//Variable to keep track if we should end the game for a win
unsigned char sendEndGameGood;

//Variable to keep track of sending reset signal to arduino
unsigned char sendResetGame;

//Variable to track if sending reset to win demo
unsigned char sendResetWinDemo;

//Tracks whether to reset all states
unsigned char resetGame;

//Tracks whether to reset to win demo
unsigned char resetGameWinDemo;

//Keeps track of output of joystick (which direction is being input)
//NO INPUT: J_Output == 0x00
//UP:		J_Output == 0x01
//RIGHT:	J_Output == 0x02
//DOWN:		J_Output == 0x03
//LEFT:		J_Output == 0x04
unsigned char J_Direction = 0x00;

//Variable for storing score
unsigned short score;

//Tracks whether to incrementScore
unsigned char incrementScore;

//Track how many spaces need to be filled
unsigned short requiredSpaces;

//Maps Info previous
unsigned char nGroup;
unsigned char nBottomLeftCorner;
unsigned char nBottomRightCorner;
unsigned char nTopRightCorner;
unsigned char nTopLeftCorner;

//Maps Info current
unsigned char group;
unsigned char bottomLeftCorner;
unsigned char bottomRightCorner;
unsigned char topRightCorner;
unsigned char topLeftCorner;

void setBoardToDrawRandom()
{
	group = nGroup;
	bottomLeftCorner = nBottomLeftCorner;
	bottomRightCorner = nBottomRightCorner;
	topRightCorner = nTopRightCorner;
	topLeftCorner = nTopLeftCorner;
	
	nGroup = group == 1 ? 2 : 1;
	nBottomLeftCorner = group == 1 ? rand() % 4 : (rand() % 4) + 4;
	nBottomRightCorner = group == 1 ? rand() % 4 : (rand() % 4) + 4;
	nTopLeftCorner = group == 1 ? rand() % 4 : (rand() % 4) + 4;
	nTopRightCorner = group == 1 ? rand() % 4 : (rand() % 4) + 4;
}

void setBoardToDrawWinDemo()
{
	group = nGroup;
	
	nGroup = 0;
}

#endif