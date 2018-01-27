/*
 * PlotterController.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef _Plotter_Controller_H_
#define _Plotter_Controller_H_

#include "Arduino.h"
#include "typedef.hpp"

namespace PlotterControllerApp
{

class PlotterController
{
private:
	static TID taskId;
	static bool isMsgReceived;
	static bool ForwardHomeState;
	static bool BackwardHomeState;

public:

	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
	static void ForwardHomeCallBack(bool);
	static void BackwardHomeCallBack(bool);
};

}

#endif /* _Plotter_Controller_H_ */
