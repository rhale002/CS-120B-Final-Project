#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

//Setup LED Matrix
#define CLK 8 
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

//Variables to track USART recieving order
unsigned char USART_Index = 0;

//Struct for player positions
typedef struct _Player
{
  unsigned char xPosition;
  unsigned char yPosition;
} Player;
Player player;

unsigned char recieveEndGameBad = 0x00;
unsigned char recieveEndGameGood = 0x00;
unsigned char recieveResetGame = 0x00;

unsigned char recieveResetGameToWinDemo = 0x00;

unsigned char group = 0x00;
unsigned char bottomLeftCorner = 0x00;
unsigned char bottomRightCorner = 0x00;
unsigned char topRightCorner = 0x00;
unsigned char topLeftCorner = 0x00;

void recieveUSART()
{
  if(USART_Index == 0)      
  {
    group = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 1)   
  {
    bottomLeftCorner = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 2)   
  {
    bottomRightCorner = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 3)   
  {
    topLeftCorner = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 4)
  {
    topRightCorner = Serial.read();
    ++USART_Index;
  }
  else if (USART_Index == 5)         //Player xPosition
  {
    player.xPosition = Serial.read();
    ++USART_Index;
  }
  else if (USART_Index == 6)    //Player yPosition
  {
    player.yPosition = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 7)     //Endgame testing
  {
    recieveEndGameBad = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 8)     //Endgame testing
  {
    recieveEndGameGood = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 9)     //Endgame testing
  {
    recieveResetGame = Serial.read();
    ++USART_Index;
  }
  else if(USART_Index == 10)    //If game should be reset with win demo
  {
    recieveResetGameToWinDemo = Serial.read();
    USART_Index = 0;
  }
}

void drawPlayer()
{
  matrix.drawPixel(player.xPosition, player.yPosition, matrix.Color333(0, 0, 7));
}

/*
void drawBoundaries()
{
  //Basic Board
  //Left lower corner Box
   matrix.drawLine(31, 13, 18, 13, matrix.Color333(7, 0, 0));
   matrix.drawLine(18, 13, 18, 1, matrix.Color333(7, 0, 0));
   matrix.drawLine(17, 1, 17, 14, matrix.Color333(7, 0, 0));
   matrix.drawLine(30, 0, 20, 0, matrix.Color333(7, 0, 0));
   matrix.drawLine(30, 1, 30, 11, matrix.Color333(7, 0, 0));
   matrix.drawLine(29, 1, 29, 11, matrix.Color333(7, 0, 0));
   matrix.drawLine(28, 1, 28, 11, matrix.Color333(7, 0, 0));
   matrix.drawLine(24, 13, 24, 2, matrix.Color333(7, 0, 0));
   matrix.drawLine(23, 13, 23, 2, matrix.Color333(7, 0, 0));
   matrix.drawLine(22, 13, 22, 2, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 13, 21, 2, matrix.Color333(7, 0, 0));

   //Right lower corner maze
   matrix.drawLine(18, 1, 1, 1, matrix.Color333(7, 0, 0));
   matrix.drawLine(0, 3, 15, 3, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 5, 16, 5, matrix.Color333(7, 0, 0));
   matrix.drawLine(0, 7, 15, 7, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 9, 16, 9, matrix.Color333(7, 0, 0));
   matrix.drawLine(0, 11, 15, 11, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 13, 16, 13, matrix.Color333(7, 0, 0));

   //Upper Half line
   matrix.drawLine(31, 14, 1, 14, matrix.Color333(7, 0, 0));

   //Upper right L
   matrix.drawLine(1, 17, 5, 17, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 18, 5, 18, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 19, 5, 19, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 20, 11, 20, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 21, 11, 21, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 22, 11, 22, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 23, 11, 23, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 24, 11, 24, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 25, 11, 25, matrix.Color333(7, 0, 0));

   //Upper right top bar
   matrix.drawLine(1, 28, 18, 28, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 29, 18, 29, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 30, 18, 30, matrix.Color333(7, 0, 0));

   //Upper right lopsided bar
   matrix.drawLine(7, 16, 23, 16, matrix.Color333(7, 0, 0));
   matrix.drawLine(7, 17, 23, 17, matrix.Color333(7, 0, 0));
   matrix.drawLine(7, 18, 12, 18, matrix.Color333(7, 0, 0));
   matrix.drawLine(20, 18, 23, 18, matrix.Color333(7, 0, 0));
   matrix.drawLine(20, 19, 23, 19, matrix.Color333(7, 0, 0));

   //Upper right block
   matrix.drawLine(14, 19, 18, 19, matrix.Color333(7, 0, 0));
   matrix.drawLine(14, 20, 18, 20, matrix.Color333(7, 0, 0));
   matrix.drawLine(14, 21, 18, 21, matrix.Color333(7, 0, 0));
   matrix.drawLine(14, 22, 18, 22, matrix.Color333(7, 0, 0));
   matrix.drawLine(14, 23, 18, 23, matrix.Color333(7, 0, 0));
   matrix.drawLine(14, 24, 18, 24, matrix.Color333(7, 0, 0));
   matrix.drawLine(14, 25, 18, 25, matrix.Color333(7, 0, 0));

   //Upper left bottom left block
   matrix.drawLine(26, 16, 30, 16, matrix.Color333(7, 0, 0));
   matrix.drawLine(26, 17, 30, 17, matrix.Color333(7, 0, 0));
   matrix.drawLine(26, 18, 30, 18, matrix.Color333(7, 0, 0));
   matrix.drawLine(30, 19, 30, 25, matrix.Color333(7, 0, 0));
   matrix.drawLine(29, 25, 25, 25, matrix.Color333(7, 0, 0));

   //Upper left middle block
   matrix.drawLine(25, 20, 28, 20, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 21, 28, 21, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 22, 28, 22, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 23, 28, 23, matrix.Color333(7, 0, 0));

   //Upper left upper right block
   matrix.drawLine(21, 26, 23, 26, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 27, 23, 27, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 28, 23, 28, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 29, 23, 29, matrix.Color333(7, 0, 0));
   matrix.drawLine(21, 30, 23, 30, matrix.Color333(7, 0, 0));

   //Upper left upper left block
   matrix.drawLine(26, 27, 30, 27, matrix.Color333(7, 0, 0));
   matrix.drawLine(26, 28, 30, 28, matrix.Color333(7, 0, 0));
   matrix.drawLine(26, 29, 30, 29, matrix.Color333(7, 0, 0));
   matrix.drawLine(26, 30, 30, 30, matrix.Color333(7, 0, 0));
}
*/

//Fill bottom left corner square with random grid
void bottomLeftCornerRandFill()
{
  if(bottomLeftCorner == 0)
  {
    //top left box
    matrix.drawLine(31, 15, 29, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 14, 29, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 13, 29, 13, matrix.Color333(7, 0, 0));

    //top middle box
    matrix.drawLine(25, 15, 24, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 14, 24, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 13, 24, 13, matrix.Color333(7, 0, 0));

    //top middle right box
    matrix.drawLine(22, 14, 21, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 13, 21, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 12, 21, 12, matrix.Color333(7, 0, 0));
    
    //top right box
    matrix.drawLine(19, 15, 16, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 14, 16, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 13, 18, 13, matrix.Color333(7, 0, 0));

    //top left L
    matrix.drawLine(30, 11, 28, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 11, 27, 14, matrix.Color333(7, 0, 0));

    //spec next to L
    matrix.drawLine(24, 11, 23, 11, matrix.Color333(7, 0, 0));

    //spec below L
    matrix.drawLine(30, 8, 30, 7, matrix.Color333(7, 0, 0));

    //right of below L spec
    matrix.drawLine(28, 9, 28, 6, matrix.Color333(7, 0, 0));

    //Line below spec
    matrix.drawLine(31, 5, 31, 3, matrix.Color333(7, 0, 0));

    //Line Right of left line
    matrix.drawLine(29, 4, 27, 4, matrix.Color333(7, 0, 0));

    //Dot below line
    matrix.drawLine(28, 2, 28, 2, matrix.Color333(7, 0, 0));

    //Lower left L
    matrix.drawLine(30, 1, 30, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 0, 27, 0, matrix.Color333(7, 0, 0));

    //Line right of dot
    matrix.drawLine(25, 5, 25, 1, matrix.Color333(7, 0, 0));

    //Odd right of line
    matrix.drawLine(23, 6, 21, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 7, 21, 7, matrix.Color333(7, 0, 0));

    //Rect right of line
    matrix.drawLine(23, 1, 21, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 0, 21, 0, matrix.Color333(7, 0, 0));

    //rect above rect
    matrix.drawLine(22, 4, 20, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 3, 20, 3, matrix.Color333(7, 0, 0));

    //tall rect right of rect
    matrix.drawLine(18, 0, 18, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 0, 17, 6, matrix.Color333(7, 0, 0));

    //Rect above tall rect
    matrix.drawLine(17, 8, 17, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(16, 8, 16, 10, matrix.Color333(7, 0, 0));

    //square above line
    matrix.drawLine(25, 9, 24, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 8, 24, 8, matrix.Color333(7, 0, 0));

    //Square right of square
    matrix.drawLine(21, 10, 20, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 9, 20, 9, matrix.Color333(7, 0, 0));
  }
  else if(bottomLeftCorner == 1)
  {
    //lower left small line
    matrix.drawLine(30, 0, 30, 1, matrix.Color333(7, 0, 0));

    //Odd Right of small line
    matrix.drawLine(28, 1, 28, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 3, 29, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 4, 30, 4, matrix.Color333(7, 0, 0));

    //big odd right of odd
    matrix.drawLine(28, 5, 25, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 4, 25, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 3, 25, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 2, 25, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 1, 22, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 0, 22, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 0, 21, 10, matrix.Color333(7, 0, 0));

    //Spec inside big odd crevice
    matrix.drawLine(23, 3, 23, 4, matrix.Color333(7, 0, 0));

    //odd L above big odd
    matrix.drawLine(24, 6, 24, 7, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 8, 30, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 9, 29, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 10, 29, 10, matrix.Color333(7, 0, 0));

    // fat base L above odd L
    matrix.drawLine(31, 12, 29, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 13, 29, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 14, 29, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 15, 24, 15, matrix.Color333(7, 0, 0));

    //Side S below odd L
    matrix.drawLine(27, 13, 23, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 13, 22, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 12, 26, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 11, 26, 11, matrix.Color333(7, 0, 0));

    //Square below side S
    matrix.drawLine(24, 11, 23, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 10, 23, 10, matrix.Color333(7, 0, 0));

    //Right of side S
    matrix.drawLine(20, 13, 20, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 14, 18, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 15, 18, 15, matrix.Color333(7, 0, 0));

    //Line below object above
    matrix.drawLine(19, 11, 19, 8, matrix.Color333(7, 0, 0));

    //Box below above line
    matrix.drawLine(20, 6, 17, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 5, 17, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 4, 17, 4, matrix.Color333(7, 0, 0));

    //Line spec left below box
    matrix.drawLine(19, 2, 19, 1, matrix.Color333(7, 0, 0));

    //Spec right of spec
    matrix.drawLine(17, 1, 17, 0, matrix.Color333(7, 0, 0));
  }
  else if(bottomLeftCorner == 2)
  {
    //lower left rect
    matrix.drawLine(29, 1, 25, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 2, 25, 2, matrix.Color333(7, 0, 0));

    //rect above rect
    matrix.drawLine(30, 4, 27, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 5, 27, 5, matrix.Color333(7, 0, 0));

    //Rect of left middle
    matrix.drawLine(31, 7, 28, 7, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 8, 28, 8, matrix.Color333(7, 0, 0));

    //odd above left middle rect
    matrix.drawLine(26, 9, 24, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 10, 24, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 11, 24, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 12, 27, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(28, 13, 27, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(28, 14, 27, 14, matrix.Color333(7, 0, 0));

    //square above odd
    matrix.drawLine(31, 14, 30, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 15, 30, 15, matrix.Color333(7, 0, 0));

    //Square right of odd
    matrix.drawLine(25, 15, 23, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 14, 23, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 13, 23, 13, matrix.Color333(7, 0, 0));

    //Big square to the right
    matrix.drawLine(21, 14, 19, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 13, 17, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 12, 17, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 11, 17, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 10, 17, 10, matrix.Color333(7, 0, 0));

    //Sqaure below big square
    matrix.drawLine(19, 8, 16, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 7, 16, 7, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 6, 19, 6, matrix.Color333(7, 0, 0));

    //Big odd below square
    matrix.drawLine(23, 0, 21, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 1, 21, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 2, 17, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 3, 17, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 4, 17, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 5, 17, 5, matrix.Color333(7, 0, 0));

    //Middle 
    matrix.drawLine(25, 6, 22, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 7, 22, 7, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 8, 22, 8, matrix.Color333(7, 0, 0));
  }
  else if(bottomLeftCorner == 3)
  {
    //Big bottom left square
    matrix.drawLine(30, 0, 28, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 1, 28, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 2, 28, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 3, 28, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 4, 28, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 5, 28, 5, matrix.Color333(7, 0, 0));

    //Odd right of bottom left square
    matrix.drawLine(26, 1, 24, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 2, 24, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 3, 24, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 4, 24, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 5, 24, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 6, 24, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 7, 24, 7, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 7, 31, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 14, 28, 14, matrix.Color333(7, 0, 0));

    //Square in odd crevice
    matrix.drawLine(26, 13, 26, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 12, 26, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 11, 26, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 10, 26, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 9, 26, 9, matrix.Color333(7, 0, 0));

    //spec near odd
    matrix.drawLine(24, 10, 23, 10, matrix.Color333(7, 0, 0));

    //Square above spec
    matrix.drawLine(23, 12, 22, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 13, 22, 13, matrix.Color333(7, 0, 0));

    //Line to right of square
    matrix.drawLine(20, 14, 20, 10, matrix.Color333(7, 0, 0));

    //Line right of line
    matrix.drawLine(18, 13, 18, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 8, 19, 6, matrix.Color333(7, 0, 0));

    //line left of line
    matrix.drawLine(22, 8, 22, 5, matrix.Color333(7, 0, 0));

    //box below line
    matrix.drawLine(20, 4, 19, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 3, 19, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 2, 19, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 1, 19, 1, matrix.Color333(7, 0, 0));

    //Top mess up line
    matrix.drawLine(31, 15, 16, 15, matrix.Color333(7, 0, 0));

    //right line below mess up
    matrix.drawLine(17, 13, 17, 8, matrix.Color333(7, 0, 0));

    //spec below line
    matrix.drawLine(16, 6, 16, 5, matrix.Color333(7, 0, 0));

    //Left of line verticle line
    matrix.drawLine(18, 3, 18, 1, matrix.Color333(7, 0, 0));

    //Fix line
    matrix.drawLine(16, 4, 18, 4, matrix.Color333(7, 0, 0));
  }
}

//Fill bottom right corner with random grid
void bottomRightCornerRandFill()
{
  if(bottomRightCorner == 0)
  {
    //bottom right rect
    matrix.drawLine(3, 2, 1, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 3, 1, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 4, 1, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 5, 1, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 6, 1, 6, matrix.Color333(7, 0, 0));

    //Bottom right S
    matrix.drawLine(4, 0, 2, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(5, 0, 5, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 5, 5, 5, matrix.Color333(7, 0, 0));

    //Left of S
    matrix.drawLine(8, 3, 7, 3, matrix.Color333(7, 0, 0));
    matrix.drawLine(10, 2, 7, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(10, 1, 7, 1, matrix.Color333(7, 0, 0));

    //Left of box
    matrix.drawLine(15, 1, 13, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(15, 2, 13, 2, matrix.Color333(7, 0, 0));

    //Big box above
    matrix.drawLine(14, 4, 10, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 5, 10, 5, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 6, 10, 6, matrix.Color333(7, 0, 0));

    //long odd above
    matrix.drawLine(15, 13, 15, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 13, 14, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(13, 8, 9, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(10, 9, 9, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(10, 10, 3, 10, matrix.Color333(7, 0, 0));
    matrix.drawLine(4, 9, 3, 9, matrix.Color333(7, 0, 0));

    //Spec inside odd long
    matrix.drawLine(6, 8, 7, 8, matrix.Color333(7, 0, 0));

    //top right big odd
    matrix.drawLine(0, 8, 0, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(1, 8, 1, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(6, 12, 2, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(6, 13, 5, 13, matrix.Color333(7, 0, 0));

    //Above right big odd
    matrix.drawLine(2, 14, 3, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(2, 15, 9, 15, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 14, 9, 14, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 13, 9, 13, matrix.Color333(7, 0, 0));

    //Left of that shit
    matrix.drawLine(11, 14, 11, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(12, 14, 12, 10, matrix.Color333(7, 0, 0));
  }
  else if(bottomRightCorner == 1)
  {
    //Bottom right oddball 
    matrix.drawLine(0, 0, 0, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(1, 11, 4, 11, matrix.Color333(7, 0, 0));
    matrix.drawLine(1, 0, 4, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(1, 1, 4, 1, matrix.Color333(7, 0, 0));

    //Inside crevice
    matrix.drawLine(2, 3, 2, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 3, 3, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(4, 9, 5, 9, matrix.Color333(7, 0, 0));

    //middle bottom
    matrix.drawLine(6, 1, 6, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 1, 7, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 5, 8, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 5, 9, 6, matrix.Color333(7, 0, 0));

    //Bottom left
    matrix.drawLine(9, 0, 13, 0, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 1, 13, 1, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 2, 11, 2, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 3, 11, 3, matrix.Color333(7, 0, 0));

    //little up bottom left
    matrix.drawLine(15, 1, 15, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 3, 14, 4, matrix.Color333(7, 0, 0));
    matrix.drawLine(13, 3, 13, 4, matrix.Color333(7, 0, 0));

    //above that shit 
    matrix.drawLine(14, 6, 11, 6, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 7, 11, 7, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 8, 13, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 9, 13, 9, matrix.Color333(7, 0, 0));

    //box above the left middle box
    matrix.drawLine(11, 9, 9, 9, matrix.Color333(7, 0, 0));
    matrix.drawLine(11, 10, 9, 10, matrix.Color333(7, 0, 0));

    //Big ass shit above
    matrix.drawLine(7, 11, 7, 8, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 12, 7, 12, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 13, 7, 13, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 14, 7, 14, matrix.Color333(7, 0, 0));

    //top right line
    matrix.drawLine(1, 13, 5, 13, matrix.Color333(7, 0, 0));
  }
  else if(bottomRightCorner == 2)
  {
     //bottom right L
     matrix.drawLine(0, 0, 0, 5, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 5, 1, 5, matrix.Color333(7, 0, 0));

     //bottom right rect
     matrix.drawLine(2, 1, 3, 1, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 2, 3, 2, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 3, 3, 3, matrix.Color333(7, 0, 0));

     //Fat Butt L
     matrix.drawLine(5, 0, 5, 6, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 5, 8, 5, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 6, 8, 6, matrix.Color333(7, 0, 0));

     //Under dat booty
     matrix.drawLine(7, 1, 7, 3, matrix.Color333(7, 0, 0));
     matrix.drawLine(8, 2, 8, 3, matrix.Color333(7, 0, 0));
     matrix.drawLine(9, 2, 9, 3, matrix.Color333(7, 0, 0));

     //Left of da booty
     matrix.drawLine(10, 4, 10, 5, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 4, 11, 5, matrix.Color333(7, 0, 0));
     matrix.drawLine(12, 4, 12, 5, matrix.Color333(7, 0, 0));

     //Bottom left corner box
     matrix.drawLine(9, 0, 13, 0, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 1, 13, 1, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 2, 13, 2, matrix.Color333(7, 0, 0));

     //Bottom left line
     matrix.drawLine(15, 1, 15, 3, matrix.Color333(7, 0, 0));

     //Bottom Left L
     matrix.drawLine(14, 5, 14, 7, matrix.Color333(7, 0, 0));
     matrix.drawLine(13, 7, 11, 7, matrix.Color333(7, 0, 0));

     //Above the L
     matrix.drawLine(15, 9, 12, 9, matrix.Color333(7, 0, 0));

     //Big top left corner box
     matrix.drawLine(14, 11, 9, 11, matrix.Color333(7, 0, 0));
     matrix.drawLine(14, 12, 9, 12, matrix.Color333(7, 0, 0));
     matrix.drawLine(14, 13, 9, 13, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 14, 9, 14, matrix.Color333(7, 0, 0));

     //top right box
     matrix.drawLine(7, 15, 1, 15, matrix.Color333(7, 0, 0));
     matrix.drawLine(7, 14, 1, 14, matrix.Color333(7, 0, 0));
     matrix.drawLine(7, 13, 6, 13, matrix.Color333(7, 0, 0));

     //Top right little lower box
     matrix.drawLine(0, 12, 4, 12, matrix.Color333(7, 0, 0));
     matrix.drawLine(0, 11, 6, 11, matrix.Color333(7, 0, 0));

     //middle long box
     matrix.drawLine(1, 9, 9, 9, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 8, 9, 8, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 7, 3, 7, matrix.Color333(7, 0, 0));

     //top right line
     matrix.drawLine(15, 15, 12, 15, matrix.Color333(7, 0, 0));
  }
  else if(bottomRightCorner == 3)
  {
     //Bottom right box
     matrix.drawLine(1, 1, 4, 1, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 2, 3, 2, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 3, 3, 3, matrix.Color333(7, 0, 0));

     //bottom middle box
     matrix.drawLine(7, 1, 7, 3, matrix.Color333(7, 0, 0));
     matrix.drawLine(8, 1, 8, 3, matrix.Color333(7, 0, 0));

     //above L
     matrix.drawLine(5, 3, 5, 5, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 5, 7, 5, matrix.Color333(7, 0, 0));

     //Bottom left block
     matrix.drawLine(10, 4, 14, 4, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 3, 14, 3, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 2, 11, 2, matrix.Color333(7, 0, 0));

     //Bottom left line
     matrix.drawLine(13, 1, 15, 1, matrix.Color333(7, 0, 0));

     //Left middle weird
     matrix.drawLine(15, 6, 9, 6, matrix.Color333(7, 0, 0));
     matrix.drawLine(15, 7, 14, 7, matrix.Color333(7, 0, 0));
     matrix.drawLine(15, 8, 14, 8, matrix.Color333(7, 0, 0));
     matrix.drawLine(15, 9, 14, 9, matrix.Color333(7, 0, 0));
     matrix.drawLine(15, 10, 11, 10, matrix.Color333(7, 0, 0));

     //Crevice L
     matrix.drawLine(12, 8, 9, 8, matrix.Color333(7, 0, 0));
     matrix.drawLine(9, 9, 9, 11, matrix.Color333(7, 0, 0));

     //Top left box
     matrix.drawLine(12, 12, 14, 12, matrix.Color333(7, 0, 0));
     matrix.drawLine(12, 13, 14, 13, matrix.Color333(7, 0, 0));
     matrix.drawLine(12, 14, 14, 14, matrix.Color333(7, 0, 0));

     //Top middle box
     matrix.drawLine(10, 15, 8, 15, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 14, 8, 14, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 13, 8, 13, matrix.Color333(7, 0, 0));

     //Top middle L
     matrix.drawLine(6, 14, 6, 12, matrix.Color333(7, 0, 0));
     matrix.drawLine(5, 12, 3, 12, matrix.Color333(7, 0, 0));

     //Top right box
     matrix.drawLine(4, 15, 1, 15, matrix.Color333(7, 0, 0));
     matrix.drawLine(4, 14, 2, 14, matrix.Color333(7, 0, 0));

     //top right spec
     matrix.drawLine(0, 13, 0, 12, matrix.Color333(7, 0, 0));

     //middle box
     matrix.drawLine(1, 10, 7, 10, matrix.Color333(7, 0, 0));
     matrix.drawLine(4, 9, 7, 9, matrix.Color333(7, 0, 0));
     matrix.drawLine(4, 8, 7, 8, matrix.Color333(7, 0, 0));
     matrix.drawLine(4, 7, 7, 7, matrix.Color333(7, 0, 0));

     //Middle Right box
     matrix.drawLine(0, 5, 0, 8, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 5, 1, 8, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 5, 2, 8, matrix.Color333(7, 0, 0));
  }
}

//Fill top left corner with random grid
void topLeftCornerRandFill()
{
  if(topLeftCorner == 0)
  {
    //Top Left box
    matrix.drawLine(31, 31, 26, 31, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 30, 26, 24, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 30, 27, 24, matrix.Color333(7, 0, 0));

    //Top Left left box
    matrix.drawLine(30, 29, 30, 23, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 29, 29, 23, matrix.Color333(7, 0, 0));

    //bottom left L
    matrix.drawLine(30, 20, 30, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 17, 25, 17, matrix.Color333(7, 0, 0));

    //Bottom left box
    matrix.drawLine(28, 21, 28, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 21, 27, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 21, 26, 19, matrix.Color333(7, 0, 0));

    //bottom middle box
    matrix.drawLine(23, 16, 23, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 16, 22, 18, matrix.Color333(7, 0, 0));

    //Bottom right box
    matrix.drawLine(20, 17, 17, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 18, 17, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 18, 18, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 20, 23, 20, matrix.Color333(7, 0, 0));

    //right middle box
    matrix.drawLine(18, 22, 24, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 23, 18, 26, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 23, 19, 26, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 23, 20, 26, matrix.Color333(7, 0, 0));

    //Middle box
    matrix.drawLine(22, 24, 22, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 24, 23, 27, matrix.Color333(7, 0, 0));

    //Top middle box
    matrix.drawLine(24, 29, 22, 29, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 30, 22, 30, matrix.Color333(7, 0, 0));

    //top right box
    matrix.drawLine(18, 31, 18, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 31, 19, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 31, 20, 28, matrix.Color333(7, 0, 0));

    //Top Right Line
    matrix.drawLine(16, 30, 16, 27, matrix.Color333(7, 0, 0));
  }
  else if(topLeftCorner == 1)
  {
    //big top left box
    matrix.drawLine(30, 30, 18, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 29, 26, 29, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 28, 26, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 27, 26, 27, matrix.Color333(7, 0, 0));

    //big middle left box
    matrix.drawLine(31, 25, 26, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 24, 26, 24, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 23, 29, 23, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 22, 29, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 21, 29, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(31, 20, 29, 20, matrix.Color333(7, 0, 0));

    //bottom left box
    matrix.drawLine(30, 18, 28, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 17, 28, 17, matrix.Color333(7, 0, 0));

    //bottom middle box
    matrix.drawLine(26, 16, 26, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 16, 25, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 16, 24, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 21, 22, 21, matrix.Color333(7, 0, 0));

    //Bottom right mid block
    matrix.drawLine(21, 17, 21, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 17, 22, 19, matrix.Color333(7, 0, 0));

    //Bottom Right block
    matrix.drawLine(17, 17, 17, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 17, 18, 19, matrix.Color333(7, 0, 0));

    //Right middle block
    matrix.drawLine(18, 21, 18, 23, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 21, 19, 23, matrix.Color333(7, 0, 0));

    //middle box
    matrix.drawLine(21, 23, 24, 23, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 24, 24, 24, matrix.Color333(7, 0, 0));

    //top right box
    matrix.drawLine(17, 26, 17, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 26, 18, 25, matrix.Color333(7, 0, 0));

    // top right middle box
    matrix.drawLine(19, 28, 24, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 27, 24, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 26, 24, 26, matrix.Color333(7, 0, 0));

    //Top right line
    matrix.drawLine(16, 30, 16, 28, matrix.Color333(7, 0, 0));
  }
  else if(topLeftCorner == 2)
  {
    //top left box
    matrix.drawLine(30, 30, 26, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 29, 26, 29, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 28, 26, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 27, 28, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 26, 28, 26, matrix.Color333(7, 0, 0));

    //Bottom left box
    matrix.drawLine(30, 24, 30, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 24, 29, 17, matrix.Color333(7, 0, 0));

    //bottom left box
    matrix.drawLine(27, 18, 26, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 19, 26, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 20, 24, 20, matrix.Color333(7, 0, 0));

    //bottom middle block
    matrix.drawLine(24, 17, 23, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 18, 23, 18, matrix.Color333(7, 0, 0));

    //above spec
    matrix.drawLine(22, 20, 22, 21, matrix.Color333(7, 0, 0));

    //Bottom right box
    matrix.drawLine(19, 16, 19, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 16, 20, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 16, 21, 18, matrix.Color333(7, 0, 0));

    //Bottom right line
    matrix.drawLine(17, 17, 17, 19, matrix.Color333(7, 0, 0));

    //Bottom right mid box
    matrix.drawLine(16, 21, 20, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(16, 22, 20, 22, matrix.Color333(7, 0, 0));

    //right mid box
    matrix.drawLine(17, 24, 17, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 24, 18, 25, matrix.Color333(7, 0, 0));

    //right top box
    matrix.drawLine(17, 31, 19, 31, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 30, 19, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 29, 19, 29, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 28, 19, 28, matrix.Color333(7, 0, 0));

    //Top middle box
    matrix.drawLine(20, 26, 20, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 30, 21, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(22, 30, 22, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 30, 23, 25, matrix.Color333(7, 0, 0));

    //Middle block
    matrix.drawLine(25, 24, 25, 26, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 24, 26, 26, matrix.Color333(7, 0, 0));
  }
  else if(topLeftCorner == 3)
  {
    //Top left line
    matrix.drawLine(31, 31, 24, 31, matrix.Color333(7, 0, 0));

    //top left 2nd low line
    matrix.drawLine(31, 29, 25, 29, matrix.Color333(7, 0, 0));

    //below 2nd line
    matrix.drawLine(30, 27, 24, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(28, 26, 27, 26, matrix.Color333(7, 0, 0));
    matrix.drawLine(28, 25, 27, 25, matrix.Color333(7, 0, 0));

    //Left mid block
    matrix.drawLine(31, 25, 31, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 25, 30, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(29, 23, 29, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(28, 23, 28, 22, matrix.Color333(7, 0, 0));

    //Bottom left block
    matrix.drawLine(31, 19, 31, 16, matrix.Color333(7, 0, 0));
    matrix.drawLine(30, 19, 30, 16, matrix.Color333(7, 0, 0));

    //bottom left tetris block
    matrix.drawLine(28, 17, 28, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(27, 17, 27, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(26, 19, 26, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 19, 25, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(24, 19, 24, 22, matrix.Color333(7, 0, 0));

    //Bottom mid block
    matrix.drawLine(25, 16, 24, 16, matrix.Color333(7, 0, 0));
    matrix.drawLine(25, 17, 24, 17, matrix.Color333(7, 0, 0));

    //Bottom right block
    matrix.drawLine(17, 17, 22, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(17, 18, 22, 18, matrix.Color333(7, 0, 0));

    //Bottom right line
    matrix.drawLine(19, 20, 22, 20, matrix.Color333(7, 0, 0));

    //Big top right block
    matrix.drawLine(17, 22, 17, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(18, 22, 18, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(19, 22, 19, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(20, 22, 20, 31, matrix.Color333(7, 0, 0));
    matrix.drawLine(21, 22, 21, 31, matrix.Color333(7, 0, 0));

    //Top right box
    matrix.drawLine(16, 30, 18, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(16, 29, 18, 29, matrix.Color333(7, 0, 0));

    //middle box
    matrix.drawLine(23, 25, 25, 25, matrix.Color333(7, 0, 0));
    matrix.drawLine(23, 24, 25, 24, matrix.Color333(7, 0, 0));
  }
}

//Fill top right corner with random grid
void topRightCornerRandFill()
{
  if(topRightCorner == 0)
  {
     //Top right box
     matrix.drawLine(0, 31, 0, 25, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 31, 1, 30, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 31, 2, 30, matrix.Color333(7, 0, 0));
     matrix.drawLine(3, 31, 3, 30, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 26, 1, 25, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 26, 2, 25, matrix.Color333(7, 0, 0));

     //Weird middle right box
     matrix.drawLine(2, 28, 4, 28, matrix.Color333(7, 0, 0));
     matrix.drawLine(4, 27, 4, 24, matrix.Color333(7, 0, 0));
     matrix.drawLine(5, 23, 1, 23, matrix.Color333(7, 0, 0));
     matrix.drawLine(5, 22, 1, 22, matrix.Color333(7, 0, 0));
     matrix.drawLine(5, 21, 1, 21, matrix.Color333(7, 0, 0));

     //line to the left
     matrix.drawLine(6, 29, 6, 25, matrix.Color333(7, 0, 0));

     //Bottom right sqaure
     matrix.drawLine(0, 19, 1, 19, matrix.Color333(7, 0, 0));
     matrix.drawLine(0, 18, 1, 18, matrix.Color333(7, 0, 0));

     //Bottom left little middle box
     matrix.drawLine(4, 19, 4, 17, matrix.Color333(7, 0, 0));
     matrix.drawLine(5, 19, 5, 17, matrix.Color333(7, 0, 0));

     //bottom middle line
     matrix.drawLine(7, 18, 7, 16, matrix.Color333(7, 0, 0));

     //bottom left middle box
     matrix.drawLine(10, 18, 10, 19, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 18, 11, 19, matrix.Color333(7, 0, 0));

     //bottom left L
     matrix.drawLine(13, 18, 13, 17, matrix.Color333(7, 0, 0));
     matrix.drawLine(14, 17, 14, 17, matrix.Color333(7, 0, 0));

     //bottom left up mid box
     matrix.drawLine(15, 19, 15, 21, matrix.Color333(7, 0, 0));
     matrix.drawLine(14, 20, 14, 21, matrix.Color333(7, 0, 0));

     //mid left box
     matrix.drawLine(12, 21, 11, 21, matrix.Color333(7, 0, 0));
     matrix.drawLine(12, 22, 11, 22, matrix.Color333(7, 0, 0));
     matrix.drawLine(14, 23, 11, 23, matrix.Color333(7, 0, 0));

     //Mid left spec
     matrix.drawLine(13, 25, 12, 25, matrix.Color333(7, 0, 0));

     //middle long box
     matrix.drawLine(9, 22, 9, 30, matrix.Color333(7, 0, 0));
     matrix.drawLine(8, 22, 8, 30, matrix.Color333(7, 0, 0));

     //bottom spec
     matrix.drawLine(8, 20, 7, 20, matrix.Color333(7, 0, 0));

     // top left Brace
     matrix.drawLine(14, 27, 12, 27, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 27, 11, 31, matrix.Color333(7, 0, 0));
     matrix.drawLine(14, 31, 12, 31, matrix.Color333(7, 0, 0));

     //Top left line
     matrix.drawLine(15, 29, 13, 29, matrix.Color333(7, 0, 0));
  }
  else if(topRightCorner == 1)
  {
    //top right box
    matrix.drawLine(1, 30, 1, 23, matrix.Color333(7, 0, 0));
    matrix.drawLine(2, 30, 2, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 30, 3, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 23, 2, 23, matrix.Color333(7, 0, 0));

    //spec in crevice
    matrix.drawLine(3, 25, 4, 25, matrix.Color333(7, 0, 0));

    //middle weird thing
    matrix.drawLine(7, 28, 9, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 27, 8, 24, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 27, 9, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 24, 6, 24, matrix.Color333(7, 0, 0));

    //top middle box
    matrix.drawLine(6, 26, 5, 26, matrix.Color333(7, 0, 0));
    matrix.drawLine(5, 27, 5, 31, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 30, 6, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 31, 6, 31, matrix.Color333(7, 0, 0));

    //bottom up middle block
    matrix.drawLine(0, 21, 0, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(1, 21, 1, 18, matrix.Color333(7, 0, 0));

    //Bottom right line
    matrix.drawLine(1, 16, 4, 16, matrix.Color333(7, 0, 0));

    //L left of block
    matrix.drawLine(3, 20, 3, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(4, 20, 5, 20, matrix.Color333(7, 0, 0));

    //L left of L
    matrix.drawLine(7, 21, 7, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(6, 22, 5, 22, matrix.Color333(7, 0, 0));

    //bottom mid block
    matrix.drawLine(6, 17, 8, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(5, 18, 8, 18, matrix.Color333(7, 0, 0));

    //bottom left line
    matrix.drawLine(11, 17, 14, 17, matrix.Color333(7, 0, 0));

    //Bottom left mid line
    matrix.drawLine(12, 19, 15, 19, matrix.Color333(7, 0, 0));

    //Mid left block
    matrix.drawLine(11, 21, 13, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(11, 22, 13, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 21, 14, 24, matrix.Color333(7, 0, 0));

    //top left block
    matrix.drawLine(12, 24, 12, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(13, 26, 13, 28, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 26, 14, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(15, 26, 15, 30, matrix.Color333(7, 0, 0));
  }
  else if(topRightCorner == 2)
  {
     //Top Right box
     matrix.drawLine(1, 30, 8, 30, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 29, 8, 29, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 28, 8, 28, matrix.Color333(7, 0, 0));

     //Top right line
     matrix.drawLine(0, 28, 4, 28, matrix.Color333(7, 0, 0));

     //Right mid box
     matrix.drawLine(1, 26, 3, 26, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 25, 3, 25, matrix.Color333(7, 0, 0));
     matrix.drawLine(1, 24, 3, 24, matrix.Color333(7, 0, 0));

     // right mid low block
     matrix.drawLine(0, 22, 2, 22, matrix.Color333(7, 0, 0));
     matrix.drawLine(0, 21, 2, 21, matrix.Color333(7, 0, 0));
     matrix.drawLine(0, 20, 0, 17, matrix.Color333(7, 0, 0));

     //block to the left
     matrix.drawLine(2, 19, 3, 19, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 18, 3, 18, matrix.Color333(7, 0, 0));

     //block to the left
     matrix.drawLine(5, 17, 5, 20, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 17, 6, 20, matrix.Color333(7, 0, 0));

     //Middle bottom S
     matrix.drawLine(6, 22, 8, 22, matrix.Color333(7, 0, 0));
     matrix.drawLine(8, 21, 8, 16, matrix.Color333(7, 0, 0));
     matrix.drawLine(9, 16, 11, 16, matrix.Color333(7, 0, 0));

     //Bottom left block
     matrix.drawLine(14, 16, 14, 18, matrix.Color333(7, 0, 0));
     matrix.drawLine(15, 16, 15, 18, matrix.Color333(7, 0, 0));

     //Bottom left duck
     matrix.drawLine(13, 20, 14, 20, matrix.Color333(7, 0, 0));
     matrix.drawLine(12, 18, 12, 20, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 18, 11, 20, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 18, 10, 23, matrix.Color333(7, 0, 0));

     //box above S
     matrix.drawLine(7, 24, 7, 26, matrix.Color333(7, 0, 0));
     matrix.drawLine(6, 24, 6, 26, matrix.Color333(7, 0, 0));
     matrix.drawLine(5, 24, 5, 26, matrix.Color333(7, 0, 0));

     //S above duck
     matrix.drawLine(15, 22, 12, 22, matrix.Color333(7, 0, 0));
     matrix.drawLine(12, 23, 12, 26, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 26, 9, 26, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 25, 9, 25, matrix.Color333(7, 0, 0));

     //Above duck S
     matrix.drawLine(14, 24, 14, 28, matrix.Color333(7, 0, 0));
     matrix.drawLine(13, 28, 10, 28, matrix.Color333(7, 0, 0));
     matrix.drawLine(10, 29, 10, 31, matrix.Color333(7, 0, 0));
     matrix.drawLine(11, 29, 11, 31, matrix.Color333(7, 0, 0));

     //Top Left line
     matrix.drawLine(13, 30, 15, 30, matrix.Color333(7, 0, 0));
  }
  else if(topRightCorner == 3)
  {
     //Top right box
     matrix.drawLine(1, 30, 1, 27, matrix.Color333(7, 0, 0));
     matrix.drawLine(2, 30, 2, 27, matrix.Color333(7, 0, 0));
     matrix.drawLine(3, 30, 3, 25, matrix.Color333(7, 0, 0));

     //top right mid box
     matrix.drawLine(0, 25, 1, 25, matrix.Color333(7, 0, 0));
     matrix.drawLine(0, 24, 1, 24, matrix.Color333(7, 0, 0));

    //bottom right box
    matrix.drawLine(0, 20, 0, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(1, 20, 1, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(2, 17, 3, 17, matrix.Color333(7, 0, 0));

    //bottom weird box
    matrix.drawLine(1, 22, 5, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 21, 5, 21, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 20, 5, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(3, 19, 5, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(5, 18, 5, 16, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 16, 5, 16, matrix.Color333(7, 0, 0));

    //Bottom big block
    matrix.drawLine(9, 23, 9, 17, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 23, 8, 18, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 23, 7, 18, matrix.Color333(7, 0, 0));

    //Bottom left L
    matrix.drawLine(11, 16, 11, 19, matrix.Color333(7, 0, 0));
    matrix.drawLine(12, 16, 13, 16, matrix.Color333(7, 0, 0));

    //Bottom left block
    matrix.drawLine(13, 18, 13, 20, matrix.Color333(7, 0, 0));
    matrix.drawLine(14, 18, 14, 20, matrix.Color333(7, 0, 0));

    //left mid block
    matrix.drawLine(15, 22, 13, 22, matrix.Color333(7, 0, 0));
    matrix.drawLine(15, 23, 13, 23, matrix.Color333(7, 0, 0));

    //line above left mid block
    matrix.drawLine(14, 25, 12, 25, matrix.Color333(7, 0, 0));

    //Top left L
    matrix.drawLine(15, 27, 13, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(15, 28, 15, 30, matrix.Color333(7, 0, 0));

    //Top middle big block
    matrix.drawLine(10, 25, 10, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(9, 25, 9, 30, matrix.Color333(7, 0, 0));
    matrix.drawLine(8, 25, 8, 27, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 25, 7, 27, matrix.Color333(7, 0, 0));

    //Top Mid Block
    matrix.drawLine(5, 26, 5, 31, matrix.Color333(7, 0, 0));
    matrix.drawLine(6, 29, 6, 31, matrix.Color333(7, 0, 0));
    matrix.drawLine(7, 29, 7, 31, matrix.Color333(7, 0, 0));
  }
}

void drawWinDemo()
{
  //Win Demo Board
  matrix.drawLine(31, 5, 31, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(30, 0, 30, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(29, 0, 29, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(28, 0, 28, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(27, 0, 27, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(26, 0, 26, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(25, 0, 25, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(24, 0, 24, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(23, 0, 23, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(22, 0, 22, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(21, 0, 21, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(20, 0, 20, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(19, 0, 19, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(18, 0, 18, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(17, 0, 17, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(16, 0, 16, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(15, 0, 15, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(14, 0, 14, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(13, 0, 13, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(12, 0, 12, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(11, 0, 11, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(10, 0, 10, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(9, 0, 9, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(8, 0, 8, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(7, 0, 7, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(6, 0, 6, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(5, 0, 5, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(4, 0, 4, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(3, 0, 3, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(2, 0, 2, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(1, 0, 1, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(0, 0, 0, 31, matrix.Color333(7, 0, 0));
}

void drawRandBoard()
{
//  bottomLeftCornerRandFill();
//  bottomRightCornerRandFill();
  topLeftCornerRandFill();
//  topRightCornerRandFill();
}

void reset()
{
  Serial.flush();
  
  USART_Index = 0;
  
  player.xPosition = 31;
  player.yPosition = 0;
  
  recieveEndGameBad = 0x00;
  recieveEndGameGood = 0x00;
  recieveResetGame = 0x00;
  recieveResetGameToWinDemo = 0x00;

  matrix.fillScreen(0);

  if(group == 0)
    drawWinDemo();
  else 
    drawRandBoard();
}

void setup() 
{
  matrix.begin();

  Serial.begin(9600);

  //FIXME TESTING!!!!!
//  group = 0;
  group = 1;
  bottomLeftCorner = 0x00;
  bottomRightCorner = 0x00;
  topRightCorner = 0x00;
  topLeftCorner = 0x03;
  
  reset();
}

void loop() 
{ 
  if(Serial.available() > 0)
    recieveUSART();
    
  if(recieveResetGame == 0x01 || recieveResetGameToWinDemo == 0x01)
  {
    reset();
  }
  else if(recieveEndGameBad == 0x00 && recieveEndGameGood == 0x00)
  {
    drawPlayer();
  }
  else if(recieveEndGameBad == 0x01)
  {
    recieveEndGameBad == 0xFF;
  }
  else if(recieveEndGameGood == 0x01)
  {
    recieveEndGameGood == 0xFF;
  }
  else if(recieveEndGameBad == 0xFF || recieveEndGameGood == 0xFF)
  {}
  
  matrix.swapBuffers(false);
}
