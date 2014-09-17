#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <memory>
#include "Connection.h"
#include "TimerManager.h"
#include "Handler.h"

using namespace MySql;
using namespace Utilities;

class Application
{
public:
    Application();
    ~Application();

public:
    static Application* GetInstance() { return s_instance; }

    void Init();
    bool Run();

    TimerManager& GetTimerManager() { return m_timer_mgr; }
    std::shared_ptr<Connection> GetConnection() { return m_conn; }

private:
    void InitDb();

private:
    Handler m_handler;
    TimerManager m_timer_mgr;
    std::shared_ptr<Connection> m_conn;

    static Application* s_instance;
};

#endif // _APPLICATION_H_