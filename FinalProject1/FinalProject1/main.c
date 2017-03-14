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
#include "usart_ATmega1284.h"
#include "structs.h"
#include "J_Task.h"
#include "U_Task.h"
#include "M_Task.h"
#include "B_Task.h"

//Task Scheduler Variables
unsigned long numTasks = 4;

int main(void)
{
	DDRA = 0x00; PORTC = 0xFF;	//Setup Port A for Joystick input
	DDRD = 0x02; PORTD = 0x01;	//Setup Port D for USART
	
	//Initialize joystick reading
	InitADC();
	
	//Initialize UART
	initUSART(0);
	
	//Initialize timer
	TimerSet(1);
	TimerOn();
	
	//Initialize task scheduler
	task tasks[numTasks];
	
	//Initialize all tasks for scheduler
	unsigned long taskIndex = 0;
	//Initialize joystick task
	tasks[taskIndex].state = J_Base;
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
		while (!TimerFlag);
		TimerFlag = 0;
    }
}

