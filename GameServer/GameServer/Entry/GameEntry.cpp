#include "GameEntry.h"
#include "ActionFactory.h"
#include "Context.h"

GameEntry::GameEntry(ISocketHandler& h)
: Entry(h)
{
}

GameEntry::GameEntry(ISocketHandler& h, size_t isize, size_t osize)
: Entry(h, isize, osize)
{
}

GameEntry::~GameEntry()
{
}

std::shared_ptr<IActionFactory> GameEntry::GetActionFactory()
{
    return Context::GetInstance()->GetActionFactory();
}
