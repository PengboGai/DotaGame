#include "AccountEntry.h"
#include "ActionFactory.h"
#include "Context.h"

AccountEntry::AccountEntry(ISocketHandler& h)
: Entry(h)
{
}

AccountEntry::AccountEntry(ISocketHandler& h, size_t isize, size_t osize)
: Entry(h, isize, osize)
{
}

AccountEntry::~AccountEntry()
{
}

std::shared_ptr<IActionFactory> AccountEntry::GetActionFactory()
{
    return Context::GetInstance()->GetActionFactory();
}
