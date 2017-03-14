#ifndef STRUCTS_H
#define STRUCTS_H

//Object for tracking player positions
typedef struct _Player
{
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

//Keeps track of output of joystick (which direction is being input)
//NO INPUT: J_Output == 0x00
//UP:		J_Output == 0x01
//RIGHT:	J_Output == 0x02
//DOWN:		J_Output == 0x03
//LEFT:		J_Output == 0x04
unsigned char J_Direction = 0x00;

#endif