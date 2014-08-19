#ifndef _MYSQL_DATA_FIELD_H_
#define _MYSQL_DATA_FIELD_H_

#include "sql_include.h"

namespace MySql
{

class DataField
{
public:
	DataField();
	DataField(MYSQL_FIELD& field);
	~DataField();

	const std::string& GetTableName();

	const std::string& GetName();
	DbType GetType();
	uint32_t GetFlags();

	void SetName(const std::string& name);
	void SetType(DbType type);
	void SetFlags(uint32_t flags);

	bool IsNotNull();
	bool IsPrimaryKey();
	bool IsUniqueKey();
	bool IsAutoIncrement();

private:
	DbType GetDbType(enum_field_types type);

private:
	std::string m_name;
	std::string m_table_name;
	DbType m_type;
	uint32_t m_flags;
};

}; // namespace MySql

#endif // _MYSQL_DATA_FIELD_H_