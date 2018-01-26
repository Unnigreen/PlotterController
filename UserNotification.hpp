/*
 * UserNotification.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef USERNOTIFICATION_HPP_
#define USERNOTIFICATION_HPP_

#include "typedef.hpp"

namespace UserNotificationLogic
{

#define LED_BUZZER_DURATION_INVALID	(0)
#define LED_BUZZER_DURATION_50MS	(1)
#define LED_BUZZER_DURATION_100MS	(LED_BUZZER_DURATION_50MS * 2)
#define LED_BUZZER_DURATION_250MS	(LED_BUZZER_DURATION_50MS * 5)
#define LED_BUZZER_DURATION_500MS	(LED_BUZZER_DURATION_50MS * 10)
#define LED_BUZZER_DURATION_750MS	(LED_BUZZER_DURATION_50MS * 15)
#define LED_BUZZER_DURATION_1000MS	(LED_BUZZER_DURATION_50MS * 20)

#define STATUS_LED_PIN 			LED_BUILTIN
#define BUZZER_PIN 				PIN_A0
#define MAX_LED_BUZZER_ON_OFF	6
#define LED_REPEAT_ON			true
#define LED_REPEAT_OFF			false
#define BUZZER_REPEAT_ON		true
#define BUZZER_REPEAT_OFF		false

typedef enum
{
	NOTIFICATION_STATE_INVALID = -1,
	NOTIFICATION_STATE_INITIALIZING,
	NOTIFICATION_STATE_READY,
	NOTIFICATION_STATE_ON_JOB,
	NOTIFICATION_STATE_JOB_COMPLETED,
	NOTIFICATION_STATE_INITIALIZATION_ERROR,
	NOTIFICATION_STATE_COMMUNICATION_ERROR,
	NOTIFICATION_STATE_JOB_ERROR,
	NOTIFICATION_STATE_OVER_RUN_ERROR,
	NOTIFICATION_STATE_OTHER_ERROR,
	NOTIFICATION_STATE_MAX
}NotificationState;

typedef struct
{
	bool IsOn;
	USHORT Duration;
}LedBuzzerStateInfo;

typedef struct
{
	bool isStatusLedRepeatOn;
	bool isBuzzerRepeatOn;
	LedBuzzerStateInfo StatusLedOnOffTable[MAX_LED_BUZZER_ON_OFF];
	LedBuzzerStateInfo BuzzerOnOffTable[MAX_LED_BUZZER_ON_OFF];
}NotificationTableInfo;

typedef struct
{
	NotificationState curNotificationState;
	NotificationState prvNotificationState;
	NotificationState nxtNotificationState;
	bool isStatusLedOn;
	bool isStatusLedTaskRunning;
	bool isBuzzerOn;
	bool isBuzzerTaskRunning;
	USHORT StatusLedDurationRequired;
	USHORT StatusLedDurationCounter;
	USHORT StatusLedOnOffTableIndex;
	USHORT BuzzerDurationRequired;
	USHORT BuzzerDurationCounter;
	USHORT BuzzerOnOffTableIndex;
}RunningNotificationInfo;

class UserNotification
{
private:
	static TID taskId;
	static bool isMsgReceived;
	static RunningNotificationInfo NotificationStateInfo;
	static NotificationTableInfo * NotificationTable[NOTIFICATION_STATE_MAX];
public:
	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
	static void StartStatusLedOperation();
	static void StartBuzzerOperation();
	static void StatusLedOperation();
	static void BuzzerOperation();
	static void SendMessage(NotificationState);
};

}

#endif /* USERNOTIFICATION_HPP_ */
