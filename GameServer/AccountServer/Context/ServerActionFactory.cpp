#include "ServerActionFactory.h"
#include "MsgType.h"

ServerActionFactory::ServerActionFactory()
{
}

ServerActionFactory::~ServerActionFactory()
{
}

Action* ServerActionFactory::GetAction(int msg_type, Entry& entry)
{
    Action* action = nullptr;
    switch (msg_type)
    {
    case SYS_MSG_USER_HAS_LOGINED:
        break;
    default:
        break;
    }
    return action;
}
