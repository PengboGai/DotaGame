#include "Entry.h"
#include "BaseMsg.h"
#include "Action.h"
#include "IActionFactory.h"

Entry::Entry(ISocketHandler& h)
: TcpSocket(h)
{
}

Entry::Entry(ISocketHandler& h, size_t isize, size_t osize)
: TcpSocket(h, isize, osize)
{
}

Entry::~Entry()
{
}

void Entry::OnRead()
{
    TcpSocket::OnRead();

    const char* buf = ibuf.GetStart();
    if (buf) {
        OnMessage(buf);
        ibuf.Remove(((MSG_HEAD*)buf)->len);
    }
}

void Entry::OnMessage(const char* msg)
{
    MSG_HEAD* head = (MSG_HEAD*)msg;
    Action* action = GetActionFactory()->GetAction(head->type, *this);
    if (action) {
        action->onMessage(head);
        delete action;
    }
}
