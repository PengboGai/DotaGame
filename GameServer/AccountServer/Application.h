#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <memory>
#include "SocketHandler.h"
#include "Connection.h"
#include "Command.h"
#include "TimerManager.h"
#include "LoginOverTime.h"

using namespace MySql;
using namespace Utilities;

class Application
{
    typedef SocketHandler RequestHandler;

public:
    Application(unsigned short port);
    ~Application();

    static Application* GetInstance() { return s_instance; }

public:
    void Init();
    bool Run();

    TimerManager& GetTimerManager() { return m_timer_mgr; }

    std::shared_ptr<Command> CreateCommand();

private:
    unsigned short m_port;
    RequestHandler m_handler;
    TimerManager m_timer_mgr;
    LoginOverTime m_login_overtime;
    std::shared_ptr<Connection> m_conn;

    static Application* s_instance;
};

#endif // _APPLICATION_H_