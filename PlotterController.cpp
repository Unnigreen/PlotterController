/*
 * PlotterController.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "PlotterController.hpp"

namespace PlotterControllerApp
{

TID PlotterController::taskId = TASK_ID_INVALID;

bool PlotterController::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void PlotterController::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
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
