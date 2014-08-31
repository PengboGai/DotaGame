#include "PlayerActionFactory.h"
#include "MsgType.h"

PlayerActionFactory::PlayerActionFactory()
{
}

PlayerActionFactory::~PlayerActionFactory()
{
}

Action* PlayerActionFactory::GetAction(int msg_type, Entry& entry)
{
    Action* action = nullptr;
    switch (msg_type)
    {
    case MSG_ACCOUNT_LOGIN_C:
        break;
    case MSG_ACCOUNT_REG_C:
        break;
    default:
        break;
    }
    return action;
}
