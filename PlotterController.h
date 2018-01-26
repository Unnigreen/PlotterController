// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Plotter_Controller_H_
#define _Plotter_Controller_H_
#include "Arduino.h"

namespace PlotterControllerApp
{

class PlotterController
{
private:

public:

	static bool TaskInit();
	static void TaskRun();
};

}

#endif /* _Plotter_Controller_H_ */
