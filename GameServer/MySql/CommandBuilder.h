#ifndef _MYSQL_COMMAND_BUILDER_H_
#define _MYSQL_COMMAND_BUILDER_H_

#include "sql_include.h"

namespace MySql
{

class CommandBuilder
{
public:
	CommandBuilder();
	~CommandBuilder();

	std::string GetDeleteCommand();
	std::string GetInsertCommand();
	std::string GetUpdateCommand();

private:
};

}; // namespace MySql

#endif // _MYSQL_COMMAND_BUILDER_H_