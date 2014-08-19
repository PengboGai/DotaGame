#ifndef _MYSQL_DATA_TABLE_H_
#define _MYSQL_DATA_TABLE_H_

#include "sql_include.h"

namespace MySql
{

class FieldRow;
class DataRow;
class DataItem;
class DataTable
{
	typedef std::function<bool(const std::shared_ptr<DataRow>&)> SELECTOR;

public:
	DataTable();
	DataTable(MYSQL_RES* res);
	~DataTable();

	const std::string& GetTableName();

	DbType GetFieldType(uint32_t col_index);
	DbType GetFieldType(const std::string& col_title);
	std::string GetFieldName(uint32_t col_index);
	int32_t GetPrimaryKeyColumnIndex();
	int32_t GetUniqueKeyColumnIndex();

	std::shared_ptr<DataItem> GetItem(uint32_t col_index);
	std::shared_ptr<DataItem> GetItem(const std::string& col_title);

	uint32_t GetFieldCount();
	uint32_t GetRowCount();
	bool HasRow();
	bool Read();

	void SetFieldRow(const std::shared_ptr<FieldRow>& field_row);

	void AddRow(const std::shared_ptr<DataRow>& row);

	void RemoveRow(uint32_t row_index);
	void RemoveRow(SELECTOR selector);
	void RemoveRows(SELECTOR selector);

	std::shared_ptr<DataRow> GetRow(uint32_t row_index);
	std::shared_ptr<DataRow> GetRowBySel(SELECTOR selector);
	const std::vector<std::shared_ptr<DataRow> >& GetAllRows();
	std::vector<std::shared_ptr<DataRow> > GetRowsBySel(SELECTOR selector);

	std::shared_ptr<DataRow> CreateNewRow();

private:
	std::string m_tablename;
	std::shared_ptr<FieldRow> m_fieldrow;
	std::vector<std::shared_ptr<DataRow> > m_rows;
	int32_t m_cur_row;
};

}; // namespace MySql

#endif // _MYSQL_DATA_TABLE_H_