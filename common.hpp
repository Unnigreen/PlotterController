/*
 * common.hpp
 *
 *  Created on: Jan 25, 2018
 *      Author: unni
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#define TASK_TICK_10MS	 (1)
#define TASK_TICK_20MS	 (TASK_TICK_10MS * 2)
#define TASK_TICK_50MS	 (TASK_TICK_10MS * 5)
#define TASK_TICK_100MS	 (TASK_TICK_10MS * 10)
#define TASK_TICK_200MS	 (TASK_TICK_100MS * 2)
#define TASK_TICK_500MS	 (TASK_TICK_100MS * 5)
#define TASK_TICK_1000ms (TASK_TICK_10MS * 100)

#define TASK_INPUT_CONDITIONING_TICK 	TASK_TICK_20MS
#define TASK_MOTOR_CONTROL_TICK		 	TASK_TICK_10MS
#define TASK_USER_NOTIFICATION_TICK 	TASK_TICK_50MS
#define TASK_PLOTTER_CONTROLLER_TICK 	TASK_TICK_100MS

#define TASK_ID_INVALID		0
#define TASK_INIT_FAILED	-1

typedef enum
{
	TASK_CREATE_RESPONSE_INVALID = -1,
	TASK_CREATE_RESPONSE_SUCCESS,
	TASK_CREATE_RESPONSE_FAILURE,
	TASK_CREATE_RESPONSE_MAX
}eTaskCreateResponse;

#endif /* COMMON_HPP_ */
