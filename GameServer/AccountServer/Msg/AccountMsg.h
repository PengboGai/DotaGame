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
	enum LoginResult
	{
		LR_FAIL,					// ʧ��
		LR_SUCCESS,					// �ɹ�
		LR_INVALID_USER_OR_PWD		// �û������������
	};

public:
	SMsgAccountLogin();
	~SMsgAccountLogin();

public:
	struct MSG_INFO : MSG_HEAD
	{
		unsigned char result;
		unsigned long long userid;
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
	enum RegResult
	{
		RR_FAIL,					// ʧ��
		RR_SUCCESS,					// ע��ɹ�
		RR_EXIST_USER,				// �û����Ѵ���
		RR_PWD_DIFFERENT,			// �������벻һ��
	};

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

//////////////////////////////////////////////////////////////////////////
// �ַ��б���Ϣ
class SMsgServerList : public BaseMsg
{
public:
	enum ServerStatus
	{
		SS_NEW,		// �·�
		SS_GOOD,	// ����
		SS_HOT,		// ��
	};

public:
	SMsgServerList();
	~SMsgServerList();

	void AddServer(char name[20], ServerStatus status, char ip[16], unsigned short port);

public:
	struct SERVER_INFO
	{
		char name[20];			// �ַ�����
		char ip[16];			// IP��ַ
		unsigned char status;	// ״̬
		unsigned short port;	// �˿ں�
	};

	struct MSG_INFO : MSG_HEAD
	{
		unsigned char end;		// �Ƿ����һ����Ϣ
		unsigned short count;	// �б�����
		SERVER_INFO servers[1];	// �ַ��б�
	};
	MSG_INFO* m_info;
};

#pragma pack(pop)

#endif // _ACCOUNT_MESSAGE_H_