// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

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
