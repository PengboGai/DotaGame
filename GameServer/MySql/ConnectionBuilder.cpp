#include "ConnectionBuilder.h"
#include "StringTool.h"

using namespace Utilities;

namespace MySql
{

ConnectionBuilder::ConnectionBuilder()
: m_hostname("localhost")
, m_dbname("mysql")
, m_port(3306)
, m_user("root")
, m_pwd("root")
{
}

ConnectionBuilder::~ConnectionBuilder()
{
}

void ConnectionBuilder::SetHostName(const std::string& hostname)
{
	m_hostname = hostname;
}

const std::string& ConnectionBuilder::GetHostName()
{
	return m_hostname;
}

void ConnectionBuilder::SetDbName(const std::string& dbname)
{
	m_dbname = dbname;
}

const std::string& ConnectionBuilder::GetDbName()
{
	return m_dbname;
}

void ConnectionBuilder::SetUser(const std::string& user)
{
	m_user = user;
}

const std::string& ConnectionBuilder::GetUser()
{
	return m_user;
}

void ConnectionBuilder::SetPwd(const std::string& pwd)
{
	m_pwd = pwd;
}

const std::string& ConnectionBuilder::GetPwd()
{
	return m_pwd;
}

void ConnectionBuilder::SetPort(unsigned short port)
{
	m_port = port;
}

unsigned short ConnectionBuilder::GetPort()
{
	return m_port;
}

std::string ConnectionBuilder::GetConnectionString()
{
	return StringTool::Format("HostName=%s;DataBase=%s;Port=%d;User=%s;Pwd=%s",
		m_hostname.c_str(), m_dbname.c_str(), m_port, m_user.c_str(), m_pwd.c_str());
}

} // namespace MySql
