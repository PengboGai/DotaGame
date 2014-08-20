#include "AccountMsg.h"
#include "MsgType.h"

CMsgAccountLogin::CMsgAccountLogin()
{
	SetType(MSG_ACCOUNT_LOGIN_C);
	m_info = (MSG_INFO*)GetBuffer();
	SetLen(sizeof(MSG_INFO));
}

CMsgAccountLogin::~CMsgAccountLogin()
{
}

//////////////////////////////////////////////////////////////////////////
SMsgAccountLogin::SMsgAccountLogin()
{
	SetType(MSG_ACCOUNT_LOGIN_S);
	m_info = (MSG_INFO*)GetBuffer();
	SetLen(sizeof(MSG_INFO));
}

SMsgAccountLogin::~SMsgAccountLogin()
{
}

//////////////////////////////////////////////////////////////////////////
CMsgAccountReg::CMsgAccountReg()
{
	SetType(MSG_ACCOUNT_REG_C);
	m_info = (MSG_INFO*)GetBuffer();
	SetLen(sizeof(MSG_INFO));
}

CMsgAccountReg::~CMsgAccountReg()
{
}

//////////////////////////////////////////////////////////////////////////
SMsgAccountReg::SMsgAccountReg()
{
	SetType(MSG_ACCOUNT_REG_S);
	m_info = (MSG_INFO*)GetBuffer();
	SetLen(sizeof(MSG_INFO));
}

SMsgAccountReg::~SMsgAccountReg()
{
}

//////////////////////////////////////////////////////////////////////////
SMsgServerList::SMsgServerList()
{
	SetType(MSG_SERVER_LIST_S);
	m_info = (MSG_INFO*)GetBuffer();
	SetLen(sizeof(MSG_INFO));
}

SMsgServerList::~SMsgServerList()
{
}