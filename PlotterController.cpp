/*
 * PlotterController.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "PlotterController.hpp"
#include "UserNotification.hpp"
#include "Scheduler.hpp"

namespace PlotterControllerApp
{

TID PlotterController::taskId = TASK_ID_INVALID;
bool PlotterController::isMsgReceived = false;
bool PlotterController::ForwardHomeState = false;
bool PlotterController::BackwardHomeState = false;

bool PlotterController::TaskInit()
{
//	pinMode(LED_BUILTIN, OUTPUT);
	return true;
}

void PlotterController::TaskRun()
{
	isMsgReceived = false;

	Serial.write(ForwardHomeState + 0x30);
	Serial.write(BackwardHomeState + 0x30);
	SchedulerNs::Scheduler::DisableTask(taskId);
}

void PlotterController::SetTaskId(TID id)
{
	taskId = id;
}

TID PlotterController::GetTaskId()
{
	return taskId;
}

void PlotterController::ForwardHomeCallBack(bool state)
{
	isMsgReceived = true;
	ForwardHomeState = state;
	SchedulerNs::Scheduler::EnableTask(taskId);
}

void PlotterController::BackwardHomeCallBack(bool state)
{
	isMsgReceived = true;
	BackwardHomeState = state;
	SchedulerNs::Scheduler::EnableTask(taskId);
}

}
