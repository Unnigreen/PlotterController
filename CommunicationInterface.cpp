/*
 * CommunicationInterface.cpp
 *
 *  Created on: Feb 2, 2018
 *      Author: unni
 */

#include "Arduino.h"
#include "CommunicationInterface.hpp"

namespace CommunicationInterface
{

#define ALIVE_MSG_TIME_INTERVAL_MS		100

ULONG ComInterface::aliveMsgTimeoutCount = 0;

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

bool SerialCom::ReceiveCommand()
{
	bool retVal = false;

	return retVal;
}

bool SerialCom::MsgToInterface(UBYTE* buf, ULONG size)
{
	bool retVal = false;

	Serial.write(buf, size);
	return retVal;
}

bool SerialCom::SendAliveMsg()
{
	bool retVal = false;
	UBYTE aliveMsg[] = "ALIVE-01";

	MsgToInterface(aliveMsg, sizeof aliveMsg);
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

}

void ComInterface::SetTaskId(TID id)
{
	taskId = id;
}

TID ComInterface::GetTaskId()
{
	return taskId;
}

void ComInterface::SendMessage()
{
//	comChannel->ReceiveCommand();
}

}
