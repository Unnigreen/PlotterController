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
RunningNotificationInfo UserNotification::NotificationStateInfo;
bool UserNotification::isMsgReceived;

NotificationTableInfo NotificationTableEntry_Init = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_50MS, },
				{ true, LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_1000MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_Ready = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_3000MS, },
				{ false, LED_BUZZER_DURATION_3000MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_OnJob = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_JobCompleted = {
		LED_REPEAT_OFF, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_50MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_InitError = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_50MS, },
				{ true, LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ true, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_2000MS, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_ComError = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_1000MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_JobError = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ true, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ true, LED_BUZZER_DURATION_1500MS, },
				{ false, LED_BUZZER_DURATION_2000MS, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_OverRunError = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo NotificationTableEntry_OtherError = {
		LED_REPEAT_ON, BUZZER_REPEAT_OFF,
		{
				{ true,  LED_BUZZER_DURATION_100MS, },
				{ false, LED_BUZZER_DURATION_3000MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
		{
				{ true,  LED_BUZZER_DURATION_750MS, },
				{ false, LED_BUZZER_DURATION_500MS, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
				{ false, LED_BUZZER_DURATION_INVALID, },
		},
};

NotificationTableInfo * UserNotification::NotificationTable[NOTIFICATION_STATE_MAX] = {
		 &NotificationTableEntry_Init,
		 &NotificationTableEntry_Ready,
		 &NotificationTableEntry_OnJob,
		 &NotificationTableEntry_JobCompleted,
		 &NotificationTableEntry_InitError,
		 &NotificationTableEntry_ComError,
		 &NotificationTableEntry_JobError,
		 &NotificationTableEntry_OverRunError,
		 &NotificationTableEntry_OtherError,
};

bool UserNotification::TaskInit()
{
	pinMode(STATUS_LED_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	return true;
}

void UserNotification::TaskRun()
{
//	  digitalWrite(STATUS_LED_PIN, digitalRead(LED_BUILTIN) ^ 1);

	  if(isMsgReceived == true)
	  {
		  NotificationStateInfo.prvNotificationState = NotificationStateInfo.curNotificationState;
		  NotificationStateInfo.curNotificationState = NotificationStateInfo.nxtNotificationState;
		  NotificationStateInfo.nxtNotificationState = NOTIFICATION_STATE_INVALID;
		  StartStatusLedOperation();
		  StartBuzzerOperation();
		  isMsgReceived = false;
		  Serial.write(NotificationStateInfo.curNotificationState + 0x30);
	  }

	  StatusLedOperation();
	  BuzzerOperation();
	  if( (NotificationStateInfo.isStatusLedTaskRunning == false) && (NotificationStateInfo.isBuzzerTaskRunning == false) )
	  {
		  SchedulerNs::Scheduler::DisableTask(taskId);
	  }
}

void UserNotification::SetTaskId(TID id)
{
	taskId = id;
}

TID UserNotification::GetTaskId()
{
	return taskId;
}

void UserNotification::StartStatusLedOperation()
{
	NotificationStateInfo.StatusLedOnOffTableIndex = 0;
	NotificationStateInfo.isStatusLedOn = NotificationTable[NotificationStateInfo.curNotificationState]->StatusLedOnOffTable[NotificationStateInfo.StatusLedOnOffTableIndex].IsOn;
	NotificationStateInfo.StatusLedDurationRequired = NotificationTable[NotificationStateInfo.curNotificationState]->StatusLedOnOffTable[NotificationStateInfo.StatusLedOnOffTableIndex].Duration;
	NotificationStateInfo.StatusLedDurationCounter = 0;
	if(NotificationStateInfo.StatusLedDurationRequired != LED_BUZZER_DURATION_INVALID){
		digitalWrite(STATUS_LED_PIN, NotificationStateInfo.isStatusLedOn);
		NotificationStateInfo.isStatusLedTaskRunning = true;
	}
	else{
		NotificationStateInfo.isStatusLedTaskRunning = false;
	}
}

void UserNotification::StartBuzzerOperation()
{
	NotificationStateInfo.BuzzerOnOffTableIndex = 0;
	NotificationStateInfo.isBuzzerOn = NotificationTable[NotificationStateInfo.curNotificationState]->BuzzerOnOffTable[NotificationStateInfo.BuzzerOnOffTableIndex].IsOn;
	NotificationStateInfo.BuzzerDurationRequired = NotificationTable[NotificationStateInfo.curNotificationState]->BuzzerOnOffTable[NotificationStateInfo.BuzzerOnOffTableIndex].Duration;
	NotificationStateInfo.BuzzerDurationCounter = 0;
	if(NotificationStateInfo.BuzzerDurationRequired != LED_BUZZER_DURATION_INVALID){
		digitalWrite(BUZZER_PIN, NotificationStateInfo.isBuzzerOn);
		NotificationStateInfo.isBuzzerTaskRunning = true;
	}
	else{
		NotificationStateInfo.isBuzzerTaskRunning = false;
	}
}

void UserNotification::StatusLedOperation()
{
	if(NotificationStateInfo.isStatusLedTaskRunning == true)
	{
		NotificationStateInfo.StatusLedDurationCounter++;
		if(NotificationStateInfo.StatusLedDurationCounter > NotificationStateInfo.StatusLedDurationRequired)
		{
			NotificationStateInfo.StatusLedOnOffTableIndex++;
			if( (NotificationTable[NotificationStateInfo.curNotificationState]->StatusLedOnOffTable[NotificationStateInfo.StatusLedOnOffTableIndex].Duration == LED_BUZZER_DURATION_INVALID)
				|| (NotificationStateInfo.StatusLedOnOffTableIndex >= MAX_LED_BUZZER_ON_OFF))
			{
				NotificationStateInfo.StatusLedOnOffTableIndex = 0;
				if(NotificationTable[NotificationStateInfo.curNotificationState]->isStatusLedRepeatOn == false)
				{
					NotificationStateInfo.isStatusLedTaskRunning = false;
					return;
				}
			}
			NotificationStateInfo.isStatusLedOn = NotificationTable[NotificationStateInfo.curNotificationState]->StatusLedOnOffTable[NotificationStateInfo.StatusLedOnOffTableIndex].IsOn;
			NotificationStateInfo.StatusLedDurationRequired = NotificationTable[NotificationStateInfo.curNotificationState]->StatusLedOnOffTable[NotificationStateInfo.StatusLedOnOffTableIndex].Duration;
			NotificationStateInfo.StatusLedDurationCounter = 0;
			digitalWrite(STATUS_LED_PIN, NotificationStateInfo.isStatusLedOn);
		}
	}
}

void UserNotification::BuzzerOperation()
{
	if(NotificationStateInfo.isBuzzerTaskRunning == true)
	{
		NotificationStateInfo.BuzzerDurationCounter++;
		if(NotificationStateInfo.BuzzerDurationCounter > NotificationStateInfo.BuzzerDurationRequired)
		{
			NotificationStateInfo.BuzzerOnOffTableIndex++;
			if( (NotificationTable[NotificationStateInfo.curNotificationState]->BuzzerOnOffTable[NotificationStateInfo.BuzzerOnOffTableIndex].Duration == LED_BUZZER_DURATION_INVALID)
					|| (NotificationStateInfo.BuzzerOnOffTableIndex >= MAX_LED_BUZZER_ON_OFF))
			{
				NotificationStateInfo.BuzzerOnOffTableIndex = 0;
				if(NotificationTable[NotificationStateInfo.curNotificationState]->isBuzzerRepeatOn == false)
				{
					NotificationStateInfo.isBuzzerTaskRunning = false;
					return;
				}
			}
			NotificationStateInfo.isBuzzerOn = NotificationTable[NotificationStateInfo.curNotificationState]->BuzzerOnOffTable[NotificationStateInfo.BuzzerOnOffTableIndex].IsOn;
			NotificationStateInfo.BuzzerDurationRequired = NotificationTable[NotificationStateInfo.curNotificationState]->BuzzerOnOffTable[NotificationStateInfo.BuzzerOnOffTableIndex].Duration;
			NotificationStateInfo.BuzzerDurationCounter = 0;
			digitalWrite(BUZZER_PIN, NotificationStateInfo.isBuzzerOn);
		}
	}
}

void UserNotification::SendMessage(NotificationState state)
{
	NotificationStateInfo.nxtNotificationState = state;
	isMsgReceived = true;
	SchedulerNs::Scheduler::EnableTask(taskId);
}

}
