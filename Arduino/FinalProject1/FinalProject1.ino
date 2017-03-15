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

unsigned char group = 0x01;
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
