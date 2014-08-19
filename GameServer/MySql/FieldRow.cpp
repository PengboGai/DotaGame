#include "FieldRow.h"
#include "DataField.h"

namespace MySql
{

FieldRow::FieldRow()
{
}

FieldRow::FieldRow(MYSQL_FIELD* field, uint32_t cols)
{
	if (field) {
		for (uint32_t i = 0; i < cols; ++i) {
			AddField(field[i]);
		}
	}
}

FieldRow::~FieldRow()
{
	m_header.clear();
}

std::shared_ptr<DataField> FieldRow::GetField(uint32_t h_index)
{
	if (h_index >= m_header.size()) {
		return nullptr;
	}
	return m_header[h_index];
}

std::shared_ptr<DataField> FieldRow::GetField(const std::string& h_title)
{
	for (auto& item : m_header) {
		if (item->GetName() == h_title) {
			return item;
		}
	}
	return nullptr;
}

int32_t FieldRow::GetIndex(const std::string& h_title)
{
	for (uint32_t i = 0; i < m_header.size(); ++i) {
		if (m_header[i]->GetName() == h_title) {
			return i;
		}
	}
	return -1;
}

std::string FieldRow::GetName(uint32_t h_index)
{
	std::shared_ptr<DataField> header = GetField(h_index);
	if (header) {
		return header->GetName();
	}
	return "";
}

int32_t FieldRow::GetPrimaryKeyIndex()
{
	for (uint32_t i = 0; i < m_header.size(); ++i) {
		if (m_header[i]->IsPrimaryKey()) {
			return (int32_t)i;
		}
	}
	return -1;
}

int32_t FieldRow::GetUniqueKeyIndex()
{
	for (uint32_t i = 0; i < m_header.size(); ++i) {
		if (m_header[i]->IsUniqueKey()) {
			return (int32_t)i;
		}
	}
	return -1;
}

void FieldRow::AddField(const std::shared_ptr<DataField>& item)
{
	if (item && GetField(item->GetName())) {
		return;
	}
	m_header.push_back(item);
}

void FieldRow::AddField(MYSQL_FIELD& field)
{
	if (GetField(field.name) == nullptr) {
		std::shared_ptr<DataField> header(new DataField(field));
		m_header.push_back(header);
	}
}

uint32_t FieldRow::GetCount()
{
	return m_header.size();
}

} // namespace MySql
