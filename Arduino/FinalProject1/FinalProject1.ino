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
   matrix.drawLine(18, 14, 31, 14, matrix.Color333(7, 0, 0));
   matrix.drawLine(30, 0, 20, 0, matrix.Color333(7, 0, 0));
   matrix.drawLine(30, 14, 31, 14, matrix.Color333(7, 0, 0));
   matrix.drawLine(30, 1, 30, 11, matrix.Color333(7, 0, 0));
   matrix.drawLine(29, 1, 29, 11, matrix.Color333(7, 0, 0));
   matrix.drawLine(28, 1, 28, 11, matrix.Color333(7, 0, 0));

   //Right lower corner maze
   matrix.drawLine(18, 1, 1, 1, matrix.Color333(7, 0, 0));
   matrix.drawLine(0, 3, 15, 3, matrix.Color333(7, 0, 0));
   matrix.drawLine(1, 5, 16, 5, matrix.Color333(7, 0, 0));
   matrix.drawLine(0, 7, 15, 7, matrix.Color333(7, 0, 0));
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
