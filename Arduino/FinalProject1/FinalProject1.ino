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

    
  }
  else if(bottomRightCorner == 2)
  {

  }
  else if(bottomRightCorner == 3)
  {

  }
}

//Fill top left corner with random grid
void topLeftCornerRandFill()
{
  if(topLeftCorner == 0)
  {

  }
  else if(topLeftCorner == 1)
  {

  }
  else if(topLeftCorner == 2)
  {

  }
  else if(topLeftCorner == 3)
  {

  }
}

//Fill top right corner with random grid
void topRightCornerRandFill()
{
  if(topRightCorner == 0)
  {

  }
  else if(topRightCorner == 1)
  {

  }
  else if(topRightCorner == 2)
  {

  }
  else if(topRightCorner == 3)
  {

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
  //bottomLeftCornerRandFill();
  bottomRightCornerRandFill();
  topLeftCornerRandFill();
  topRightCornerRandFill();
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
  //group = 0;
  group = 1;
  bottomLeftCorner = 0x00;
  bottomRightCorner = 0x01;
  topRightCorner = 0x00;
  topLeftCorner = 0x00;
  
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
