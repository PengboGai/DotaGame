#include "Application.h"
#include "ListenSocket.h"
#include "ConnectionBuilder.h"
#include "AccountEntry.h"

Application* Application::s_instance = nullptr;

Application::Application()
{
    s_instance = this;
}

Application::~Application()
{
    s_instance = nullptr;

    if (m_conn) {
        m_conn->Close();
    }
}

void Application::Init()
{
    InitDb();
}

bool Application::Run()
{
    ListenSocket<AccountEntry> listener(m_handler);
    if (listener.Bind(6220)) {
        return false;
    }
    m_handler.Add(&listener);
    m_handler.Select(1, 0);
    while (m_handler.GetCount()) {
        m_handler.Select(0, 100 * 1000);
        m_timer_mgr.Tick();
    }
    return true;
}

void Application::InitDb()
{
    if (m_conn == nullptr) {
        ConnectionBuilder builder;
        builder.SetHostName("localhost");
        builder.SetDbName("test2");
        builder.SetPort(3306);
        builder.SetUser("root");
        builder.SetPwd("root");

        m_conn = std::shared_ptr<Connection>(new Connection(builder.GetConnectionString()));
        if (m_conn) {
            if (!m_conn->Open()) {
                m_conn.reset();
            }
        }
    }
}
