#include "Command.h"
#include "DataReader.h"
#include "Connection.h"
#include "DataItem.h"
#include "DataField.h"
#include "Log.h"
#include "StringTool.h"

using namespace Utilities;

namespace MySql
{

Command::Command(std::shared_ptr<Connection>& conn)
: m_conn(conn)
, m_type(CommandType::TEXT)
{
}

Command::Command(std::shared_ptr<Connection>& conn, const std::string& text)
: m_conn(conn)
, m_text(text)
, m_type(CommandType::TEXT)
{
}

Command::~Command()
{
}

void Command::SetCommandText(const std::string& text)
{
	m_text = text;
}

void Command::SetCommandType(CommandType type)
{
	m_type = type;
}

std::shared_ptr<Connection>& Command::getConnection()
{
	return m_conn;
}

uint64_t Command::ExecuteNonQuery()
{
	uint64_t affected_rows = 0;
	std::vector<std::string> multi_query = SplitMultiQuery();
	for (auto& query : multi_query) {
		if (mysql_query(&m_conn->m_mysql, query.c_str()) != 0) {
			Log::DbErr(&m_conn->m_mysql, query);
			return affected_rows;
		}

		affected_rows = mysql_affected_rows(&m_conn->m_mysql);
		do {
			MYSQL_RES* res = mysql_store_result(&m_conn->m_mysql);
			mysql_free_result(res);
		} while (!mysql_next_result(&m_conn->m_mysql));
	}
	return affected_rows;
}

std::shared_ptr<DataReader> Command::ExecuteReader()
{
	std::shared_ptr<DataReader> reader(new DataReader());
	std::vector<std::string> multi_query = SplitMultiQuery();
	for (auto& query : multi_query) {
		if (mysql_query(&m_conn->m_mysql, query.c_str()) != 0) {
			Log::DbErr(&m_conn->m_mysql, query);
			return nullptr;
		}

		do {
			MYSQL_RES* res = mysql_store_result(&m_conn->m_mysql);
			if (res) {
				reader->AddTable(res);
				mysql_free_result(res);
			}
		} while (!mysql_next_result(&m_conn->m_mysql));
	}
	return reader;
}

std::shared_ptr<DataItem> Command::ExecuteScalar()
{
	std::shared_ptr<DataItem> ret = nullptr;
	std::vector<std::string> multi_query = SplitMultiQuery();
	for (auto& query : multi_query) {
		if (mysql_query(&m_conn->m_mysql, query.c_str()) != 0) {
			Log::DbErr(&m_conn->m_mysql, query);
			return nullptr;
		}

		MYSQL_RES* res = mysql_store_result(&m_conn->m_mysql);
		if (res) {
			uint32_t cols = mysql_num_fields(res);
			MYSQL_FIELD* field = mysql_fetch_fields(res);
			if (cols > 0 && field) {
				std::shared_ptr<DataField> data_field(new DataField(field[0]));

				MYSQL_ROW row = mysql_fetch_row(res);
				if (row && mysql_num_rows(res) > 0) {
					if (row[0]) {
						ret = std::shared_ptr<DataItem>(new DataItem(data_field));
						ret->SetData((char*)row[0]);
					}
				}
				mysql_free_result(res);

				do {
					MYSQL_RES* res = mysql_store_result(&m_conn->m_mysql);
					mysql_free_result(res);
				} while (!mysql_next_result(&m_conn->m_mysql));
			}
		}
	}
	return ret;
}

uint64_t Command::GetInsertId()
{
	if (!m_conn->IsConnected()) {
		// ERROR:
		return 0;
	}
	return mysql_insert_id(&m_conn->m_mysql);
}

std::vector<std::string> Command::SplitMultiQuery()
{
	std::vector<std::string> multi_query = StringTool::Split(m_text, ";");
	auto iter = multi_query.begin();
	for (; iter != multi_query.end();) {
		std::string query = StringTool::Trim(*iter);
		if (query.empty()) {
			iter = multi_query.erase(iter);
			continue;
		}
		query += ";";
		++iter;
	}
	return std::move(multi_query);
}

} // namespace MySql
