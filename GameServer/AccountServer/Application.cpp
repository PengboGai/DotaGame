#include "Application.h"
#include "ListenSocket.h"
#include "LoginResponse.h"
#include "ConnectionBuilder.h"
#include "Debug.h"

Application* Application::s_instance = nullptr;

Application::Application(unsigned short port)
: m_port(port)
{
    s_instance = this;
}

Application::~Application()
{
    s_instance = nullptr;

    m_conn->Close();
}

void Application::Init()
{
    auto tick = std::bind(&LoginOverTime::Tick, &m_login_overtime, std::placeholders::_1);
    Timer* timer = new Timer(tick, 1000, Timer::REPEAT_FOREVER);
    m_timer_mgr.AddTimer(timer);
}

bool Application::Run()
{
    ListenSocket<LoginResponse> listener(m_handler);
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

std::shared_ptr<Command> Application::CreateCommand()
{
    if (m_conn == nullptr) {
        ConnectionBuilder builder;
        builder.SetDbName("test2");
        std::string conn_str = builder.GetConnectionString();
        m_conn = std::shared_ptr<Connection>(new Connection(conn_str));
        if (m_conn) {
            if (!m_conn->Open()) {
                m_conn.reset();
            }
        }
    }

    if (m_conn) {
        return m_conn->CreateCommand();
    }
    return nullptr;
}
