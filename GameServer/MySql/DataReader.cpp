#include "DataReader.h"
#include "DataTable.h"

namespace MySql
{

DataReader::DataReader()
: m_cur_table(0)
{
}

DataReader::~DataReader()
{
	m_tables.size();
}

DbType DataReader::GetFieldType(uint32_t col_index)
{
	if (m_cur_table >= m_tables.size()) {
		return DbType::UNKNOWN;
	}
	return m_tables[m_cur_table]->GetFieldType(col_index);
}

DbType DataReader::GetFieldType(const std::string& col_title)
{
	if (m_cur_table >= m_tables.size()) {
		return DbType::UNKNOWN;
	}
	return m_tables[m_cur_table]->GetFieldType(col_title);
}

std::string DataReader::GetFieldName(uint32_t col_index)
{
	if (m_cur_table >= m_tables.size()) {
		return "";
	}
	return m_tables[m_cur_table]->GetFieldName(col_index);
}

std::shared_ptr<DataItem> DataReader::GetItem(uint32_t col_index)
{
	if (m_cur_table >= m_tables.size()) {
		return nullptr;
	}
	return m_tables[m_cur_table]->GetItem(col_index);
}

std::shared_ptr<DataItem> DataReader::GetItem(const std::string& col_title)
{
	if (m_cur_table >= m_tables.size()) {
		return nullptr;
	}
	return m_tables[m_cur_table]->GetItem(col_title);
}

uint32_t DataReader::GetFieldCount()
{
	if (m_cur_table >= m_tables.size()) {
		return 0;
	}
	return m_tables[m_cur_table]->GetFieldCount();
}

uint32_t DataReader::GetRowCount()
{
	if (m_cur_table >= m_tables.size()) {
		return 0;
	}
	return m_tables[m_cur_table]->GetRowCount();
}

bool DataReader::HasRow()
{
	if (m_cur_table >= m_tables.size()) {
		return false;
	}
	return m_tables[m_cur_table]->HasRow();
}

bool DataReader::Read()
{
	if (m_cur_table >= m_tables.size()) {
		return false;
	}
	return m_tables[m_cur_table]->Read();
}

bool DataReader::NextResult()
{
	++m_cur_table;
	if (m_cur_table >= m_tables.size()) {
		return false;
	}
	return true;
}

void DataReader::AddTable(const std::shared_ptr<DataTable>& new_table)
{
	if (new_table) {
		for (auto& table : m_tables) {
			if (table.get() == new_table.get()) {
				return;
			}
		}
		m_tables.push_back(new_table);
	}
}

void DataReader::AddTable(MYSQL_RES* res)
{
	if (res) {
		std::shared_ptr<DataTable> new_table(new DataTable(res));
		m_tables.push_back(new_table);
	}
}

std::string DataReader::GetTableName()
{
	if (m_cur_table >= m_tables.size()) {
		return "";
	}
	return m_tables[m_cur_table]->GetTableName();
}

std::shared_ptr<DataTable> DataReader::GetDataTable()
{
	if (m_cur_table >= m_tables.size()) {
		return false;
	}
	return m_tables[m_cur_table];
}

} // namespace MySql
