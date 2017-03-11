#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

//Setup LED Matrix
#define CLK 8 
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

//Variable to store incomingByte from USART
int incomingByte = 0;

//Variables to track USART recieving order
unsigned int USART_Index = 0;
unsigned int obstacleIndex = 0;

//Struct for player positions
typedef struct _Player
{
  unsigned int xPosition;
  unsigned int yPosition;
} Player;
Player player;

//Struct for obstacles' positions
typedef struct _Obstacle
{
  unsigned int xPosition;
  unsigned int yPosition;
} Obstacle;
Obstacle obstacles[8];

void recieveUSART()
{
  if (USART_Index == 0 && Serial.available() > 0)         //Player xPosition
  {
    incomingByte = Serial.read();
    player.xPosition = incomingByte;
    
    ++USART_Index;
  }
  else if (USART_Index == 1 && Serial.available() > 0)    //Player yPosition
  {
    incomingByte = Serial.read();
    player.yPosition = incomingByte;
    
    ++USART_Index;
  }
  else if (USART_Index == 2 && Serial.available() > 0)    //Obstacle 0 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 3 && Serial.available() > 0)   //Obstacle 0 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 4 && Serial.available() > 0)    //Obstacle 1 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 5 && Serial.available() > 0)   //Obstacle 1 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 6 && Serial.available() > 0)    //Obstacle 2 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 7 && Serial.available() > 0)   //Obstacle 2 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 8 && Serial.available() > 0)    //Obstacle 3 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 9 && Serial.available() > 0)   //Obstacle 3 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 10 && Serial.available() > 0)   //Obstacle 4 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 11 && Serial.available() > 0) //Obstacle 4 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 12 && Serial.available() > 0)   //Obstacle 5 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 13 && Serial.available() > 0) //Obstacle 5 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 14 && Serial.available() > 0)   //Obstacle 6 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 15 && Serial.available() > 0) //Obstacle 6 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    ++obstacleIndex;
    ++USART_Index;
  }
  else if (USART_Index == 16 && Serial.available() > 0)   //Obstacle 7 xPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].xPosition = incomingByte;
    
    ++USART_Index;
  }
   else if (USART_Index == 17 && Serial.available() > 0) //Obstacle 7 yPosition
  {
    incomingByte = Serial.read();
    obstacles[obstacleIndex].yPosition = incomingByte;
    
    obstacleIndex = 0;
    USART_Index = 0;
  }
}

void drawPlayer()
{
  matrix.fillRect(player.xPosition, player.yPosition, 2, 2, matrix.Color333(0, 0, 7));
}

void drawBoundaries()
{
   matrix.drawLine(0, 0, 31, 0, matrix.Color333(7, 0, 0));
   matrix.drawLine(0, 15, 31, 15, matrix.Color333(7, 0, 0));
}

void setup() 
{
  matrix.begin();

  Serial.begin(9600);
  incomingByte = 0;
 
  USART_Index = 0;
  obstacleIndex = 0;
  
  player.xPosition = 30;
  player.yPosition = 7;

  for(unsigned int i = 0; i < 8; i++)
  {
    obstacles[i].xPosition = 0;
    obstacles[i].yPosition = 0;
  }
}

void loop() 
{
  matrix.fillScreen(0);
  recieveUSART();
  drawPlayer();
  //drawBoundaries();
  matrix.swapBuffers(false);
}
