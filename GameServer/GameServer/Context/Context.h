#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <memory>

class ActionFactory;

class Context
{
public:
    Context();
    ~Context();

    static Context* GetInstance();

    std::shared_ptr<ActionFactory> GetActionFactory();

private:
    std::shared_ptr<ActionFactory> m_factory;
};

#endif // _CONTEXT_H_