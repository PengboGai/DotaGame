#include "ActionFactory.h"
#include "MsgType.h"
#include "Action1000.h"
#include "Action1002.h"

ActionFactory::ActionFactory()
{
}

ActionFactory::~ActionFactory()
{
}

Action* ActionFactory::GetAction(int msg_type, Entry& entry)
{
    Action* action = nullptr;
    switch (msg_type)
    {
    case MSG_ACCOUNT_LOGIN_C:
        action = new Action1000(entry);
        break;
    case MSG_ACCOUNT_REG_C:
        action = new Action1002(entry);
        break;
    default:
        break;
    }
    return action;
}
