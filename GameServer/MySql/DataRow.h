#ifndef _MYSQL_DATA_ROW_H_
#define _MYSQL_DATA_ROW_H_

#include "sql_include.h"

namespace MySql
{

class Command;
class DataItem;
class FieldRow;
class DataRow
{
	typedef std::function<bool(const std::shared_ptr<DataItem>&)> SELECTOR;

public:
	enum class Status
	{
		NORMAL,
		INSERT,
		DELETED,
		UPDATE,
	};

public:
	DataRow();
	DataRow(const std::shared_ptr<FieldRow>& field_row, MYSQL_ROW row, uint32_t cols);
	~DataRow();

	void AddNullItem();
	void AddItem(const std::shared_ptr<DataItem>& item);

	std::shared_ptr<DataItem> GetItem(uint32_t col_index);
	std::shared_ptr<DataItem> GetItem(const std::string& field_name);
	std::shared_ptr<DataItem> GetItemBySel(SELECTOR selector);

	int64_t GetIntItem(uint32_t col_index);
	int64_t GetIntItem(const std::string& title);

	double GetDoubleItem(uint32_t col_index);
	double GetDoubleItem(const std::string& title);

	std::string GetStringItem(uint32_t col_index);
	std::string GetStringItem(const std::string& title);

	void SetIntItem(const std::string& title, int64_t data);
	void SetIntItem(uint32_t col_index, int64_t data);

	void SetDoubleItem(const std::string& title, double data);
	void SetDoubleItem(uint32_t col_index, double data);

	void SetStringItem(const std::string& title, const std::string& data);
	void SetStringItem(uint32_t col_index, const std::string& data);

	void SetStatus(Status status);
	Status GetStatus();

	bool Insert(const std::shared_ptr<Command>& cmd);
	bool Update(const std::shared_ptr<Command>& cmd);
	bool Delete(const std::shared_ptr<Command>& cmd);

private:
	int32_t GetPrimaryKeyColumnIndex();
	std::string GetPrimaryKeyColumnFieldName();
	void ResetDataItemsStatus();

private:
	Status m_status;
	std::vector<std::shared_ptr<DataItem> > m_row;
};

}; // namespace MySql

#endif // _MYSQL_DATA_ROW_H_