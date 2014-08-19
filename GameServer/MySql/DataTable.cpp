#include "DataTable.h"
#include "FieldRow.h"
#include "DataField.h"
#include "DataRow.h"
#include "DataItem.h"

namespace MySql
{

DataTable::DataTable()
: m_fieldrow(nullptr)
, m_cur_row(-1)
{
}

DataTable::DataTable(MYSQL_RES* res)
	: m_fieldrow(nullptr)
	, m_cur_row(-1)
{
	if (res) {
		uint32_t cols = mysql_num_fields(res);
		MYSQL_FIELD* field = mysql_fetch_fields(res);
		std::shared_ptr<FieldRow> field_row(new FieldRow(field, cols));
		SetFieldRow(field_row);

		uint64_t rows = mysql_num_rows(res);
		for (uint32_t i = 0; i < rows; ++i) {
			MYSQL_ROW row = mysql_fetch_row(res);
			std::shared_ptr<DataRow> data_row(new DataRow(field_row, row, cols));
			AddRow(data_row);
		}

		if (cols > 0) {
			m_tablename = field[0].org_table;
		}
	}
}

DataTable::~DataTable()
{
	m_rows.clear();
}

const std::string& DataTable::GetTableName()
{
	return m_tablename;
}

DbType DataTable::GetFieldType(uint32_t col_index)
{
	std::shared_ptr<DataField> field = m_fieldrow->GetField(col_index);
	if (field) {
		return field->GetType();
	}
	return DbType::UNKNOWN;
}

DbType DataTable::GetFieldType(const std::string& col_title)
{
	std::shared_ptr<DataField> field = m_fieldrow->GetField(col_title);
	if (field) {
		return field->GetType();
	}
	return DbType::UNKNOWN;
}

std::string DataTable::GetFieldName(uint32_t col_index)
{
	std::shared_ptr<DataField> field = m_fieldrow->GetField(col_index);
	if (field) {
		return field->GetName();
	}
	return "";
}

int32_t DataTable::GetPrimaryKeyColumnIndex()
{
	return m_fieldrow->GetPrimaryKeyIndex();
}

int32_t DataTable::GetUniqueKeyColumnIndex()
{
	return m_fieldrow->GetUniqueKeyIndex();
}

std::shared_ptr<DataItem> DataTable::GetItem(uint32_t col_index)
{
	if (m_cur_row == -1 || (uint32_t)m_cur_row >= m_rows.size()) {
		return nullptr;
	}
	return m_rows[m_cur_row]->GetItem(col_index);
}

std::shared_ptr<DataItem> DataTable::GetItem(const std::string& col_title)
{
	return GetItem(m_fieldrow->GetIndex(col_title));
}

uint32_t DataTable::GetFieldCount()
{
	return m_fieldrow->GetCount();
}

uint32_t DataTable::GetRowCount()
{
	return m_rows.size();
}

bool DataTable::HasRow()
{
	return !m_rows.empty();
}

bool DataTable::Read()
{
	++m_cur_row;
	if ((uint32_t)m_cur_row >= m_rows.size()) {
		return false;
	}
	return true;
}

void DataTable::SetFieldRow(const std::shared_ptr<FieldRow>& field_row)
{
	if (field_row && !m_fieldrow) {
		m_fieldrow = field_row;
	}
}

void DataTable::AddRow(const std::shared_ptr<DataRow>& row)
{
	if (row) {
		for (auto& item : m_rows) {
			if (item.get() == row.get()) {
				return;
			}
		}
		m_rows.push_back(row);
	}
}

void DataTable::RemoveRow(uint32_t row_index)
{
	if (m_cur_row == -1 || (uint32_t)m_cur_row >= m_rows.size()) {
		return;
	}

	auto iter = m_rows.begin();
	for (uint32_t i = 0; iter != m_rows.end(); ++iter, ++i) {
		if (i == row_index) {
			m_rows.erase(iter);
		}
	}

	if (m_cur_row == row_index) {
		m_cur_row = -1;
	}
}

void DataTable::RemoveRow(SELECTOR selector)
{
	auto iter = m_rows.begin();
	for (; iter != m_rows.end(); ++iter) {
		if (selector(*iter)) {
			m_rows.erase(iter);
			break;
		}
	}
}

void DataTable::RemoveRows(SELECTOR selector)
{
	auto iter = m_rows.begin();
	for (; iter != m_rows.end();) {
		if (selector(*iter)) {
			iter = m_rows.erase(iter);
		}
		else {
			++iter;
		}
	}
}

std::shared_ptr<DataRow> DataTable::GetRow(uint32_t row_index)
{
	if (row_index >= m_rows.size()) {
		return nullptr;
	}
	return m_rows[row_index];
}

std::shared_ptr<DataRow> DataTable::GetRowBySel(SELECTOR selector)
{
	auto iter = m_rows.begin();
	for (; iter != m_rows.end(); ++iter) {
		if (selector(*iter)) {
			return *iter;
		}
	}
	return nullptr;
}

const std::vector<std::shared_ptr<DataRow> >& DataTable::GetAllRows()
{
	return m_rows;
}

std::vector<std::shared_ptr<DataRow> > DataTable::GetRowsBySel(SELECTOR selector)
{
	std::vector<std::shared_ptr<DataRow> > ret;
	for (auto& row : m_rows) {
		if (selector(row)) {
			ret.push_back(row);
		}
	}
	return std::move(ret);
}

std::shared_ptr<DataRow> DataTable::CreateNewRow()
{
	std::shared_ptr<DataRow> new_row(new DataRow());
	new_row->SetStatus(DataRow::Status::INSERT);
	for (uint32_t i = 0; i < m_fieldrow->GetCount(); ++i) {
		std::shared_ptr<DataField> field = m_fieldrow->GetField(i);
		std::shared_ptr<DataItem> item(new DataItem(field, "0"));
		new_row->AddItem(item);
	}
	return new_row;
}

} // namespace MySql
