#ifndef _ACTION_FACTORY_H_
#define _ACTION_FACTORY_H_

#include "IActionFactory.h"

class ActionFactory : public IActionFactory
{
public:
    ActionFactory();
    virtual ~ActionFactory();

public:
    virtual Action* GetAction(int msg_type, Entry& entry) override;
};

#endif // _ACTION_FACTORY_H_