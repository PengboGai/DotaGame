#include "Context.h"
#include "ActionFactory.h"

Context::Context()
: m_factory(new ActionFactory())
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

std::shared_ptr<ActionFactory> Context::GetActionFactory()
{
    return m_factory;
}
