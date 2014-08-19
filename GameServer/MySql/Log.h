#ifndef _MYSQL_LOG_H_
#define _MYSQL_LOG_H_

#include "sql_include.h"

namespace MySql
{

class Log
{
public:
	Log();
	~Log();

	static void Info(const std::string& info_str);
	static void Error(const std::string& err_str);
	static void DbErr(MYSQL* mysql, const std::string& query_str);
};

}; // namespace MySql

#endif // _MYSQL_LOG_H_