#ifndef _MYSQL_FIELD_ROW_H_
#define _MYSQL_FIELD_ROW_H_

#include "sql_include.h"

namespace MySql
{

class DataField;
class FieldRow
{
public:
	FieldRow();
	FieldRow(MYSQL_FIELD* field, uint32_t cols);
	~FieldRow();

	std::shared_ptr<DataField> GetField(uint32_t h_index);
	std::shared_ptr<DataField> GetField(const std::string& h_title);

	int32_t GetIndex(const std::string& h_title);
	std::string GetName(uint32_t h_index);
	int32_t GetPrimaryKeyIndex();
	int32_t GetUniqueKeyIndex();

	void AddField(const std::shared_ptr<DataField>& item);
	void AddField(MYSQL_FIELD& field);

	uint32_t GetCount();

private:
	std::vector<std::shared_ptr<DataField> > m_header;
};

}; // namespace MySql

#endif // _MYSQL_FIELD_ROW_H_