#include "ServerEntry.h"
#include "ServerActionFactory.h"
#include "Context.h"

ServerEntry::ServerEntry(ISocketHandler& h)
: Entry(h)
{
}

ServerEntry::ServerEntry(ISocketHandler& h, size_t isize, size_t osize)
: Entry(h, isize, osize)
{
}

ServerEntry::~ServerEntry()
{
}

std::shared_ptr<IActionFactory> ServerEntry::GetActionFactory()
{
    return Context::GetInstance()->GetServerActionFactory();
}
