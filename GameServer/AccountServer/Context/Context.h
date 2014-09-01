#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <memory>

class GameServers;
class PlayerActionFactory;
class ServerActionFactory;

class Context
{
public:
    Context();
    ~Context();

    static Context* GetInstance();

    std::shared_ptr<GameServers> GetGameServers();
    std::shared_ptr<PlayerActionFactory> GetPlayerActionFactory();
    std::shared_ptr<ServerActionFactory> GetServerActionFactory();

private:
    std::shared_ptr<GameServers> m_servers;
    std::shared_ptr<PlayerActionFactory> m_factory;
    std::shared_ptr<ServerActionFactory> m_server_factory;
};

#endif // _CONTEXT_H_