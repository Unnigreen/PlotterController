/*
 * UserNotification.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */
#include "Arduino.h"
#include "common.hpp"
#include "UserNotification.hpp"

namespace UserNotificationLogic
{

TID UserNotification::taskId = TASK_ID_INVALID;

bool UserNotification::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void UserNotification::TaskRun()
{
	  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

void UserNotification::SetTaskId(TID task)
{
	taskId = task;
}

TID UserNotification::GetTaskId()
{
	return taskId;
}

}
