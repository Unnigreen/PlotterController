/*
 * Scheduler.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

#include "typedef.hpp"
#include "common.hpp"

namespace SchedulerNs
{

#define MAX_TASKS			8

typedef void (*taskRunFn_ptr)();
typedef bool (*taskInitFn_ptr)();

typedef struct
{
	TID taskId;
	USHORT taskPrio;
	bool isTaskEnabled;
	ULONG taskTicksToRun;
	ULONG taskTickCount;
	taskInitFn_ptr taskInitFn;
	taskRunFn_ptr taskRunFn;
}taskControlBlock;

class Scheduler
{
private:
	static taskControlBlock taskInfo[MAX_TASKS];
	static bool isSchdulerUp;
public:
	static ULONG schedulerTriggerCount;

	static void schedulerTimerInit();
	static void Init();
	static void Start();
	static void Run(void);
	static void DisableTask(TID);
	static void EnableTask(TID);
	static TID CreateTask(USHORT taskPrio, ULONG ticksToRun, taskInitFn_ptr taskInitFn, taskRunFn_ptr taskRunFn);
	static void DecrementSchedulerTriggerCount();
};

}

#endif /* SCHEDULER_HPP_ */
