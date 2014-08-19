#include "Application.h"
#include "ListenSocket.h"
#include "LoginRequest.h"

Application* Application::s_instance = nullptr;

Application::Application(unsigned short port)
: m_port(port)
{
	s_instance = this;
}

Application::~Application()
{
	s_instance = nullptr;
}

bool Application::Run()
{
	ListenSocket<LoginRequest> listener(m_handler);
	if (listener.Bind(6220)) {
		return false;
	}
	m_handler.Add(&listener);
	m_handler.Select(1, 0);
	while (m_handler.GetCount()) {
		m_handler.Select(0, 500 * 1000);
	}
	return true;
}

std::shared_ptr<Connection> Application::GetDbConn()
{
	if (m_conn == nullptr) {
		std::string conn_str = "HostName=localhost;DataBase=test2;Port=3306;User=root;Pwd=23285155xbb";
		m_conn = std::shared_ptr<Connection>(new Connection(conn_str));
		if (m_conn && m_conn->Open()) {
			return m_conn;
		}

		if (m_conn) {
			m_conn.reset();
		}
		return nullptr;
	}
	return m_conn;
}
