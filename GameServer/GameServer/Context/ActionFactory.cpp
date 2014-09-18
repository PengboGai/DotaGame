#include "ActionFactory.h"
#include "MsgType.h"

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
    default:
        break;
    }
    return action;
}
