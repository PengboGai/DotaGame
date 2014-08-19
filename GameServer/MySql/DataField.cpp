#include "DataField.h"

namespace MySql
{

DataField::DataField()
: m_type(DbType::UNKNOWN)
, m_flags(0)
{
}

DataField::DataField(MYSQL_FIELD& field)
: m_name(field.name)
, m_flags(field.flags)
, m_table_name(field.org_table)
, m_type(GetDbType(field.type))
{
}

DataField::~DataField()
{
}

const std::string& DataField::GetTableName()
{
	return m_table_name;
}

const std::string& DataField::GetName()
{
	return m_name;
}

DbType DataField::GetType()
{
	return m_type;
}

uint32_t DataField::GetFlags()
{
	return m_flags;
}

void DataField::SetName(const std::string& name)
{
	m_name = name;
}

void DataField::SetType(DbType type)
{
	m_type = type;
}

void DataField::SetFlags(uint32_t flags)
{
	m_flags = flags;
}

bool DataField::IsNotNull()
{
	return m_flags & NOT_NULL_FLAG;
}

bool DataField::IsPrimaryKey()
{
	return !!(m_flags & PRI_KEY_FLAG);
}

bool DataField::IsUniqueKey()
{
	return !!(m_flags & UNIQUE_KEY_FLAG);
}

bool DataField::IsAutoIncrement()
{
	return !!(m_flags & AUTO_INCREMENT_FLAG);
}

DbType DataField::GetDbType(enum_field_types type)
{
	DbType ret = DbType::UNKNOWN;
	switch (type)
	{
	case MYSQL_TYPE_DECIMAL:
	case MYSQL_TYPE_NEWDECIMAL:
		ret = DbType::DECIMAL;
		break;
	case MYSQL_TYPE_TINY:
		ret = DbType::BYTE;
		break;
	case MYSQL_TYPE_SHORT:
		ret = DbType::INT16;
		break;
	case MYSQL_TYPE_INT24:
	case MYSQL_TYPE_LONG:
		ret = DbType::INT32;
		break;
	case MYSQL_TYPE_FLOAT:
		ret = DbType::FLOAT;
		break;
	case MYSQL_TYPE_DOUBLE:
		ret = DbType::DOUBLE;
		break;
	case MYSQL_TYPE_NULL:
		break;
	case MYSQL_TYPE_TIMESTAMP:
		ret = DbType::TIMESTAMP;
		break;
	case MYSQL_TYPE_LONGLONG:
		ret = DbType::INT64;
		break;
	case MYSQL_TYPE_DATE:
		break;
	case MYSQL_TYPE_TIME:
		break;
	case MYSQL_TYPE_DATETIME:
		break;
	case MYSQL_TYPE_YEAR:
		break;
	case MYSQL_TYPE_NEWDATE:
		break;
	case MYSQL_TYPE_BIT:
		ret = DbType::BOOLEAN;
		break;
	case MYSQL_TYPE_ENUM:
		break;
	case MYSQL_TYPE_SET:
		break;
	case MYSQL_TYPE_TINY_BLOB:
		break;
	case MYSQL_TYPE_MEDIUM_BLOB:
		break;
	case MYSQL_TYPE_LONG_BLOB:
		break;
	case MYSQL_TYPE_BLOB:
		break;
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_VARCHAR:
	case MYSQL_TYPE_STRING:
		ret = DbType::STRING;
		break;
	case MYSQL_TYPE_GEOMETRY:
		break;
	default:
		break;
	}
	return ret;
}

} // namespace MySql
