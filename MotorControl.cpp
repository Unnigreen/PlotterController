/*
 * MotorControl.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "MotorControl.hpp"

#include "Arduino.h"

namespace MotorControlLogic
{

bool MotorControl::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void MotorControl::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
