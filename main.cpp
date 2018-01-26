/*
 * main.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: unni
 */

#include "Scheduler.hpp"
#include "MotorControl.hpp"
#include "UserNotification.hpp"
#include "InputConditioning.hpp"
#include "PlotterController.h"

void setup()
{
	SchedulerNs::Scheduler::Init();
	SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_200MS, UserNotificationNs::UserNotification::TaskInit, UserNotificationNs::UserNotification::TaskRun);
	SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_500MS, MotorControlLogic::MotorControl::TaskInit, MotorControlLogic::MotorControl::TaskRun);
	SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_500MS, InputConditioningLogic::InputConditioning::TaskInit, InputConditioningLogic::InputConditioning::TaskRun);
	SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_500MS, PlotterControllerApp::PlotterController::TaskInit, PlotterControllerApp::PlotterController::TaskRun);
	SchedulerNs::Scheduler::Start();
}

void loop()
{
	if(SchedulerNs::Scheduler::schedulerTriggerCount != 0)
	{
		SchedulerNs::Scheduler::Run();
		SchedulerNs::Scheduler::DecrementSchedulerTriggerCount();
	}
}


