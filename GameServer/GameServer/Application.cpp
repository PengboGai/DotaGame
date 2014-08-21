#include "Application.h"
#include "ListenSocket.h"
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
}

bool Application::Run()
{
    return true;
}