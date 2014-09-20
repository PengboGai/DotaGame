#include "Action1000.h"
#include "UserMsg.h"
#include "StringTool.h"
#include "Entry.h"
#include "Context.h"

Action1000::Action1000(Entry& entry)
: Action(entry)
{
}

Action1000::~Action1000()
{
}

void Action1000::onMessage(MSG_HEAD* head)
{
    CMsgUserLogin msg;
    msg.SetBuffer((const char*)head, head->len);


}
