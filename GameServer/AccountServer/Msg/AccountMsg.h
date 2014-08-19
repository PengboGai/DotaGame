#ifndef _ACCOUNT_MESSAGE_H_
#define _ACCOUNT_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

class CMsgAccountLogin : public BaseMsg
{
public:
	struct SM_DATA_IN
	{
		char name[20];
		char pwd[20];
		char ip[16];
	};

public:
	CMsgAccountLogin();
	~CMsgAccountLogin();

	const char* getUserName();
	void setUserName(const char* name, unsigned int len);

	const char* getUserPwd();
	void setUserPwd(const char* pwd, unsigned int len);

	const char* getUserIP();
	void setUserIP(const char* ip, unsigned int len);

protected:
	CREATE_DATA_IN_FUNC(SM_DATA_IN);
};

class SMsgAccountLogin : public BaseMsg
{
public:
	typedef enum {
		LR_FAIL,
		LR_SUCCESS,
		LR_NOT_EXIST_USER_NAME,
		LR_INVALID_PASSWORD,
	} LoginResult;

public:
	struct SM_DATA_IN
	{
		unsigned char result;
	};

public:
	SMsgAccountLogin();
	~SMsgAccountLogin();

	void setResult(LoginResult result);
	LoginResult getResult();

protected:
	CREATE_DATA_IN_FUNC(SM_DATA_IN);
};

#pragma pack(pop)

#endif // _ACCOUNT_MESSAGE_H_