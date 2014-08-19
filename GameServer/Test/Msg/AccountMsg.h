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

//////////////////////////////////////////////////////////////////////////
class SMsgAccountLogin : public BaseMsg
{
public:
	typedef enum {
		LR_FAIL,					// ʧ��
		LR_SUCCESS,					// �ɹ�
		LR_INVALID_USER_OR_PWD		// �û������������
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

//////////////////////////////////////////////////////////////////////////
class CMsgAccountReg : public BaseMsg
{
public:
	struct SM_DATA_IN
	{
		char name[20];
		char pwd[20];
		char pwd2[20];
		char ip[16];
	};

public:
	CMsgAccountReg();
	~CMsgAccountReg();

	const char* getUserName();
	void setUserName(const char* name, unsigned int len);

	const char* getUserPwd();
	void setUserPwd(const char* pwd, unsigned int len);

	const char* getUserConfirmPwd();
	void setUserConfirmPwd(const char* pwd, unsigned int len);

	const char* getUserIP();
	void setUserIP(const char* ip, unsigned int len);

protected:
	CREATE_DATA_IN_FUNC(SM_DATA_IN);
};

//////////////////////////////////////////////////////////////////////////
class SMsgAccountReg : public BaseMsg
{
public:
	typedef enum {
		RR_FAIL,					// ʧ��
		RR_SUCCESS,					// ע��ɹ�
		RR_EXIST_USER,				// �û����Ѵ���
		RR_PWD_DIFFERENT,			// �������벻һ��
	} RegResult;

public:
	struct SM_DATA_IN
	{
		unsigned char result;
	};

public:
	SMsgAccountReg();
	~SMsgAccountReg();

	void setResult(RegResult result);
	RegResult getResult();

protected:
	CREATE_DATA_IN_FUNC(SM_DATA_IN);
};

#pragma pack(pop)

#endif // _ACCOUNT_MESSAGE_H_