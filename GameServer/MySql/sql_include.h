#ifndef _MYSQL_INCLUDE_H_
#define _MYSQL_INCLUDE_H_

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <mutex>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <WinSock2.h>
#include <mysql.h>

enum class DbType
{
	UNKNOWN = 0,
	NULLPTR,
	BOOLEAN,
	BINARY,
	REAL,
	BYTE,
	INT16,
	INT32,
	INT64,
	FLOAT,
	DOUBLE,
	DECIMAL,
	STRING,
	DATE,
	TIME,
	DATETIME,
	TIMESTAMP,
};

enum class CommandType
{
	TEXT,
	STORED_PROCEDURE,
};

//typedef char				int8_t;
//typedef short				int16_t;
//typedef int					int32_t;
//typedef long long			int64_t;
//typedef unsigned char		uint8_t;
//typedef unsigned short		uint16_t;
//typedef unsigned int		uint32_t;
//typedef unsigned long long	uint64_t;

#endif // _MYSQL_INCLUDE_H_