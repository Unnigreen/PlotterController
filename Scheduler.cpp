/*
 * Scheduler.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */
#include "Arduino.h"
#include "Scheduler.hpp"

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	SchedulerNs::Scheduler::schedulerTriggerCount++;
//	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

namespace SchedulerNs
{

taskControlBlock Scheduler::taskInfo[MAX_TASKS];
bool Scheduler::isSchdulerUp = false;
ULONG Scheduler::schedulerTriggerCount = 0;

void Scheduler::Init()
{
	// initialize timer1
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;

//	OCR1A = 31250;            // compare match register 16MHz/256/2Hz
	OCR1A = 312;
	TCCR1B |= (1 << WGM12);   // CTC mode
	TCCR1B |= (1 << CS12);    // 256 prescaler
	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

	for(int i = 0; i < MAX_TASKS; i++)
	{
		taskInfo[i].taskId = TASK_ID_INVALID;
	}
	schedulerTriggerCount = 0;
	interrupts();
}

Scheduler::Scheduler()
{
	if(isSchdulerUp == false)
	{
		isSchdulerUp = true;
		// initialize timer1
		noInterrupts();           // disable all interrupts
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;

		//	OCR1A = 31250;            // compare match register 16MHz/256/2Hz
		OCR1A = 312;
		TCCR1B |= (1 << WGM12);   // CTC mode
		TCCR1B |= (1 << CS12);    // 256 prescaler
		TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

		for(int i = 0; i < MAX_TASKS; i++)
		{
			taskInfo[i].taskId = TASK_ID_INVALID;
		}
		schedulerTriggerCount = 0;
		interrupts();
	}
}

Scheduler::~Scheduler()
{

}

TID Scheduler::CreateTask(USHORT taskPrio, ULONG ticksToRun, taskInitFn_ptr taskInitFn, taskRunFn_ptr taskRunFn)
{
	TID id = TASK_ID_INVALID;

	noInterrupts();           // disable all interrupts
	for(int i = 0; i < MAX_TASKS; i++)
	{
		if(taskInfo[i].taskId == TASK_ID_INVALID)
		{
			taskInfo[i].taskId = (i+1);
			taskInfo[i].taskPrio = taskPrio;
			taskInfo[i].taskTicksToRun = ticksToRun;
			taskInfo[i].taskTickCount = 0;
			taskInfo[i].taskInitFn = taskInitFn;
			taskInfo[i].taskRunFn = taskRunFn;
			if(taskInfo[i].taskInitFn != NULL)
			{
				taskInfo[i].taskInitFn() == true ? (id = i) : (id = TASK_INIT_FAILED);
			}
			break;
		}
	}
	interrupts();

	return id;
}

void Scheduler::DecrementSchedulerTriggerCount()
{
	noInterrupts();
	schedulerTriggerCount > 0 ? (schedulerTriggerCount--) : (schedulerTriggerCount = 0);
	interrupts();
}

void Scheduler::Run()
{
	for(int i = 0; i < MAX_TASKS; i++)
	{
		if(taskInfo[i].taskId != TASK_ID_INVALID)
		{
			taskInfo[i].taskTickCount++;
			if(taskInfo[i].taskTickCount >= taskInfo[i].taskTicksToRun)
			{
				taskInfo[i].taskRunFn();
				taskInfo[i].taskTickCount = 0;
			}
		}
	}
}

TID CreateTask1(taskInitFn_ptr taskInitFn, taskRunFn_ptr taskRunFn)
{
}

}
