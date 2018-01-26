/*
 * UserNotification.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef USERNOTIFICATION_HPP_
#define USERNOTIFICATION_HPP_

#include "typedef.hpp"

namespace UserNotificationLogic
{

class UserNotification
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

#endif /* USERNOTIFICATION_HPP_ */
