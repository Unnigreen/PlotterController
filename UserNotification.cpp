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

bool UserNotification::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void UserNotification::TaskRun()
{
	  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
