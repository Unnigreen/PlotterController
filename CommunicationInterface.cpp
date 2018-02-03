/*
 * CommunicationInterface.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "CommunicationInterface.hpp"
#include "string.h"

namespace CommunicationInterface
{

#define ALIVE_MSG_TIME_INTERVAL_MS		100

//ULONG ComInterface::aliveMsgTimeoutCount = 0;
InterfaceCmd ComInterface::msg;
ULONG ComInterface::msgSize;

ComBase::ComBase()
{

}

ComBase::~ComBase()
{

}

SerialCom::SerialCom()
{
	Serial.begin(115200);
}

SerialCom::~SerialCom()
{

}

bool SerialCom::ProcessMsgFromInterface(InterfaceCmd* buf, ULONG size)
{
	bool retVal = false;

	if(size <= sizeof(InterfaceCmd))
	{
		switch(buf->cmdType)
		{
		case COMMAND_TYE_BASE_MOTOR:
		case COMMAND_TYE_CROSS_MOTOR:
		case COMMAND_TYE_DRILL_MOTOR:
			break;
		default:
			break;
		}
	}
	return retVal;
}

bool SerialCom::SendMsgToInterface(UBYTE* buf, ULONG size)
{
	bool retVal = false;

	Serial.write(buf, size);
	return retVal;
}

bool SerialCom::SendAliveMsg()
{
	bool retVal = false;
	UBYTE aliveMsg[] = "ALIVE-01";

	SendMsgToInterface(aliveMsg, sizeof aliveMsg);
	return retVal;
}

ComInterface::ComInterface()
{

}

ComInterface::~ComInterface()
{

}

bool ComInterface::TaskInit()
{
	bool retVal = false;

	comChannel = new SerialCom();

	return retVal;
}

void ComInterface::TaskRun()
{
	if(isMsgReceived == true)
	{
		comChannel->ProcessMsgFromInterface(&msg, msgSize);
	}
}

void ComInterface::SetTaskId(TID id)
{
	taskId = id;
}

TID ComInterface::GetTaskId()
{
	return taskId;
}

void ComInterface::SendMessage(UBYTE* buf, ULONG size)
{
	if(isMsgReceived == false)
	{
		if(size <= sizeof(InterfaceCmd))
		{
			memcpy((void*)&msg, buf, size);
		}
		else
		{
			/* error: message received is longer than maximum expected */
		}
	}
	else
	{
		/* error: received message under process, cannot receive new one */
	}
}

}
