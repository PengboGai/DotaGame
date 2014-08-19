#include "BaseMsg.h"

BaseMsg::BaseMsg()
{
	memset(&_msg, 0, sizeof(SOCKET_MSG));
	_msg.len = sizeof(_msg.len) + sizeof(_msg.type);
}

BaseMsg::~BaseMsg()
{
}

void BaseMsg::getBuffer(char* buffer, unsigned short len)
{
	memset(buffer, 0, len);
	memcpy(buffer, (void*)&_msg, _msg.len);
}

char* BaseMsg::getBuffer(unsigned short len)
{
	char* buffer = new char[len];
	getBuffer(buffer, len);
	return buffer;
}

void BaseMsg::setBuffer(const char* buffer, unsigned short len)
{
	memset(&_msg, 0, sizeof(_msg));
	memcpy(&_msg, buffer, len);
}

unsigned short BaseMsg::getLen()
{
	return _msg.len;
}

void BaseMsg::setLen(unsigned short len)
{
	_msg.len = len + sizeof(_msg.len) + sizeof(_msg.type);
}

unsigned short BaseMsg::getType()
{
	return _msg.type;
}

void BaseMsg::setType(unsigned short type)
{
	_msg.type = type;
}

const char* BaseMsg::getData()
{
	return _msg.data;
}