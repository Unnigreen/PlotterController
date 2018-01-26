/*
 * main.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: unni
 */

#include "PlotterController.h"
#include "Scheduler.hpp"
#include "UserNotification.hpp"

void setup()
{
	SchedulerNs::Scheduler::Init();
	SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_1SECOND, UserNotificationNs::UserNotification::TaskInit, UserNotificationNs::UserNotification::TaskRun);
}

void loop()
{
	if(SchedulerNs::Scheduler::schedulerTriggerCount != 0)
	{
		SchedulerNs::Scheduler::Run();
		SchedulerNs::Scheduler::DecrementSchedulerTriggerCount();
	}
}


