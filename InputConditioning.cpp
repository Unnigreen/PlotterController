/*
 * InputProcessing.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "InputConditioning.hpp"

namespace InputConditioningLogic
{

TID InputConditioning::taskId = TASK_ID_INVALID;

bool InputConditioning::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void InputConditioning::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

void InputConditioning::SetTaskId(TID id)
{
	taskId = id;
}

TID InputConditioning::GetTaskId()
{
	return taskId;
}

}
