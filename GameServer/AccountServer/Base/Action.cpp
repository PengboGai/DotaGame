#include "Action.h"
#include "Entry.h"
#include "BaseMsg.h"
#include "Application.h"

Action::Action(Entry& entry)
: m_entry(entry)
, m_cmd(nullptr)
{
}

Action::~Action()
{
}

void Action::Send(BaseMsg* msg)
{
    m_entry.SendBuf(msg->GetBuffer(), msg->GetLen());
}

TimerManager& Action::GetTimerManager()
{
    return Application::GetInstance()->GetTimerManager();
}

std::shared_ptr<Command> Action::GetCommand()
{
    if (m_cmd == nullptr) {
        m_cmd = Application::GetInstance()->CreateCommand();
    }
    return m_cmd;
}
