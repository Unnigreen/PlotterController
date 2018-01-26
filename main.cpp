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
#include "PlotterController.hpp"

void setup()
{
	TID taskId;

	SchedulerNs::Scheduler::Init();

	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_200MS, UserNotificationLogic::UserNotification::TaskInit, UserNotificationLogic::UserNotification::TaskRun);
	UserNotificationLogic::UserNotification::SetTaskId(taskId);
	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_500MS, MotorControlLogic::MotorControl::TaskInit, MotorControlLogic::MotorControl::TaskRun);
	MotorControlLogic::MotorControl::SetTaskId(taskId);
	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_500MS, InputConditioningLogic::InputConditioning::TaskInit, InputConditioningLogic::InputConditioning::TaskRun);
	InputConditioningLogic::InputConditioning::SetTaskId(taskId);
	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_TICK_500MS, PlotterControllerApp::PlotterController::TaskInit, PlotterControllerApp::PlotterController::TaskRun);
	PlotterControllerApp::PlotterController::SetTaskId(taskId);

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
