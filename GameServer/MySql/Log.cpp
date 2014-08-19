#include "Log.h"

namespace MySql
{

Log::Log()
{
}

Log::~Log()
{
}

void Log::Info(const std::string& info_str)
{
	time_t t = time(nullptr);
	struct tm tp;
	localtime_s(&tp, &t);
	fprintf(stdout, "[SQL INFO] %d-%02d-%02d %02d:%02d:%02d\n%s\n",
		tp.tm_year + 1900, tp.tm_mon + 1, tp.tm_mday,
		tp.tm_hour, tp.tm_min, tp.tm_sec,
		info_str.c_str());
}

void Log::Error(const std::string& str)
{
	time_t t = time(nullptr);
	struct tm tp;
	localtime_s(&tp, &t);
	fprintf(stderr, "[SQL ERROR] %d-%02d-%02d %02d:%02d:%02d :: %s\n",
		tp.tm_year + 1900, tp.tm_mon + 1, tp.tm_mday,
		tp.tm_hour, tp.tm_min, tp.tm_sec,
		str.c_str());
}

void Log::DbErr(MYSQL* mysql, const std::string& query_str)
{
	time_t t = time(nullptr);
	struct tm tp;
	localtime_s(&tp, &t);
	fprintf(stderr, "[SQL ERR]\n%d-%02d-%02d %02d:%02d:%02d\n%s\n%d - %s\n",
		tp.tm_year + 1900, tp.tm_mon + 1, tp.tm_mday, tp.tm_hour, tp.tm_min,
		tp.tm_sec, query_str.c_str(), mysql_errno(mysql), mysql_error(mysql));
}

} // namespace MySql
