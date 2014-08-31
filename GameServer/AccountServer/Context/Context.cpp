#include "Context.h"
#include "GameServers.h"
#include "PlayerActionFactory.h"

Context::Context()
: m_servers(new GameServers())
, m_factory(new PlayerActionFactory())
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
