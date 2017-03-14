#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct _Player
{
	unsigned char xPosition;
	unsigned char yPosition;
} Player;

Player player;

unsigned char board[32][32]  = {{0}};

#endif