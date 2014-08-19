#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <memory>
#include "SocketHandler.h"
#include "Connection.h"
#include "Command.h"
using namespace MySql;

class Application
{
	typedef SocketHandler RequestHandler;

public:
	Application(unsigned short port);
	~Application();

	static Application* GetInstance() { return s_instance; }

	bool Run();

	std::shared_ptr<Command> CreateCommand();

private:
	unsigned short m_port;
	RequestHandler m_handler;
	std::shared_ptr<Connection> m_conn;

	static Application* s_instance;
};

#endif // _APPLICATION_H_