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
	case MOTOR_TYPE_STEPPER_BASE:
		config.accStepSize = 1;
		config.stepSize = 200;
		config.homeToHomeSteps = 0;
		config.curStep = 0;
		config.pwmPin = STEPPER_BASE_MOTOR_PIN;
		break;
	case MOTOR_TYPE_STEPPER_CROSS:
		config.accStepSize = 1;
		config.stepSize = 200;
		config.homeToHomeSteps = 0;
		config.curStep = 0;
		config.pwmPin = STEPPER_CROSS_MOTOR_PIN;
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
	case MOTOR_TYPE_DC_DRILL:
		config.accStepSize = 0;
		config.stepSize = 200;
		config.homeToHomeSteps = 0;
		config.curStep = 0;
		config.pwmPin = DC_DRILL_MOTOR_PIN;
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
	BaseMotor = new StepperMotor(MOTOR_TYPE_STEPPER_BASE);
	CrossMotor = new StepperMotor(MOTOR_TYPE_STEPPER_CROSS);
	DrillMotor = new DcMotor(MOTOR_TYPE_DC_DRILL);

	return true;
}

void MotorControl::TaskRun()
{
//	digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1);

//	static ULONG step = 0;
	BaseMotor->MoveMotorContinuously(MOTOR_MOVE_TYPE_INVALID);
	CrossMotor->MoveMotorContinuously(MOTOR_MOVE_TYPE_INVALID);
	DrillMotor->MoveMotorContinuously(MOTOR_MOVE_TYPE_INVALID);

//	analogWrite(5, step);
//	step += 20;
}

void MotorControl::SetTaskId(TID id)
{
	taskId = id;
}

TID MotorControl::GetTaskId()
{
	return taskId;
}

void StepperMotor::MoveMotorBySteps(SLONG steps)
{
	MotorMoveType type;

	steps >= 0 ? (type = MOTOR_MOVE_TYPE_TO_FORWARDHOME) : (type = MOTOR_MOVE_TYPE_TO_BACKWARDHOME);
	switch(type)
	{
	case MOTOR_MOVE_TYPE_TO_FORWARDHOME:
		config.dirToMove = MOTOR_MOVE_TYPE_TO_FORWARDHOME;
		config.stepsToMove = steps;
		break;
	case MOTOR_MOVE_TYPE_TO_BACKWARDHOME:
		config.dirToMove = MOTOR_MOVE_TYPE_TO_BACKWARDHOME;
		config.stepsToMove = steps * -1;
		break;
	default:
		break;
	}
}

void StepperMotor::MoveMotortoStep(ULONG step)
{
	MotorMoveType type;

	config.curStep <= step ? (type = MOTOR_MOVE_TYPE_TO_FORWARDHOME) : (type = MOTOR_MOVE_TYPE_TO_BACKWARDHOME);
	switch(type)
	{
	case MOTOR_MOVE_TYPE_TO_FORWARDHOME:
		config.stepsToMove = step - config.curStep;
		config.dirToMove = MOTOR_MOVE_TYPE_TO_FORWARDHOME;
		break;
	case MOTOR_MOVE_TYPE_TO_BACKWARDHOME:
		config.stepsToMove = config.curStep - step;
		config.dirToMove = MOTOR_MOVE_TYPE_TO_BACKWARDHOME;
		break;
	default:
		break;
	}
}

void StepperMotor::MoveMotorByDistance(SLONG dist)
{
	MotorMoveType type;

	dist >= 0 ? (type = MOTOR_MOVE_TYPE_TO_FORWARDHOME) : (type = MOTOR_MOVE_TYPE_TO_BACKWARDHOME);
	switch(type)
	{
	case MOTOR_MOVE_TYPE_TO_FORWARDHOME:
		config.dirToMove = MOTOR_MOVE_TYPE_TO_FORWARDHOME;
		config.stepsToMove = dist * config.stepsPerMm;
		break;
	case MOTOR_MOVE_TYPE_TO_BACKWARDHOME:
		config.dirToMove = MOTOR_MOVE_TYPE_TO_BACKWARDHOME;
		config.stepsToMove = dist * config.stepsPerMm * -1;
		break;
	default:
		break;
	}
}

void StepperMotor::MoveMotorContinuously(MotorMoveType type)
{
	switch(type)
	{
	case MOTOR_MOVE_TYPE_TO_FORWARDHOME:
		config.dirToMove = MOTOR_MOVE_TYPE_TO_FORWARDHOME;
		break;
	case MOTOR_MOVE_TYPE_TO_BACKWARDHOME:
		config.dirToMove = MOTOR_MOVE_TYPE_TO_BACKWARDHOME;
		break;
	default:
		break;
	}
	config.stepsToMove = ~0;
//	analogWrite(config.pwmPin, config.stepSize);
}

void StepperMotor::StopMotor()
{

}

bool BaseMotor::SetMotorConfig(MotorConfig* setting)
{
	memcpy((void*)&config, (void*)setting, sizeof(MotorConfig));
	return true;
}

bool BaseMotor::GetMotorConfig(MotorConfig* setting)
{
	memcpy((void*)setting, (void*)&config, sizeof(MotorConfig));
	return true;
}

void DcMotor::MoveMotorContinuously(MotorMoveType type)
{
	switch(type)
	{
	case MOTOR_MOVE_TYPE_CLOCKWISE:
		break;
	case MOTOR_MOVE_TYPE_ANTICLOCKWISE:
		break;
	default:
		break;
	}
	analogWrite(config.pwmPin, (config.stepSize % 255));
}

void DcMotor::StopMotor()
{
	analogWrite(config.pwmPin, 0);
}

}
