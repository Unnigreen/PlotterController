// Do not remove the include below

#include "PlotterController.h"
#include "Scheduler.hpp"
#include "UserNotification.hpp"

namespace PlotterControllerApp
{

bool PlotterController::TaskInit()
{
	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void PlotterController::TaskRun()
{
	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

}
