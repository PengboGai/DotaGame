#include "Context.h"
#include "GameServers.h"
#include "ActionFactory.h"
#include "TimerManager.h"
#include "Timer.h"
#include "Application.h"

using namespace Utilities;

const static int kOnlineTimerInterval = 1000;

Context::Context()
: m_servers(new GameServers())
, m_factory(new ActionFactory())
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

std::shared_ptr<ActionFactory> Context::GetActionFactory()
{
    return m_factory;
}

std::shared_ptr<OnlineOvertime> Context::GetOnlineOvertime()
{
    if (m_online == nullptr) {
        m_online = std::shared_ptr<OnlineOvertime>(new OnlineOvertime());

        auto tick = std::bind(&OnlineOvertime::Tick, m_online.get(), std::placeholders::_1);
        Timer* timer = new Timer(tick, kOnlineTimerInterval, Timer::REPEAT_FOREVER);
        Application::GetInstance()->GetTimerManager().AddTimer(timer);
    }
    return m_online;
}
