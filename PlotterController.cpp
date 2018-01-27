/*
 * PlotterController.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "PlotterController.hpp"
#include "UserNotification.hpp"

namespace PlotterControllerApp
{

TID PlotterController::taskId = TASK_ID_INVALID;

bool PlotterController::TaskInit()
{
//	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void PlotterController::TaskRun()
{
	static UserNotificationLogic::NotificationState nState = UserNotificationLogic::NOTIFICATION_STATE_INITIALIZING;
//	static UserNotificationLogic::NotificationState nState = UserNotificationLogic::NOTIFICATION_STATE_COMMUNICATION_ERROR;
	UserNotificationLogic::UserNotification::SendMessage(nState);
	switch(nState)
	{
	case UserNotificationLogic::NOTIFICATION_STATE_INITIALIZING:
		nState = UserNotificationLogic::NOTIFICATION_STATE_READY;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_READY:
		nState = UserNotificationLogic::NOTIFICATION_STATE_ON_JOB;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_ON_JOB:
		nState = UserNotificationLogic::NOTIFICATION_STATE_JOB_COMPLETED;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_JOB_COMPLETED:
		nState = UserNotificationLogic::NOTIFICATION_STATE_INITIALIZATION_ERROR;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_INITIALIZATION_ERROR:
		nState = UserNotificationLogic::NOTIFICATION_STATE_COMMUNICATION_ERROR;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_COMMUNICATION_ERROR:
		nState = UserNotificationLogic::NOTIFICATION_STATE_JOB_ERROR;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_JOB_ERROR:
		nState = UserNotificationLogic::NOTIFICATION_STATE_OVER_RUN_ERROR;
		break;
	case UserNotificationLogic::NOTIFICATION_STATE_OVER_RUN_ERROR:
		nState = UserNotificationLogic::NOTIFICATION_STATE_OTHER_ERROR;
		break;
	default:
		nState = UserNotificationLogic::NOTIFICATION_STATE_INITIALIZING;
		break;
	}
//	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
//		Serial.write("Hello");
}

void PlotterController::SetTaskId(TID id)
{
	taskId = id;
}

TID PlotterController::GetTaskId()
{
	return taskId;
}

}
