#ifndef _MYSQL_COMMAND_H_
#define _MYSQL_COMMAND_H_

#include "sql_include.h"

namespace MySql
{

class Connection;
class DataReader;
class DataItem;
class Command
{
public:
	Command(std::shared_ptr<Connection>& conn);
	Command(std::shared_ptr<Connection>& conn, const std::string& text);
	~Command();

	void SetCommandText(const std::string& text);
	void SetCommandType(CommandType type);

	std::shared_ptr<Connection>& getConnection();

	uint64_t ExecuteNonQuery();
	std::shared_ptr<DataReader> ExecuteReader();
	std::shared_ptr<DataItem> ExecuteScalar();

	uint64_t GetInsertId();

private:
	std::vector<std::string> SplitMultiQuery();

private:
	std::string m_text;
	CommandType m_type;
	std::shared_ptr<Connection> m_conn;
};

}; // namespace MySql

#endif // _MYSQL_COMMAND_H_