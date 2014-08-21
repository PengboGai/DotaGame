#include "LoginResponse.h"
#include "MsgType.h"
#include "AccountMsg.h"
#include "Application.h"
#include "Connection.h"
#include "Command.h"
#include "DataReader.h"
#include "DataTable.h"
#include "DataRow.h"
#include "Debug.h"
#include "StringTool.h"

using namespace Utilities;

// 一个包所允许存储的最大分服数
const static int MAX_SERVER_SIZE = 20;

LoginResponse::LoginResponse(ISocketHandler& h)
: Response(h)
, m_cmd(nullptr)
, m_server_table(nullptr)
{
}

LoginResponse::~LoginResponse()
{
}

void LoginResponse::OnMessage(const char* msg)
{
	MSG_HEAD* head = (MSG_HEAD*)msg;
	switch (head->type)
	{
	case MSG_ACCOUNT_LOGIN_C:
		{
			CMsgAccountLogin data;
			data.SetBuffer(msg, head->len);
			LoginHandle(&data);
		}
		break;
	case MSG_ACCOUNT_REG_C:
		{
			CMsgAccountReg data;
			data.SetBuffer(msg, head->len);
			RegisterHandle(&data);
		}
		break;
	default:
		break;
	}
}

void LoginResponse::LoginHandle(CMsgAccountLogin* msg)
{
	std::string name = msg->m_info->name;
	std::string pwd = msg->m_info->pwd;

	unsigned char result = 0;
	unsigned long long userid = 0;
	std::string query = StringTool::Format("SELECT * FROM `account` "
		"WHERE `user_name`='%s' AND `user_pwd`='%s' LIMIT 1;", name.c_str(), pwd.c_str());
	GetCommand()->SetCommandText(query);
	std::shared_ptr<DataReader> reader = GetCommand()->ExecuteReader();
	if (reader && reader->HasRow()) {
		std::shared_ptr<DataTable> table = reader->GetDataTable();
		std::shared_ptr<DataRow> row = table->GetRow(0);
		row->SetStringItem("login_ip", msg->m_info->ip);
		row->SetIntItem("login_time", time(nullptr));
		if (row->Update(GetCommand())) {
			result = SMsgAccountLogin::LR_SUCCESS;
			userid = row->GetIntItem("id");
		}
		else {
			result = SMsgAccountLogin::LR_FAIL;
		}
	}
	else {
		result = SMsgAccountLogin::LR_INVALID_USER_OR_PWD;
	}

	SMsgAccountLogin send_msg;
	send_msg.m_info->result = result;
	send_msg.m_info->userid = userid;
	SendBuf(send_msg.GetBuffer(), send_msg.GetLen());

	if (result == SMsgAccountLogin::LR_SUCCESS) {
		ServerList();
	}
}

void LoginResponse::RegisterHandle(CMsgAccountReg* msg)
{
	std::string name = msg->m_info->name;
	std::string pwd = msg->m_info->pwd;
	std::string pwd2 = msg->m_info->pwd2;

	unsigned char result = 0;
	if (pwd != pwd2) {
		result = SMsgAccountReg::RR_PWD_DIFFERENT;
	}
	else {
		std::string query = StringTool::Format("SELECT * FROM `account` "
			"WHERE `user_name`='%s' LIMIT 1;", name.c_str());
		GetCommand()->SetCommandText(query);
		std::shared_ptr<DataReader> reader = GetCommand()->ExecuteReader();
		if (reader) {
			if (reader->HasRow()) {
				result = SMsgAccountReg::RR_EXIST_USER;
			}
			else {
				std::shared_ptr<DataTable> table = reader->GetDataTable();
				std::shared_ptr<DataRow> row = table->CreateNewRow();
				row->SetStringItem("user_name", name);
				row->SetStringItem("user_pwd", pwd);
				row->SetIntItem("create_time", time(nullptr));
				row->SetIntItem("login_time", time(nullptr));
				row->SetStringItem("login_ip", msg->m_info->ip);
				if (row->Insert(GetCommand())) {
					result = SMsgAccountReg::RR_SUCCESS;
				}
			}
		}
	}

	SMsgAccountReg send_msg;
	send_msg.m_info->result = result;
	SendBuf(send_msg.GetBuffer(), send_msg.GetLen());
}

void LoginResponse::ServerList()
{
	if (m_server_table == nullptr) {
		GetCommand()->SetCommandText("SELECT * FROM `server`;");
		std::shared_ptr<DataReader> reader = GetCommand()->ExecuteReader();
		if (reader) {
			m_server_table = reader->GetDataTable();
		}
	}

	std::shared_ptr<SMsgServerList> server_list(new SMsgServerList());
	unsigned int row_count = m_server_table->GetRowCount();
	for (unsigned int i = 0; i < row_count; ++i) {
		std::shared_ptr<DataRow> row = m_server_table->GetRow(i);
		std::string name = row->GetStringItem("name");
		std::string ip = row->GetStringItem("ip");
		unsigned short port = (unsigned short)row->GetIntItem("port");

		char server_name[20] = { 0 };
		memcpy(server_name, name.c_str(), sizeof(server_name));
		char server_ip[16] = { 0 };
		memcpy(server_ip, ip.c_str(), sizeof(server_ip));

		if (server_list->m_info->count >= MAX_SERVER_SIZE) {
			server_list->m_info->end = 1;
			SendBuf(server_list->GetBuffer(), server_list->GetLen());
			server_list.reset(new SMsgServerList());
		}
		server_list->AddServer(server_name, SMsgServerList::SS_GOOD, server_ip, port);
	}
	if (server_list->m_info->count > 0) {
		server_list->m_info->end = 1;
		SendBuf(server_list->GetBuffer(), server_list->GetLen());
	}
}

const std::shared_ptr<Command>& LoginResponse::GetCommand()
{
	if (m_cmd == nullptr) {
		m_cmd = Application::GetInstance()->CreateCommand();
	}
	return m_cmd;
}
