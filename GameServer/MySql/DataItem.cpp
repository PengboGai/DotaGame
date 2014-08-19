#include "DataItem.h"
#include "DataField.h"
#include "Convert.h"

using namespace Utilities;

namespace MySql
{

DataItem::DataItem(const std::shared_ptr<DataField>& field)
: m_field(field)
, m_modified(false)
, m_d_data(0.f)
, m_i_data(0)
{
}

DataItem::DataItem(const std::shared_ptr<DataField>& field, const std::string& default_value)
: m_field(field)
, m_modified(false)
, m_d_data(0.f)
, m_i_data(0)
{
	SetData(default_value);
	SetModified(false);
}

DataItem::~DataItem()
{
}

float DataItem::ToFloat() const
{
	return (float)m_d_data;
}

double DataItem::ToDouble() const
{
	return m_d_data;
}

bool DataItem::ToBoolean() const
{
	return !!m_i_data;
}

int32_t DataItem::ToInt32() const
{
	return (int32_t)m_i_data;
}

int64_t DataItem::ToInt64() const
{
	return m_i_data;
}

const char* DataItem::ToChars() const
{
	return m_data.c_str();
}

const std::string& DataItem::ToString() const
{
	return m_data;
}

void DataItem::SetData(const std::string& data)
{
	if (m_data != data) {
		switch (m_field->GetType())
		{
		case DbType::INT16:
		case DbType::INT32:
		case DbType::INT64:
		case DbType::TIMESTAMP:
			m_i_data = Convert::ToInt64(data);
			break;
		case DbType::FLOAT:
		case DbType::DOUBLE:
		case DbType::REAL:
		case DbType::DECIMAL:
			m_d_data = Convert::ToDouble(data);
			break;
		default:
			break;
		}
		m_modified = true;
		m_data = data;
	}
}

void DataItem::SetModified(bool modified)
{
	m_modified = modified;
}

bool DataItem::IsModified()
{
	return m_modified;
}

std::string DataItem::GetFieldName()
{
	return m_field->GetName();
}

const std::shared_ptr<DataField>& DataItem::GetDataField()
{
	return m_field;
}

} // namespace MySql
