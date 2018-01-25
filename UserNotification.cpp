/*
 * UserNotification.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */
#include "Arduino.h"
#include "UserNotification.hpp"
#include "Scheduler.hpp"

namespace UserNotificationNs
{

UserNotification::UserNotification()
{
	pinMode(LED_BUILTIN, OUTPUT);
}

UserNotification::~UserNotification()
{

}
void test()
{

}
void UserNotification::TaskEntry()
{
	UserNotification notificationObj;
//	notificationObj.Run();
	SchedulerNs::Scheduler::CreateTask(1, 50, NULL, notificationObj.Run);
//	SchedulerNs::Scheduler::CreateTask(1, 50, NULL, test);
}

void UserNotification::Run()
{
	  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
