#include "Context.h"
#include "GameServers.h"
#include "PlayerActionFactory.h"
#include "ServerActionFactory.h"

Context::Context()
: m_servers(new GameServers())
, m_factory(new PlayerActionFactory())
, m_server_factory(new ServerActionFactory())
{
}

Context::~Context()
{
}

Context* Context::GetInstance()
{
    static Context s_instance;
    return &s_instance;
}

std::shared_ptr<GameServers> Context::GetGameServers()
{
    return m_servers;
}

std::shared_ptr<PlayerActionFactory> Context::GetPlayerActionFactory()
{
    return m_factory;
}

std::shared_ptr<ServerActionFactory> Context::GetServerActionFactory()
{
    return m_server_factory;
}
