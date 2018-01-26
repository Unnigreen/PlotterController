// Do not remove the include below

#include "PlotterController.h"
#include "Scheduler.hpp"
#include "UserNotification.hpp"

void taskFn()
{
//	  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

//UserNotificationNs::UserNotification notificationObj;
void setup()
{
//	pinMode(LED_BUILTIN, OUTPUT);
	SchedulerNs::Scheduler::Init();
//	SchedulerNs::Scheduler::CreateTask(1, 50, NULL, taskFn);
//	UserNotificationNs::UserNotification::TaskEntry();
	SchedulerNs::Scheduler::CreateTask(1, 50, UserNotificationNs::UserNotification::TaskInit, UserNotificationNs::UserNotification::Run);
}

void loop()
{
	if(SchedulerNs::Scheduler::schedulerTriggerCount != 0)
	{
		SchedulerNs::Scheduler::Run();
		SchedulerNs::Scheduler::DecrementSchedulerTriggerCount();
	}
}
