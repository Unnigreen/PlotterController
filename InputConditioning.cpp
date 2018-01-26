/*
 * InputProcessing.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "InputConditioning.hpp"
#include "Arduino.h"

namespace InputConditioningLogic
{

bool InputConditioning::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void InputConditioning::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
