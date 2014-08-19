#include "Connection.h"
#include "Command.h"
#include "StringTool.h"

using namespace Utilities;

namespace MySql
{

#define HOST_NAME		"HostName"
#define DATA_BASE		"DataBase"
#define USER_NAME		"User"
#define PASSWORD		"Pwd"
#define PORT			"Port"

Connection::Connection(const std::string& conn_str)
: m_conn_str(conn_str)
, m_port(3306)
{
	ParseConnStr();
}

Connection::~Connection()
{
}

void Connection::SetConnectionString(const std::string& conn_str)
{
	if (m_conn_str != conn_str) {
		m_conn_str = conn_str;
		ParseConnStr();
	}
}

bool Connection::IsConnected()
{
	if (mysql_ping(&m_mysql)) {
		return false;
	}
	return true;
}

bool Connection::Open()
{
	if (!mysql_init(&m_mysql)) {
		// ERROR: INIT MYSQL FAILED
		return false;
	}
	SetOption(m_mysql);
	unsigned long flag = CLIENT_MULTI_RESULTS | CLIENT_FOUND_ROWS | CLIENT_INTERACTIVE;
	if (!mysql_real_connect(&m_mysql, m_host.c_str(), m_user.c_str(), m_pwd.c_str(), m_db.c_str(), m_port, nullptr, flag)) {
		// ERROR: CONNECT FAILED
		return false;
	}
	return true;
}

void Connection::Close()
{
	mysql_close(&m_mysql);
}

std::shared_ptr<Command> Connection::CreateCommand()
{
	std::shared_ptr<Command> cmd(new Command(shared_from_this()));
	return cmd;
}

void Connection::ParseConnStr()
{
	std::vector<std::string> items = StringTool::Split(m_conn_str, ";");
	std::vector<std::string>::iterator iter = items.begin();
	for (; iter != items.end(); ++iter) {
		std::vector<std::string> content = StringTool::Split(*iter, "=");
		if (content.size() == 2) {
			if (content[0] == HOST_NAME) {
				m_host = content[1];
			}
			else if (content[0] == DATA_BASE) {
				m_db = content[1];
			}
			else if (content[0] == USER_NAME) {
				m_user = content[1];
			}
			else if (content[0] == PASSWORD) {
				m_pwd = content[1];
			}
			else if (content[0] == PORT) {
				m_port = (unsigned short)atoi(content[1].c_str());
			}
		}
		else {
			// TODO: error
		}
	}
}

void Connection::SetOption(MYSQL& mysql)
{
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "");
	mysql_options(&mysql, MYSQL_OPT_CONNECT_TIMEOUT, "");
	mysql.options.read_timeout = 1000;
	mysql.reconnect = 1;
}

} // namespace MySql