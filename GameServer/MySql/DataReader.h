#ifndef _MYSQL_DATA_READER_H_
#define _MYSQL_DATA_READER_H_

#include "sql_include.h"

namespace MySql
{

class DataItem;
class DataRow;
class DataTable;
class DataReader
{
public:
	DataReader();
	~DataReader();

	DbType GetFieldType(uint32_t col_index);
	DbType GetFieldType(const std::string& col_title);
	std::string GetFieldName(uint32_t col_index);

	std::shared_ptr<DataItem> GetItem(uint32_t col_index);
	std::shared_ptr<DataItem> GetItem(const std::string& col_title);

	uint32_t GetFieldCount();
	uint32_t GetRowCount();
	bool HasRow();
	bool Read();
	bool NextResult();

	void AddTable(const std::shared_ptr<DataTable>& new_table);
	void AddTable(MYSQL_RES* res);

	std::string GetTableName();
	std::shared_ptr<DataTable> GetDataTable();

private:
	uint32_t m_cur_table;
	std::vector<std::shared_ptr<DataTable> > m_tables;
};

}; // namespace MySql

#endif // _MYSQL_DATA_READER_H_