/*
 * CommunicationInterface.hpp
 *
 *  Created on: Feb 2, 2018
 *      Author: unni
 */

#ifndef COMMUNICATIONINTERFACE_HPP_
#define COMMUNICATIONINTERFACE_HPP_

#include "typedef.hpp"

namespace CommunicationInterface
{

class ComBase
{
private:

public:
	ComBase();
	virtual ~ComBase();
	virtual bool ReceiveCommand() = 0;
	virtual bool MsgToInterface(UBYTE*, ULONG) = 0;
	virtual bool SendAliveMsg() = 0;
};

class SerialCom : public ComBase
{
private:

public:
	SerialCom();
	~SerialCom();
	virtual bool ReceiveCommand();
	virtual bool MsgToInterface(UBYTE*, ULONG);
	virtual bool SendAliveMsg();
};

class ComInterface
{
private:
	static ULONG aliveMsgTimeoutCount;
	static TID taskId;
	static ComBase* comChannel;

public:
	ComInterface();
	~ComInterface();
	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
	static void SendMessage();
};

}

#endif /* COMMUNICATIONINTERFACE_HPP_ */
