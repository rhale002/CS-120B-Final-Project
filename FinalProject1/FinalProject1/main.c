/*
 * FinalProject1.c
 *
 * Created: 2/28/2017 12:45:49 PM
 * Author : robyn
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "io.h"
#include "joystick.h"
#include "scheduler.h"
#include "timer.h"
#include "usart_ATmega1284.h"
#include "structs.h"
#include "J_Task.h"
#include "U_Task.h"
#include "M_Task.h"
#include "B_Task.h"
#include "R_Task.h"
#include "S_Task.h"

//Task Scheduler Variables
unsigned long numTasks = 6;

extern unsigned char resetGame;

void resetTasks(task *tasks)
{
	//Initialize all tasks for scheduler
	unsigned long taskIndex = 0;
	//Initialize joystick task
	tasks[taskIndex].state = J_Start;
	tasks[taskIndex].period = J_Period;
	tasks[taskIndex].elapsedTime = J_Period;
	tasks[taskIndex].TickFct = &J_Tick;
	++taskIndex;
	//Initialize USART task
	tasks[taskIndex].state = U_Start;
	tasks[taskIndex].period = U_Period;
	tasks[taskIndex].elapsedTime = U_Period;
	tasks[taskIndex].TickFct = &U_Tick;
	++taskIndex;
	//Initialize Movement task
	tasks[taskIndex].state = M_Start;
	tasks[taskIndex].period = M_Period;
	tasks[taskIndex].elapsedTime = M_Period;
	tasks[taskIndex].TickFct = &M_Tick;
	++taskIndex;
	//Initialize Board task
	tasks[taskIndex].state = B_Start;
	tasks[taskIndex].period = B_Period;
	tasks[taskIndex].elapsedTime = B_Period;
	tasks[taskIndex].TickFct = &B_Tick;
	++taskIndex;
	//Initialize Reset task
	tasks[taskIndex].state = R_Start;
	tasks[taskIndex].period = R_Period;
	tasks[taskIndex].elapsedTime = R_Period;
	tasks[taskIndex].TickFct = &R_Tick;
	++taskIndex;
	//Initialize Reset task
	tasks[taskIndex].state = S_Start;
	tasks[taskIndex].period = S_Period;
	tasks[taskIndex].elapsedTime = S_Period;
	tasks[taskIndex].TickFct = &S_Tick;
	++taskIndex;
}

int main(void)
{
	DDRA = 0x00; PORTC = 0xFF;	//Setup Port A for Joystick input
	DDRD = 0x02; PORTD = 0x41;	//Setup Port D for USART
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRB = 0xFF; PORTB = 0x00; // LCD control lines
	
	//Initialize lcd screen
	LCD_init();
	
	//Initialize joystick reading
	InitADC();
	
	//Initialize UART
	initUSART(0);
	
	//Initialize timer
	TimerSet(1);
	TimerOn();
	
	//Initialize task scheduler
	task tasks[numTasks];

	resetTasks(tasks);
	
    while (1) 
    {
		if(resetGame == 0x01)
			resetTasks(tasks);
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
		while (!TimerFlag);
		TimerFlag = 0;
    }
}

