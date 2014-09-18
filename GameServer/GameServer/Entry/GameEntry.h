#ifndef _GAME_ENTRY_H_
#define _GAME_ENTRY_H_

#include "Entry.h"

class GameEntry : public Entry
{
public:
    GameEntry(ISocketHandler& h);
    GameEntry(ISocketHandler& h, size_t isize, size_t osize);
    ~GameEntry();

protected:
    virtual std::shared_ptr<IActionFactory> GetActionFactory() override;
};

#endif // _GAME_ENTRY_H_