#include "PlayerEntry.h"
#include "PlayerActionFactory.h"
#include "Context.h"

PlayerEntry::PlayerEntry(ISocketHandler& h)
: Entry(h)
{
}

PlayerEntry::PlayerEntry(ISocketHandler& h, size_t isize, size_t osize)
: Entry(h, isize, osize)
{
}

PlayerEntry::~PlayerEntry()
{
}

std::shared_ptr<IActionFactory> PlayerEntry::GetActionFactory()
{
    return Context::GetInstance()->GetPlayerActionFactory();
}
