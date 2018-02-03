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

typedef enum
{
	COMMAND_TYPE_INVALID = -1,
	COMMAND_TYE_BASE_MOTOR,
	COMMAND_TYE_CROSS_MOTOR,
	COMMAND_TYE_DRILL_MOTOR,
	COMMAND_MAX,
}CmdType;

typedef struct
{
	BIT dir;
	ULONG steps;
	USHORT crc;
}MveStepsCmd;

typedef struct
{
	BIT dir;
	ULONG distance;
	USHORT crc;
}MveDistCmd;

typedef struct
{
	BIT dir;
	ULONG duration;
	USHORT crc;
}MveTimeCmd;

typedef struct
{
	UBYTE cmdType;
	UBYTE command;
	union
	{
		MveStepsCmd mvStepCmd;
		MveDistCmd mvDistCmd;
		MveTimeCmd mvTimeCmd;
	}CmdArg;
}InterfaceCmd;

class ComBase
{
private:

protected:

public:
	ComBase();
	virtual ~ComBase();
	virtual bool ProcessMsgFromInterface(InterfaceCmd* buf, ULONG size) = 0;
	virtual bool SendMsgToInterface(UBYTE*, ULONG) = 0;
	virtual bool SendAliveMsg() = 0;
};

class SerialCom : public ComBase
{
private:

public:
	SerialCom();
	~SerialCom();
	virtual bool ProcessMsgFromInterface(InterfaceCmd* buf, ULONG size);
	virtual bool SendMsgToInterface(UBYTE*, ULONG);
	virtual bool SendAliveMsg();
};

class ComInterface
{
private:
//	static ULONG aliveMsgTimeoutCount;
	static InterfaceCmd msg;
	static ULONG msgSize;
	static TID taskId;
	static ComBase* comChannel;
	static bool isMsgReceived;
public:
	ComInterface();
	~ComInterface();
	static bool TaskInit();
	static void TaskRun();
	static void SetTaskId(TID);
	static TID GetTaskId();
	static void SendMessage(UBYTE* buf, ULONG size);
};

}

#endif /* COMMUNICATIONINTERFACE_HPP_ */
