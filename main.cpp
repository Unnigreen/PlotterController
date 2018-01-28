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

	Serial.begin(115200);
	SchedulerNs::Scheduler::Init();

	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_INPUT_CONDITIONING_TICK,InputConditioningLogic::InputConditioning::TaskInit,InputConditioningLogic::InputConditioning::TaskRun);
	InputConditioningLogic::InputConditioning::SetTaskId(taskId);
	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_MOTOR_CONTROL_TICK * 100, 	MotorControlLogic::MotorControl::TaskInit, 			MotorControlLogic::MotorControl::TaskRun);
	MotorControlLogic::MotorControl::SetTaskId(taskId);
	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_USER_NOTIFICATION_TICK, UserNotificationLogic::UserNotification::TaskInit, 	UserNotificationLogic::UserNotification::TaskRun);
	UserNotificationLogic::UserNotification::SetTaskId(taskId);
	taskId = SchedulerNs::Scheduler::CreateTask(1, TASK_PLOTTER_CONTROLLER_TICK * 200,PlotterControllerApp::PlotterController::TaskInit, 	PlotterControllerApp::PlotterController::TaskRun);
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
