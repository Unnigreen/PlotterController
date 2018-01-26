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
public:

	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
};

}

#endif /* _Plotter_Controller_H_ */
