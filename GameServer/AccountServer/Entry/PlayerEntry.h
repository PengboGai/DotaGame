#ifndef _PLAYER_ENTRY_H_
#define _PLAYER_ENTRY_H_

#include "Entry.h"

class PlayerEntry : public Entry
{
public:
    PlayerEntry(ISocketHandler& h);
    PlayerEntry(ISocketHandler& h, size_t isize, size_t osize);
    ~PlayerEntry();

protected:
    virtual std::shared_ptr<IActionFactory> GetActionFactory() override;
};

#endif // _PLAYER_ENTRY_H_