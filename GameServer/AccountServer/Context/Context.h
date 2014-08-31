#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <memory>

class GameServers;
class PlayerActionFactory;

class Context
{
public:
    Context();
    ~Context();

    static Context* GetInstance();

    std::shared_ptr<GameServers> GetGameServers();
    std::shared_ptr<PlayerActionFactory> GetPlayerActionFactory();

private:
    std::shared_ptr<GameServers> m_servers;
    std::shared_ptr<PlayerActionFactory> m_factory;
};

#endif // _CONTEXT_H_