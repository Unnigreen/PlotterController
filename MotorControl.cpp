/*
 * MotorControl.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "string.h"
#include "MotorControl.hpp"

namespace MotorControlLogic
{

TID MotorControl::taskId = TASK_ID_INVALID;
StepperMotor* MotorControl::BaseMotor = NULL;
StepperMotor* MotorControl::CrossMotor = NULL;
DcMotor* MotorControl::DrillMotor = NULL;

BaseMotor::BaseMotor()
{
	config.accStepSize = 0;
	config.stepSize = 0;
	config.homeToHomeSteps = 0;
	config.curStep = 0;
}

BaseMotor::~BaseMotor()
{

}

StepperMotor::StepperMotor(MotorType type)
{
	switch(type)
	{
	case STEPPER_BASE_MOTOR:
		config.accStepSize = 1;
		config.stepSize = 10;
		config.homeToHomeSteps = 0;
		config.curStep = 0;
		config.pwmPin = STEPPER_BASE_MOTOR_PIN;
		pinMode(config.pwmPin, OUTPUT);
		break;
	case STEPPER_CROSS_MOTOR:
		config.accStepSize = 1;
		config.stepSize = 10;
		config.homeToHomeSteps = 0;
		config.curStep = 0;
		config.pwmPin = STEPPER_CROSS_MOTOR_PIN;
		pinMode(config.pwmPin, OUTPUT);
		break;
	default:
		break;
	}
}

StepperMotor::~StepperMotor()
{

}

DcMotor::DcMotor(MotorType type)
{
	switch(type)
	{
	case DC_DRILL_MOTOR:
		config.accStepSize = 1;
		config.stepSize = 10;
		config.homeToHomeSteps = 0;
		config.curStep = 0;
		config.pwmPin = DC_DRILL_MOTOR_PIN;
		pinMode(config.pwmPin, OUTPUT);
		break;
	default:
		break;
	}
}

DcMotor::~DcMotor()
{

}

bool MotorControl::TaskInit()
{
//	pinMode(LED_BUILTIN, OUTPUT);

	BaseMotor = new StepperMotor(STEPPER_BASE_MOTOR);
	CrossMotor = new StepperMotor(STEPPER_CROSS_MOTOR);
	DrillMotor = new DcMotor(DC_DRILL_MOTOR);

	return true;
}

void MotorControl::TaskRun()
{
//	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);
}

void MotorControl::SetTaskId(TID id)
{
	taskId = id;
}

TID MotorControl::GetTaskId()
{
	return taskId;
}

bool StepperMotor::SetMotorConfig(MotorConfig* setting)
{
	memcpy((void*)&config, (void*)setting, sizeof(MotorConfig));
	return true;
}

bool StepperMotor::GetMotorConfig(MotorConfig* setting)
{
	memcpy((void*)setting, (void*)&config, sizeof(MotorConfig));
	return true;
}

void StepperMotor::MoveMotorBySteps(ULONG step)
{

}

void StepperMotor::MoveMotortoStep(ULONG step)
{

}

void StepperMotor::MoveMotorByDistance(ULONG dist)
{

}

void StepperMotor::MoveMotorContinuously()
{

}

void StepperMotor::StopMotor()
{

}

bool DcMotor::SetMotorConfig(MotorConfig* setting)
{
	memcpy((void*)&config, (void*)setting, sizeof(MotorConfig));
	return true;
}

bool DcMotor::GetMotorConfig(MotorConfig* setting)
{
	memcpy((void*)setting, (void*)&config, sizeof(MotorConfig));
	return true;
}

void DcMotor::MoveMotorContinuously()
{

}

void DcMotor::StopMotor()
{

}

}
