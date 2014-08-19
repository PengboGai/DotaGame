#ifndef _BASE_MESSAGE_H_
#define _BASE_MESSAGE_H_

#include <memory>

#pragma pack(push, 1)

#define CREATE_DATA_IN_FUNC(__ST_TYPE__) \
	__ST_TYPE__* getDataIn() { return (__ST_TYPE__*)getData(); }

#define MSG_MAX_SIZE					1024

struct SOCKET_MSG
{
	unsigned short len;
	unsigned short type;
	char data[MSG_MAX_SIZE];
};

class BaseMsg
{
public:
	BaseMsg();
	virtual ~BaseMsg();

	void getBuffer(char* buffer, unsigned short len);
	char* getBuffer(unsigned short len);
	void setBuffer(const char* buffer, unsigned short len);

	unsigned short getLen();
	void setLen(unsigned short len);

	unsigned short getType();
	void setType(unsigned short type);

protected:
	const char* getData();

protected:
	struct SOCKET_MSG _msg;
};

#pragma pack(pop)

#endif // _BASE_MESSAGE_H_