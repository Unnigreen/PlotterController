// Do not remove the include below

#include "Arduino.h"
#include "common.hpp"
#include "PlotterController.h"

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

void PlotterController::SetTaskId(TID task)
{
	taskId = task;
}

TID PlotterController::GetTaskId()
{
	return taskId;
}

}
