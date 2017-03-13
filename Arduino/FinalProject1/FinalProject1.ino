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

void recieveUSART()
{
  if (USART_Index == 0)         //Player xPosition
  {
    player.xPosition = Serial.read();
    
    ++USART_Index;
  }
  else if (USART_Index == 1)    //Player yPosition
  {
    player.yPosition = Serial.read();
    
    //++USART_Index;
    USART_Index = 0;
  }
}

void drawPlayer()
{
  matrix.drawPixel(player.xPosition, player.yPosition, matrix.Color333(0, 0, 7));
}

void drawBoundaries()
{
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

void setup() 
{
  matrix.begin();

  Serial.begin(9600);
 
  USART_Index = 0;
  
  player.xPosition = 31;
  player.yPosition = 0;

  drawBoundaries();
}

void loop() 
{ 
  if(Serial.available() > 0)
    recieveUSART();
  
  drawPlayer();
  
  matrix.swapBuffers(false);
}
