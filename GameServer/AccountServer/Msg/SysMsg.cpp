#include "SysMsg.h"
#include "MsgType.h"

SysMsgAccountLogined::SysMsgAccountLogined()
{
    SetType(SYS_MSG_USER_HAS_LOGINED);
    m_info = (MSG_INFO*)GetBuffer();
    SetLen(sizeof(MSG_INFO));
}

SysMsgAccountLogined::~SysMsgAccountLogined()
{
}
