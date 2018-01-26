/*
 * InputProcessing.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "InputProcessing.hpp"
#include "Arduino.h"

namespace InputProcessingLogic
{

bool InputProcessing::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void InputProcessing::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
