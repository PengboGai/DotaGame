#include "DataRow.h"
#include "DataItem.h"
#include "FieldRow.h"
#include "DataField.h"
#include "Command.h"
#include "Log.h"
#include "StringTool.h"
#include "Convert.h"

using namespace Utilities;

namespace MySql
{

#define INSERT_QUERY			"INSERT INTO %s(%s) VALUES(%s);"
#define UPDATE_QUERY			"UPDATE %s SET %s WHERE %s;"
#define DELETE_QUERY			"DELETE FROM %s WHERE %s;"

DataRow::DataRow()
: m_status(Status::NORMAL)
{
}

DataRow::DataRow(const std::shared_ptr<FieldRow>& field_row, MYSQL_ROW row, uint32_t cols)
: m_status(Status::NORMAL)
{
	if (row) {
		for (uint32_t i = 0; i < cols; ++i) {
			if (row[i] == nullptr) {
				AddNullItem();
			}
			else {
				std::shared_ptr<DataField> field = field_row->GetField(i);
				std::shared_ptr<DataItem> data_item(new DataItem(field, (char*)row[i]));
				AddItem(data_item);
			}
		}
	}
}

DataRow::~DataRow()
{
	m_row.clear();
}

std::shared_ptr<DataItem> DataRow::GetItem(uint32_t col_index)
{
	if (col_index >= m_row.size()) {
		return nullptr;
	}
	return m_row[col_index];
}

std::shared_ptr<DataItem> DataRow::GetItem(const std::string& field_name)
{
	for (auto& item : m_row) {
		if (item->GetFieldName() == field_name) {
			return item;
		}
	}
	return nullptr;
}

std::shared_ptr<DataItem> DataRow::GetItemBySel(SELECTOR selector)
{
	for (auto& item : m_row) {
		if (selector(item)) {
			return item;
		}
	}
	return nullptr;
}

void DataRow::AddNullItem()
{
	m_row.push_back(nullptr);
}

void DataRow::AddItem(const std::shared_ptr<DataItem>& item)
{
	for (auto& data : m_row) {
		if (data.get() == item.get()) {
			return;
		}
	}
	m_row.push_back(item);
}

void DataRow::SetIntItem(const std::string& title, int64_t data)
{
	SetStringItem(title, Convert::ToString(data));
}

void DataRow::SetDoubleItem(const std::string& title, double data)
{
	SetStringItem(title, Convert::ToString(data));
}

void DataRow::SetStringItem(const std::string& title, const std::string& data)
{
	auto iter = m_row.begin();
	for (; iter != m_row.end(); ++iter) {
		if ((*iter)->GetFieldName() == title) {
			(*iter)->SetData(data);
			break;
		}
	}

	if (m_status == Status::NORMAL) {
		m_status = Status::UPDATE;
	}
}

void DataRow::SetIntItem(uint32_t col_index, int64_t data)
{
	SetStringItem(col_index, Convert::ToString(data));
}

void DataRow::SetDoubleItem(uint32_t col_index, double data)
{
	SetStringItem(col_index, Convert::ToString(data));
}

void DataRow::SetStringItem(uint32_t col_index, const std::string& data)
{
	if (col_index >= m_row.size()) {
		// ERROR: overrange
		return;
	}
	m_row[col_index]->SetData(data);

	if (m_status == Status::NORMAL) {
		m_status = Status::UPDATE;
	}
}

void DataRow::SetStatus(Status status)
{
	m_status = status;
}

DataRow::Status DataRow::GetStatus()
{
	return m_status;
}

bool DataRow::Insert(const std::shared_ptr<Command>& cmd)
{
	if (m_status != Status::INSERT) {
		return false;
	}

	std::string insert_query;
	std::string table_name;
	std::string insert_col;
	std::string insert_value;
	for (uint32_t i = 0; i < m_row.size(); ++i) {
		const std::shared_ptr<DataItem>& data_item = m_row[i];
		const std::shared_ptr<DataField>& data_field = data_item->GetDataField();
		if (data_item->IsModified() && !data_field->IsAutoIncrement()) {
			if (!insert_col.empty()) {
				insert_col += ",";
			}
			insert_col += StringTool::Format("%s.%s", data_field->GetTableName().c_str(), data_field->GetName().c_str());

			if (!insert_value.empty()) {
				insert_value += ",";
			}
			if (data_field->GetType() == DbType::STRING) {
				insert_value += StringTool::Format("'%s'", data_item->ToChars());
			}
			else {
				insert_value += data_item->ToString();
			}
		}

		if (table_name.empty()) {
			table_name = data_field->GetTableName();
		}
	}

	if (table_name.empty() || insert_col.empty() || insert_value.empty()) {
		// ERROR:
		return false;
	}

	insert_query = StringTool::Format(INSERT_QUERY, table_name.c_str(), insert_col.c_str(), insert_value.c_str());
	Log::Info(insert_query);
	cmd->SetCommandText(insert_query);
	if (!cmd->ExecuteNonQuery()) {
		return false;
	}

	uint64_t insert_id = cmd->GetInsertId();
	if (insert_id > 0) {
		int32_t pk = GetPrimaryKeyColumnIndex();
		SetIntItem(pk, insert_id);
	}

	SetStatus(Status::NORMAL);
	ResetDataItemsStatus();

	return true;
}

bool DataRow::Update(const std::shared_ptr<Command>& cmd)
{
	if (m_status != Status::UPDATE) {
		return false;
	}

	std::string update_query;
	std::string table_name;
	std::string set_clause;
	std::string where_clause;
	for (uint32_t i = 0; i < m_row.size(); ++i) {
		const std::shared_ptr<DataItem>& data_item = m_row[i];
		const std::shared_ptr<DataField>& data_field = data_item->GetDataField();
		if (data_item->IsModified() && !data_field->IsPrimaryKey()
			&& !data_field->IsAutoIncrement() && !data_field->IsUniqueKey()) {
			if (!set_clause.empty()) {
				set_clause += ",";
			}
			set_clause += StringTool::Format("%s.%s=", data_field->GetTableName().c_str(), data_field->GetName().c_str());
			if (data_field->GetType() == DbType::STRING) {
				set_clause += StringTool::Format("'%s'", data_item->ToChars());
			}
			else {
				set_clause += data_item->ToString();
			}
		}

		if (table_name.empty()) {
			table_name = data_field->GetTableName();
		}
	}

	int32_t pk = GetPrimaryKeyColumnIndex();
	if (pk == -1 || (uint32_t)pk >= m_row.size()) {
		return false;
	}
	const std::shared_ptr<DataItem>& data_item = m_row[pk];
	const std::shared_ptr<DataField>& data_field = data_item->GetDataField();
	where_clause = StringTool::Format("%s.%s=", data_field->GetTableName().c_str(), data_item->GetFieldName().c_str());
	if (data_field->GetType() == DbType::STRING) {
		where_clause += StringTool::Format("'%s'", data_item->ToChars());
	}
	else {
		where_clause += data_item->ToString();
	}

	if (table_name.empty() || set_clause.empty() || where_clause.empty()) {
		// ERROR:
		return false;
	}

	update_query = StringTool::Format(UPDATE_QUERY, table_name.c_str(), set_clause.c_str(), where_clause.c_str());
	Log::Info(update_query);
	cmd->SetCommandText(update_query);
	if (!cmd->ExecuteNonQuery()) {
		return false;
	}

	SetStatus(Status::NORMAL);
	ResetDataItemsStatus();

	return true;
}

bool DataRow::Delete(const std::shared_ptr<Command>& cmd)
{
	int32_t pk = GetPrimaryKeyColumnIndex();
	if (pk == -1 || (uint32_t)pk >= m_row.size()) {
		return false;
	}
	const std::shared_ptr<DataItem>& data_item = m_row[pk];
	const std::shared_ptr<DataField>& data_field = data_item->GetDataField();
	std::string where_clause = StringTool::Format("%s.%s=", data_field->GetTableName().c_str(), data_item->GetFieldName().c_str());
	if (data_field->GetType() == DbType::STRING) {
		where_clause += StringTool::Format("'%s'", data_item->ToChars());
	}
	else {
		where_clause += data_item->ToString();
	}

	std::string delete_query = StringTool::Format(DELETE_QUERY, data_field->GetTableName().c_str(), where_clause.c_str());
	Log::Info(delete_query);
	cmd->SetCommandText(delete_query);
	if (!cmd->ExecuteNonQuery()) {
		return false;
	}
	return true;
}

int32_t DataRow::GetPrimaryKeyColumnIndex()
{
	for (uint32_t i = 0; i < m_row.size(); ++i) {
		if (m_row[i]->GetDataField()->IsPrimaryKey()) {
			return (int32_t)i;
		}
	}
	// ERROR: this table does not have primary key
	return -1;
}

std::string DataRow::GetPrimaryKeyColumnFieldName()
{
	for (uint32_t i = 0; i < m_row.size(); ++i) {
		if (m_row[i]->GetDataField()->IsPrimaryKey()) {
			return m_row[i]->GetFieldName();
		}
	}
	// ERROR: this table does not have primary key
	return "";
}

void DataRow::ResetDataItemsStatus()
{
	for (uint32_t i = 0; i < m_row.size(); ++i) {
		if (m_row[i]->GetDataField()->IsPrimaryKey()) {
			return m_row[i]->SetModified(false);
		}
	}
}

} // namespace MySql
