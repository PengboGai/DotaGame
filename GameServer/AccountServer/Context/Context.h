#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <memory>
#include "OnlineOvertime.h"

class GameServers;
class ActionFactory;

class Context
{
public:
    Context();
    ~Context();

    static Context* GetInstance();

    std::shared_ptr<GameServers> GetGameServers();
    std::shared_ptr<ActionFactory> GetActionFactory();
    std::shared_ptr<OnlineOvertime> GetOnlineOvertime();

private:
    std::shared_ptr<GameServers> m_servers;
    std::shared_ptr<ActionFactory> m_factory;
    std::shared_ptr<OnlineOvertime> m_online;
};

#endif // _CONTEXT_H_