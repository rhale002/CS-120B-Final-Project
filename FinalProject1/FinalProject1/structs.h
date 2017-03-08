#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct _Player
{
	unsigned char xPosition;
	unsigned char yPosition;
} Player;

typedef struct _Obstacle
{
	unsigned char xPosition;
	unsigned char yPosition;
} Obstacle;

Player player;
Obstacle obstacles[8];

#endif