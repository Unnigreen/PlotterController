/*
 * UserNotification.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */
#include "Arduino.h"
#include "common.hpp"
#include "Scheduler.hpp"
#include "UserNotification.hpp"

namespace UserNotificationLogic
{

TID UserNotification::taskId = TASK_ID_INVALID;
NotificationDeatils UserNotification::NotificationInfo;

//NotificationTableInfo NotificationTableEntry_Init

//NotificationTableInfo UserNotification::NotificationTable[NOTIFICATION_STATE_MAX] = {
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // init
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // ready
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // on job
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // job completed
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // init error
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // communication error
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // job error
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // over run error
//		{ true, LED_BUZZER_ON_DURATION_500MS, true, LED_BUZZER_ON_DURATION_500MS, }, // other error
//};

bool UserNotification::TaskInit()
{
	pinMode(STATUS_LED_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	return true;
}

void UserNotification::TaskRun()
{
	  digitalWrite(STATUS_LED_PIN, digitalRead(LED_BUILTIN) ^ 1);
	  LedOperation();
	  BuzzerOperation();
}

void UserNotification::SetTaskId(TID id)
{
	taskId = id;
}

TID UserNotification::GetTaskId()
{
	return taskId;
}

void UserNotification::LedOperation()
{

}

void UserNotification::BuzzerOperation()
{

}

void UserNotification::SendMessage(NotificationState state)
{
	NotificationInfo.nxtNotificationState = state;
	SchedulerNs::Scheduler::EnableTask(taskId);
}

}
