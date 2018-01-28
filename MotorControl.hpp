/*
 * MotorControl.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef MOTORCONTROL_HPP_
#define MOTORCONTROL_HPP_

#include "typedef.hpp"

namespace MotorControlLogic
{

#define STEPPER_BASE_MOTOR_PIN		(9)
#define STEPPER_CROSS_MOTOR_PIN		(10)
#define DC_DRILL_MOTOR_PIN			(11)

typedef enum
{
	MOTOR_TYPE_INVALID = -1,
	STEPPER_BASE_MOTOR,
	STEPPER_CROSS_MOTOR,
	DC_DRILL_MOTOR,
	MOTOR_TYPE_MAX
}MotorType;

typedef struct
{
	USHORT pwmPin;
	USHORT accStepSize;
	USHORT stepSize;
	ULONG homeToHomeSteps;
	ULONG curStep;

}MotorConfig;

class BaseMotor
{
private:

protected:
	MotorConfig config;

public:
	BaseMotor();
	virtual ~BaseMotor();
	virtual bool SetMotorConfig(MotorConfig*) = 0;
	virtual bool GetMotorConfig(MotorConfig*) = 0;
	virtual void StopMotor() = 0;
	virtual void MoveMotorContinuously() = 0;
};

class StepperMotor : public BaseMotor
{
private:
	StepperMotor();

public:
	StepperMotor(MotorType);
	virtual ~StepperMotor();
	virtual bool SetMotorConfig(MotorConfig*);
	virtual bool GetMotorConfig(MotorConfig*);
	virtual void StopMotor();
	virtual void MoveMotorContinuously();
	void MoveMotorBySteps(ULONG);
	void MoveMotortoStep(ULONG step);
	void MoveMotorByDistance(ULONG);
};

class DcMotor : public BaseMotor
{
private:
	DcMotor();

public:
	DcMotor(MotorType);
	virtual ~DcMotor();
	virtual bool SetMotorConfig(MotorConfig*);
	virtual bool GetMotorConfig(MotorConfig*);
	virtual void StopMotor();
	virtual void MoveMotorContinuously();
};

class MotorControl
{
private:
	static TID taskId;
	static StepperMotor* BaseMotor;
	static StepperMotor* CrossMotor;
	static DcMotor* DrillMotor;

public:
	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
};

}

#endif /* MOTORCONTROL_HPP_ */
