#ifndef _SERVER_ACTION_FACTORY_H_
#define _SERVER_ACTION_FACTORY_H_

#include "IActionFactory.h"

class ServerActionFactory : public IActionFactory
{
public:
    ServerActionFactory();
    virtual ~ServerActionFactory();

public:
    virtual Action* GetAction(int msg_type, Entry& entry) override;
};

#endif // _SERVER_ACTION_FACTORY_H_