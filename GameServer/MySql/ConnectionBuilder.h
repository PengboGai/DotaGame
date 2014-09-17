#ifndef _MYSQL_CONNECTION_BUILDER_H_
#define _MYSQL_CONNECTION_BUILDER_H_

#include <string>

namespace MySql
{

#ifdef SetPort
#undef SetPort
#endif

class ConnectionBuilder
{
public:
	ConnectionBuilder();
	~ConnectionBuilder();

	void SetHostName(const std::string& hostname);
	const std::string& GetHostName();

	void SetDbName(const std::string& dbname);
	const std::string& GetDbName();

	void SetUser(const std::string& user);
	const std::string& GetUser();

	void SetPwd(const std::string& pwd);
	const std::string& GetPwd();

	void SetPort(unsigned short port);
	unsigned short GetPort();

	std::string GetConnectionString();

private:
	std::string m_hostname;
	std::string m_dbname;
	std::string m_user;
	std::string m_pwd;
	unsigned short m_port;
};

}; // namespace MySql

#endif // _MYSQL_CONNECTION_BUILDER_H_