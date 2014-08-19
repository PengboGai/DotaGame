#ifndef _MYSQL_CONNECTION_H_
#define _MYSQL_CONNECTION_H_

#include "sql_include.h"

namespace MySql
{

class Command;
class Connection : public std::enable_shared_from_this<Connection>
{
public:
	Connection(const std::string& conn_str);
	~Connection();

	// HostName=localhost;DataBase=test;Port=3306;User=root;Pwd=root
	void SetConnectionString(const std::string& conn_str);

	bool IsConnected();
	bool Open();
	void Close();

	std::shared_ptr<Command> CreateCommand();

private:
	void ParseConnStr();
	void SetOption(MYSQL& mysql);

protected:
	friend class Command;

	std::string m_conn_str;
	std::string m_host;
	std::string m_user;
	std::string m_pwd;
	std::string m_db;
	unsigned short m_port;
	MYSQL m_mysql;
};

}; // namespace MySql

#endif // _MYSQL_CONNECTION_H_