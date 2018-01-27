/*
 * InputProcessing.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef INPUTCONDITIONING_HPP_
#define INPUTCONDITIONING_HPP_

#include "typedef.hpp"

namespace InputConditioningLogic
{

#define CALLBACK_ENABLE_INPUT_ON 	0x01
#define CALLBACK_ENABLE_INPUT_OFF 	0x02

#define FORWARD_HOME_IPNPUT_PIN		PIN_A0
#define BACKWARD_HOME_IPNPUT_PIN	PIN_A1

typedef void (* inputToggle_cb)(bool);

typedef struct
{
	UBYTE InputPin;
//	UBYTE InputPinMode;
	bool isInputHigh;
	bool wasInputHigh;
	bool DefinedOnState;
	bool isInputOn;
	bool isStateConfirmed;
	UBYTE CallbackEnable;
	inputToggle_cb cbPtr;
}InputInfo;

typedef enum
{
	INPUT_TYPE_INVALID = -1,
	INPUT_TYPE_FORWARD_HOME,
	INPUT_TYPE_BACKWARD_HOME,
	INPUT_TYPE_MAX
}InputType;

class InputConditioning
{
private:
	static TID taskId;
	static InputInfo InputArray[INPUT_TYPE_MAX];

public:
	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
};

}

#endif /* INPUTPROCESSING_HPP_ */
