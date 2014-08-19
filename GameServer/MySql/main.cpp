#include <iostream>
#include "Connection.h"
#include "Command.h"
#include "DataReader.h"
#include "DataRow.h"
#include "FieldRow.h"
#include "DataTable.h"
#include "DataItem.h"

using namespace MySql;

int main()
{
	//==========================================================================
	// Note:
	// 1) Every table must set primary key, and the primary key auto increment.
	// 2) The column of every table must set DEFAULT VALUE.
	//==========================================================================
	std::string create_sql = "DROP DATABASE IF EXISTS test2;"
		" CREATE DATABASE test2  ; "
		" USE test2  ;"
		"CREATE TABLE DEMO1(id INT, name VARCHAR(20), PRIMARY KEY(id));"
		"INSERT INTO DEMO1(id, name) VALUES(1, 'aaa'),"
		"(2, '111'),"
		"(3, 'ccc'),"
		"(4, 'ddd'),"
		"(5, 'eee'),"
		"(6, 'fff'),"
		"(7, 'ggg'),"
		"(8, 'hhh'),"
		"(9, 'iii');"
		"CREATE TABLE DEMO2(id INT, zh_ch VARCHAR(20), PRIMARY KEY(id));"
		"INSERT INTO DEMO2(id, zh_ch) VALUES(1, 'china'),"
		"(2, null),"
		"(3, 'fujian'),"
		"(4, 'shanghai'),"
		"(5, 'guangzhou'),"
		"(6, 'shenzhen');"
		"CREATE TABLE DEMO3(id INT auto_increment, name VARCHAR(20) default '', count INT default 0, PRIMARY KEY(id));"
		"INSERT INTO DEMO3(name, count) VALUES('pingguo', 20),"
		"('liulian', 10),"
		"('xiangjiao', 5),"
		"('liulian', 7);";

	std::string query1 = "USE test2; SELECT * FROM DEMO1; SELECT * FROM DEMO2;";
	std::string query2 = "USE test2; SELECT * FROM DEMO3;";
	std::string query3 = "USE test2; SELECT AVG(DEMO3.COUNT) AS v FROM DEMO3;";

	std::shared_ptr<Connection> conn(new Connection("HostName=localhost;DataBase=mysql;Port=3306;User=root;Pwd=root"));
	if (!conn->Open()) {
		std::cout << "connect failed, invalid user or pwd." << std::endl;
		getchar();
		return 0;
	}
	
	if (conn->IsConnected()) {
		std::cout << "connect to mysql" << std::endl;
	}

	std::shared_ptr<Command> cmd = conn->CreateCommand();

	// create database and table
	cmd->SetCommandText(create_sql);
	cmd->ExecuteNonQuery();

	cmd->SetCommandText(query1);
	std::shared_ptr<DataReader> reader = cmd->ExecuteReader();
	if (reader) {
		do {
			if (reader->HasRow()) {

				std::cout << "TableName: " << reader->GetTableName().c_str() << std::endl;
				std::cout << "FieldCount: " << reader->GetFieldCount() << std::endl;
				std::cout << "RowCount: " << reader->GetRowCount() << std::endl;

				// header
				for (uint32_t i = 0; i < reader->GetFieldCount(); ++i) {
					std::cout << reader->GetFieldName(i).c_str() << " ";
				}
				std::cout << std::endl;

				// data row
				while (reader->Read()) {
					for (uint32_t i = 0; i < reader->GetFieldCount(); ++i) {
						std::shared_ptr<DataItem> col = reader->GetItem(i);
						if (col) {
							std::cout << col->ToChars() << " ";
						}
						else {
							std::cout << "NULL" << " ";
						}
					}
					std::cout << std::endl;
				}

				std::cout << "==============================================================" << std::endl;
			}
		} while (reader->NextResult());
	}

	cmd->SetCommandText(query2);
	reader = cmd->ExecuteReader();
	int totalCount = 0;
	if (reader && reader->HasRow()) {
		while (reader->Read()) {
			totalCount += reader->GetItem("count")->ToInt32();
		}
	}
	std::cout << "TOTAL COUNT: " << totalCount << std::endl;

	cmd->SetCommandText(query3);
	std::shared_ptr<DataItem> ret = cmd->ExecuteScalar();
	if (ret) {
		std::cout << "AVG COUNT: " << ret->ToFloat() << std::endl;
	}

	//=============================DATA TABLE OPERATE=============================//
	std::string query4 = "USE test2; SELECT * FROM DEMO3;";
	cmd->SetCommandText(query4);
	reader = cmd->ExecuteReader();
	if (reader) {
		std::shared_ptr<DataTable> demo3 = reader->GetDataTable();

#if 1
		// create new data row
		std::shared_ptr<DataRow> new_row = demo3->CreateNewRow();
		new_row->SetStringItem("name", "game_server333");
		//new_row->SetIntItem("count", 999);
		if (new_row->Insert(cmd)) {
			demo3->AddRow(new_row);
		}
#endif

#if 0
		// update data row value
		std::shared_ptr<DataRow> update_row = demo3->GetRowBySel([](const std::shared_ptr<DataRow> row)->bool {
			std::shared_ptr<DataItem> item = row->GetItem("name");
			if (item && item->ToString() == "game_server") {
				return true;
			}
			return false;
		});
		if (update_row) {
			update_row->SetIntItem("count", 222);
			update_row->Update(cmd);
		}
#endif

#if 0
		// delete data row from table
		std::shared_ptr<DataRow> delete_row = demo3->GetRowBySel([](const std::shared_ptr<DataRow> row)->bool {
			std::shared_ptr<DataItem> item = row->GetItem("id");
			if (item && item->ToInt32() == 9) {
				return true;
			}
			return false;
		});
		if (delete_row) {
			delete_row->Delete(cmd);
		}
#endif
	}

	conn->Close();

	getchar();

	return 0;
}