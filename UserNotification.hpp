/*
 * UserNotification.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef USERNOTIFICATION_HPP_
#define USERNOTIFICATION_HPP_

namespace UserNotificationNs
{

class UserNotification
{
private:

public:
	UserNotification();
	~UserNotification();
	static void TaskEntry();
	void Run();
};

}

#endif /* USERNOTIFICATION_HPP_ */
