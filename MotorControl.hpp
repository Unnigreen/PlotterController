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

class MotorControl
{
private:
	static TID taskId;
public:

	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
};

}


#endif /* MOTORCONTROL_HPP_ */
