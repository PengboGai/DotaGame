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
		LR_FAIL,					// ʧ��
		LR_SUCCESS,					// �ɹ�
		LR_INVALID_USER_OR_PWD		// �û������������
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
		RR_FAIL,					// ʧ��
		RR_SUCCESS,					// ע��ɹ�
		RR_EXIST_USER,				// �û����Ѵ���
		RR_PWD_DIFFERENT,			// �������벻һ��
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