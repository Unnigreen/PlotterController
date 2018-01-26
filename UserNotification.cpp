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

//UserNotification::UserNotification()
//{
//	pinMode(LED_BUILTIN, OUTPUT);
//}
//
//UserNotification::~UserNotification()
//{
//
//}
void test()
{

}
bool UserNotification::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
//	UserNotification notificationObj;
//	notificationObj.Run();
//	SchedulerNs::Scheduler::CreateTask(1, 50, NULL, notificationObj.Run);

//	SchedulerNs::CreateTask1( NULL, notificationObj.Run);

//	SchedulerNs::Scheduler::CreateTask(1, 50, NULL, test);
	return true;
}

void UserNotification::Run()
{
	  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
