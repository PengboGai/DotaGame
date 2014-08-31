#ifndef _PLAYER_ACTION_FACTORY_H_
#define _PLAYER_ACTION_FACTORY_H_

#include "IActionFactory.h"

class PlayerActionFactory : public IActionFactory
{
public:
    PlayerActionFactory();
    virtual ~PlayerActionFactory();

public:
    virtual Action* GetAction(int msg_type, Entry& entry) override;
};

#endif // _PLAYER_ACTION_FACTORY_H_