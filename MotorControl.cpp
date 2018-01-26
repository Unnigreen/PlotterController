/*
 * MotorControl.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "MotorControl.hpp"

namespace MotorControlLogic
{

TID MotorControl::taskId = TASK_ID_INVALID;

bool MotorControl::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void MotorControl::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

void MotorControl::SetTaskId(TID id)
{
	taskId = id;
}

TID MotorControl::GetTaskId()
{
	return taskId;
}

}
