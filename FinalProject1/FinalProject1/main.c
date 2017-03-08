/*
 * FinalProject1.c
 *
 * Created: 2/28/2017 12:45:49 PM
 * Author : robyn
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "joystick.h"
#include "scheduler.h"
#include "timer.h"

//Task Scheduler Variables
unsigned long numTasks = 1;
unsigned long taskIndex = 0;

//Initialize J_Task states and period
enum J_States {J_Base} J_State;
unsigned long J_Period = 1;
int xJoy;
int yJoy;

	
//Initialize J_Task Tick Function
int J_Tick(int currentState)
{

	switch(currentState)
	{
		case J_Base:
		{
			currentState = J_Base;
		}
		break;
			
		default:
		break;
	}//transitions

	switch(currentState)
	{
		case J_Base:
		{
			xJoy = readadc(0);      //Read ADC value from A0 (Joystick x axis)
			yJoy = readadc(1);      //Read ADC value from A1 (Joystick y axis)
			xJoy = xJoy - 512;		//Move values for easier checking
			yJoy = yJoy - 512;		//Move values for easier checking
			
			//Temporary joystick testing
			if(abs(yJoy) >= abs(xJoy) && yJoy > 75)			//If up
				PORTC = 0x01;
			else if(abs(xJoy) > abs(yJoy) && xJoy > 75)		//If right
				PORTC = 0x02;
			else if(abs(yJoy) >= abs(xJoy) && yJoy < -75)	// If down
				PORTC = 0x04;
			else if(abs(xJoy) > abs(yJoy) && xJoy < -75)	//If left
				PORTC = 0x08;
			else 											//If no direction
				PORTC = 0x00;
		}
		break;
		
		default:
		break;
	}//actions
		
	return currentState;
}

int main(void)
{
	DDRA = 0x00; PORTC = 0xFF;	//Joystick input
	DDRC = 0xFF; PORTC = 0x00;	//LED Testing Output
	
	//Initialize joystick reading
	InitADC();
	
	//Initialize timer
	TimerSet(1);
	TimerOn();
	
	//Initialize task scheduler
	task tasks[numTasks];
	
	//Initialize joystick task
	tasks[taskIndex].state = J_Base;
	tasks[taskIndex].period = J_Period;
	tasks[taskIndex].elapsedTime = J_Period;
	tasks[taskIndex].TickFct = &J_Tick;
	++taskIndex;
	
    while (1) 
    {
		//Handle tasks
		for(unsigned long i = 0; i < numTasks; i++)
		{
			tasks[i].elapsedTime += _avr_timer_cntcurr;
			
			if(tasks[i].elapsedTime >= tasks[i].period)
			{
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
		}
		//Wait for timerFlag to go high again then reset timerFlag
		while (!TimerFlag);
		TimerFlag = 0;
    }
}

