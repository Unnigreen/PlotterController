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

class InputConditioning
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

#endif /* INPUTPROCESSING_HPP_ */
