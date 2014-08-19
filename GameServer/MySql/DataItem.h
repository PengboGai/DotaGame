#ifndef _MYSQL_DATA_ITEM_H_
#define _MYSQL_DATA_ITEM_H_

#include "sql_include.h"

namespace MySql
{

class DataField;
class DataItem
{
public:
	DataItem(const std::shared_ptr<DataField>& field);
	DataItem(const std::shared_ptr<DataField>& field, const std::string& default_value);
	~DataItem();

	float ToFloat() const;
	double ToDouble() const;
	bool ToBoolean() const;
	int32_t ToInt32() const;
	int64_t ToInt64() const;
	const char* ToChars() const;
	const std::string& ToString() const;

	void SetData(const std::string& data);
	void SetModified(bool modified);
	bool IsModified();

	std::string GetFieldName();
	const std::shared_ptr<DataField>& GetDataField();

private:
	union {
		int64_t m_i_data;
		double m_d_data;
	};

	std::shared_ptr<DataField> m_field;
	std::string m_data;
	bool m_modified;
};

}; // namespace MySql

#endif // _MYSQL_DATA_ITEM_H_