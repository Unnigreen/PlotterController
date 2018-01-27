/*
 * InputProcessing.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "common.hpp"
#include "InputConditioning.hpp"
#include "PlotterController.hpp"

namespace InputConditioningLogic
{

TID InputConditioning::taskId = TASK_ID_INVALID;
InputInfo InputConditioning::InputArray[INPUT_TYPE_MAX] = {
	/*	 pin, 						is_high, 	was_high, 	define_on, 	is_on, 		state_confirm, 	callback_enable, 												callback_ptr */
		{FORWARD_HOME_IPNPUT_PIN, 	false, 		false, 		true, 		false, 		false, 			(UBYTE)(CALLBACK_ENABLE_INPUT_ON | CALLBACK_ENABLE_INPUT_OFF), 	PlotterControllerApp::PlotterController::ForwardHomeCallBack},
		{BACKWARD_HOME_IPNPUT_PIN, 	false, 		false, 		true, 		false, 		false, 			(UBYTE)(CALLBACK_ENABLE_INPUT_ON | CALLBACK_ENABLE_INPUT_OFF), 	PlotterControllerApp::PlotterController::BackwardHomeCallBack},
};

bool InputConditioning::TaskInit()
{
	for(UBYTE i = 0; i < (UBYTE)INPUT_TYPE_MAX; i++){
		pinMode(InputArray[i].InputPin, INPUT_PULLUP);
		InputArray[i].isInputHigh = digitalRead(InputArray[i].InputPin);

		InputArray[i].wasInputHigh = InputArray[i].isInputHigh;
		InputArray[i].isStateConfirmed = true;
		if(InputArray[i].DefinedOnState == InputArray[i].isInputHigh){ // detect On/Off state
			InputArray[i].isInputOn = true;
			if(InputArray[i].CallbackEnable & (UBYTE)CALLBACK_ENABLE_INPUT_ON){
				if(InputArray[i].cbPtr != NULL){ // call back if enabled and valid
					InputArray[i].cbPtr(true);
				}
			}
		}
		else{ // detect On/Off state
			InputArray[i].isInputOn = false;
			if(InputArray[i].CallbackEnable & (UBYTE)CALLBACK_ENABLE_INPUT_OFF){
				if(InputArray[i].cbPtr != NULL){ // call back if enabled and valid
					InputArray[i].cbPtr(false);
				}
			}
		}
	}
	return true;
}

void InputConditioning::TaskRun()
{
	for(UBYTE i = 0; i < (UBYTE)INPUT_TYPE_MAX; i++){
		InputArray[i].isInputHigh = digitalRead(InputArray[i].InputPin);
		if(InputArray[i].isInputHigh != InputArray[i].wasInputHigh){ // input state change detected
			if(InputArray[i].isStateConfirmed == true){ // wait to confirm state change detected
				InputArray[i].isStateConfirmed = false;
			}
			else{ // confirm state change detected
				InputArray[i].wasInputHigh = InputArray[i].isInputHigh;
				InputArray[i].isStateConfirmed = true;
				if(InputArray[i].DefinedOnState == InputArray[i].isInputHigh){ // detect On/Off state
					InputArray[i].isInputOn = true;
					if(InputArray[i].CallbackEnable & (UBYTE)CALLBACK_ENABLE_INPUT_ON){
						if(InputArray[i].cbPtr != NULL){ // call back if enabled and valid
							InputArray[i].cbPtr(true);
						}
					}
				}
				else{ // detect On/Off state
					InputArray[i].isInputOn = false;
					if(InputArray[i].CallbackEnable & (UBYTE)CALLBACK_ENABLE_INPUT_OFF){
						if(InputArray[i].cbPtr != NULL){ // call back if enabled and valid
							InputArray[i].cbPtr(false);
						}
					}
				}
			}
		}
		else{
			InputArray[i].isStateConfirmed = true;
		}
	}
}

void InputConditioning::SetTaskId(TID id)
{
	taskId = id;
}

TID InputConditioning::GetTaskId()
{
	return taskId;
}

}
