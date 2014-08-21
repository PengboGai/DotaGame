#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <memory>
#include "SocketHandler.h"

class Application
{
	typedef SocketHandler RequestHandler;

public:
	Application(unsigned short port);
	~Application();

	static Application* GetInstance() { return s_instance; }

	bool Run();

private:
	unsigned short m_port;
	RequestHandler m_handler;

	static Application* s_instance;
};

#endif // _APPLICATION_H_