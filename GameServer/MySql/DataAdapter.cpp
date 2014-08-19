#include "DataAdapter.h"
#include "DataTable.h"
#include "DataRow.h"
#include "FieldRow.h"
#include "DataItem.h"
#include "Utility.h"
#include "Command.h"
#include "DataReader.h"
#include "DataField.h"

#define UPDATE_QUERY			"UPDATE %s SET %s WHERE %s;"
#define INSERT_QUERY			"INSERT INTO %s VALUES(%s);"
#define DELETE_QUERY			"DELETE FROM %s WHERE %s;"

#define UPDATE_COLUMN_NOSTR		" %s = %s,"
#define UPDATE_COLUMN_STR		" %d = '%s',"

#define WHERE_CLAUSE_NOSTR		"%s = %s"
#define WHERE_CLAUSE_STR		"%s = '%s'"

DataAdapter::DataAdapter(const std::shared_ptr<Command>& cmd)
: m_cmd(cmd)
, m_inited_header(false)
, m_table(new DataTable())
{
}

DataAdapter::~DataAdapter()
{
}

void DataAdapter::AddRows(const std::shared_ptr<DataReader>& reader)
{
	if (reader) {
		std::shared_ptr<DataTable> table = reader->GetDataTable();
		if (table) {
			if (!m_inited_header) {
				m_inited_header = true;
				m_table->SetHeader(table->GetHeader());
			}

			uint32_t row_count = table->GetRowCount();
			for (uint32_t i = 0; i < row_count; ++i) {
				std::shared_ptr<DataRow>& row = table->GetDataRow(i);
				m_table->AddDataRow(row);
			}
		}
	}
}

void DataAdapter::AddRows(const std::vector<std::shared_ptr<DataRow> >& new_rows)
{
	auto iter = new_rows.begin();
	for (; iter != new_rows.end(); ++iter) {
		m_table->AddDataRow(*iter);
	}
}

void DataAdapter::AddRow(const std::shared_ptr<DataRow>& new_row)
{
	m_table->AddDataRow(new_row);
}

void DataAdapter::RemoveRows(int32_t primary_key)
{
	if (!m_table->HasRow()) {
		return;
	}

	int32_t pk = m_table->GetPrimaryKeyIndex();
	if (pk == -1) {
		// ERROR: this table does not have a primery key
		return;
	}

	std::vector<uint32_t> remove_list;
	uint32_t row_count = m_table->GetRowCount();
	for (uint32_t i = 0; i < row_count; ++i) {
		std::shared_ptr<DataRow>& row = m_table->GetDataRow(i);
		if (row->GetItem(pk)->ToInt32() == primary_key) {
			remove_list.push_back(i);
		}
	}

	if (!remove_list.empty()) {
		m_table->RemoveDataRows(remove_list);
		remove_list.clear();
	}
}

int32_t DataAdapter::GetUniqueKeyIndex()
{
	int32_t index = m_table->GetPrimaryKeyIndex();
	if (index == -1) {
		index = m_table->GetUniqueKeyIndex();
	}
	return index;
}

bool DataAdapter::Update()
{
	return true;
}

bool DataAdapter::Insert()
{
	return true;
}

bool DataAdapter::Delete()
{
	return true;
}

std::shared_ptr<DataRow> DataAdapter::CreateNewDataRow()
{
	std::shared_ptr<FieldRow> header = m_table->GetHeader();
	if (header == nullptr) {
		// ERROR: this table doesn't inited structure
		return nullptr;
	}

	std::shared_ptr<DataRow> new_row(new DataRow());
	for (uint32_t i = 0; i < header->GetCount(); ++i) {
		std::shared_ptr<DataField> field = header->GetField(i);
		std::shared_ptr<DataItem> item(new DataItem(field));
		item->SetData("0");
		new_row->AddItem(item);
	}
	new_row->SetStatus(DataRow::Status::NEW);
	return new_row;
}