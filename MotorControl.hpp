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

#define DC_DRILL_MOTOR_PIN			(3)
#define STEPPER_BASE_MOTOR_PIN		(5)
#define STEPPER_CROSS_MOTOR_PIN		(6)

typedef enum
{
	MOTOR_TYPE_INVALID = -1,
	MOTOR_TYPE_STEPPER_BASE,
	MOTOR_TYPE_STEPPER_CROSS,
	MOTOR_TYPE_DC_DRILL,
	MOTOR_TYPE_MAX
}MotorType;

typedef enum
{
	MOTOR_MOVE_TYPE_INVALID = -1,
	MOTOR_MOVE_TYPE_TO_FORWARDHOME,
	MOTOR_MOVE_TYPE_TO_BACKWARDHOME,
	MOTOR_MOVE_TYPE_CLOCKWISE,
	MOTOR_MOVE_TYPE_ANTICLOCKWISE,
	MOTOR_MOVE_TYPE_MAX
}MotorMoveType;

typedef struct
{
	USHORT pwmPin;
	USHORT accStepSize;
	USHORT stepSize;
	USHORT stepsPerMm;
	ULONG homeToHomeSteps;
	ULONG curStep;
	ULONG stepsToMove;
	MotorMoveType dirToMove;

}MotorConfig;

class BaseMotor
{
private:

protected:
	MotorConfig config;

public:
	BaseMotor();
	virtual ~BaseMotor();
	bool SetMotorConfig(MotorConfig*);
	bool GetMotorConfig(MotorConfig*);
	virtual void StopMotor() = 0;
	virtual void MoveMotorContinuously(MotorMoveType) = 0;
};

class StepperMotor : public BaseMotor
{
private:
	StepperMotor();

public:
	StepperMotor(MotorType);
	virtual ~StepperMotor();
//	virtual bool SetMotorConfig(MotorConfig*);
//	virtual bool GetMotorConfig(MotorConfig*);
	virtual void StopMotor();
	virtual void MoveMotorContinuously(MotorMoveType);
	void MoveMotorBySteps(SLONG);
	void MoveMotortoStep(ULONG step);
	void MoveMotorByDistance(SLONG);
};

class DcMotor : public BaseMotor
{
private:
	DcMotor();

public:
	DcMotor(MotorType);
	virtual ~DcMotor();
//	virtual bool SetMotorConfig(MotorConfig*);
//	virtual bool GetMotorConfig(MotorConfig*);
	virtual void StopMotor();
	virtual void MoveMotorContinuously(MotorMoveType);
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
