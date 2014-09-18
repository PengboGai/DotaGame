#include "Action9000.h"
#include "SysMsg.h"
#include "Context.h"

Action9000::Action9000(Entry& entry)
: Action(entry)
{
}

Action9000::~Action9000()
{
}

void Action9000::onMessage(MSG_HEAD* head)
{
    SysMsgAccountLogined msg;
    msg.SetBuffer((const char*)head, head->len);

    if (Context::GetInstance()->GetOnlineOvertime()->IsUserOnline(msg.m_info->userid)) {
        msg.m_info->result = SysMsgAccountLogined::LR_LOGINED;
    }
    else {
        msg.m_info->result = SysMsgAccountLogined::LR_UNLOGIN;
    }
    Send(&msg);
}
