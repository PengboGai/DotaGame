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

LoginResponse::LoginResponse(ISocketHandler& h)
: Response(h)
, m_cmd(nullptr)
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
	std::string ip = msg->m_info->ip;

	SMsgAccountLogin send_msg;

	std::string query = StringTool::Format("SELECT * FROM `account` "
		"WHERE `user_name`='%s' AND `user_pwd`='%s' LIMIT 1;", name.c_str(), pwd.c_str());
	m_cmd->SetCommandText(query);
	std::shared_ptr<DataReader> reader = m_cmd->ExecuteReader();
	if (reader && reader->HasRow()) {
		std::shared_ptr<DataTable> table = reader->GetDataTable();
		std::shared_ptr<DataRow> row = table->GetRow(0);
		row->SetStringItem("login_ip", ip);
		row->SetIntItem("login_time", time(nullptr));
		if (row->Update(m_cmd)) {
			send_msg.m_info->result = SMsgAccountLogin::LR_SUCCESS;
		}
		else {
			send_msg.m_info->result = SMsgAccountLogin::LR_FAIL;
		}
	}
	else {
		send_msg.m_info->result = SMsgAccountLogin::LR_INVALID_USER_OR_PWD;
	}

	SendBuf(send_msg.GetBuffer(), send_msg.GetLen());
}

void LoginResponse::RegisterHandle(CMsgAccountReg* msg)
{
	std::string name = msg->m_info->name;
	std::string pwd = msg->m_info->pwd;
	std::string pwd2 = msg->m_info->pwd2;
	std::string ip = msg->m_info->ip;

	SMsgAccountReg send_msg;
	if (pwd != pwd2) {
		send_msg.m_info->result = SMsgAccountReg::RR_PWD_DIFFERENT;
	}
	else {
		std::string query = StringTool::Format("SELECT * FROM `account` "
			"WHERE `user_name`='%s' LIMIT 1;", name.c_str());
		GetCommand()->SetCommandText(query);
		std::shared_ptr<DataReader> reader = GetCommand()->ExecuteReader();
		if (reader) {
			if (reader->HasRow()) {
				send_msg.m_info->result = SMsgAccountReg::RR_EXIST_USER;
			}
			else {
				std::shared_ptr<DataTable> table = reader->GetDataTable();
				std::shared_ptr<DataRow> row = table->CreateNewRow();
				row->SetStringItem("user_name", name);
				row->SetStringItem("user_pwd", pwd);
				row->SetIntItem("create_time", time(nullptr));
				row->SetIntItem("login_time", time(nullptr));
				row->SetStringItem("login_ip", ip);
				if (row->Insert(GetCommand())) {
					send_msg.m_info->result = SMsgAccountReg::RR_SUCCESS;
				}
			}
		}
	}

	SendBuf(send_msg.GetBuffer(), send_msg.GetLen());
}

const std::shared_ptr<Command>& LoginResponse::GetCommand()
{
	if (m_cmd == nullptr) {
		m_cmd = Application::GetInstance()->CreateCommand();
	}
	return m_cmd;
}
