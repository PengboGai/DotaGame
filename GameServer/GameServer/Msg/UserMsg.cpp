#include "UserMsg.h"
#include "MsgType.h"

CMsgUserLogin::CMsgUserLogin()
{
    SetType(MSG_USER_LOGIN_C);
    m_info = (MSG_INFO*)GetBuffer();
    SetLen(sizeof(MSG_INFO));
}

CMsgUserLogin::~CMsgUserLogin()
{
}

//////////////////////////////////////////////////////////////////////////
SMsgUserLogin::SMsgUserLogin()
{
    SetType(MSG_USER_LOGIN_S);
    m_info = (MSG_INFO*)GetBuffer();
    SetLen(sizeof(MSG_INFO));
}

SMsgUserLogin::~SMsgUserLogin()
{
}

//////////////////////////////////////////////////////////////////////////
SMsgUserInfo::SMsgUserInfo()
{
    SetType(MSG_USER_INFO_S);
    m_info = (MSG_INFO*)GetBuffer();
    SetLen(sizeof(MSG_INFO));
}

SMsgUserInfo::~SMsgUserInfo()
{
}
