#ifndef _ACCOUNT_MESSAGE_H_
#define _ACCOUNT_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

class CMsgAccountLogin : public BaseMsg
{
public:
	CMsgAccountLogin();
	~CMsgAccountLogin();

public:
	struct MSG_INFO : MSG_HEAD
	{
		char name[20];
		char pwd[20];
		char ip[16];
	};
	MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
class SMsgAccountLogin : public BaseMsg
{
public:
	typedef enum {
		LR_FAIL,					// 失败
		LR_SUCCESS,					// 成功
		LR_INVALID_USER_OR_PWD		// 用户名或密码错误
	} LoginResult;

public:
	SMsgAccountLogin();
	~SMsgAccountLogin();

public:
	struct MSG_INFO : MSG_HEAD
	{
		unsigned char result;
	};
	MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
class CMsgAccountReg : public BaseMsg
{
public:
	CMsgAccountReg();
	~CMsgAccountReg();

public:
	struct MSG_INFO : MSG_HEAD
	{
		char name[20];
		char pwd[20];
		char pwd2[20];
		char ip[16];
	};
	MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
class SMsgAccountReg : public BaseMsg
{
public:
	typedef enum {
		RR_FAIL,					// 失败
		RR_SUCCESS,					// 注册成功
		RR_EXIST_USER,				// 用户名已存在
		RR_PWD_DIFFERENT,			// 两次密码不一样
	} RegResult;

public:
	SMsgAccountReg();
	~SMsgAccountReg();

public:
	struct MSG_INFO : MSG_HEAD
	{
		unsigned char result;
	};
	MSG_INFO* m_info;
};

#pragma pack(pop)

#endif // _ACCOUNT_MESSAGE_H_