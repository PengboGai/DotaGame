#include "LoginRequest.h"
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

LoginRequest::LoginRequest(ISocketHandler& h)
: TcpSocket(h)
{
	m_cmd = Application::GetInstance()->CreateCommand();
}

LoginRequest::LoginRequest(ISocketHandler& h, size_t isize, size_t osize)
: TcpSocket(h, isize, osize)
{
	m_cmd = Application::GetInstance()->CreateCommand();
}

LoginRequest::~LoginRequest()
{
}

void LoginRequest::OnRead()
{
	TcpSocket::OnRead();

	SOCKET_MSG* socket_msg = (SOCKET_MSG*)ibuf.GetStart();
	if (socket_msg) {
		if (socket_msg->type == MSG_ACCOUNT_LOGIN_C) {
			LoginHandle(socket_msg);
		}
		else if (socket_msg->type == MSG_ACCOUNT_REG_C) {
			RegHandle(socket_msg);
		}
		ibuf.Remove(socket_msg->len);
	}
}

void LoginRequest::LoginHandle(SOCKET_MSG* socket_msg)
{
	CMsgAccountLogin msg;
	msg.setBuffer(ibuf.GetStart(), socket_msg->len);

	std::string name = msg.getUserName();
	std::string pwd = msg.getUserPwd();
	std::string ip = msg.getUserIP();

	SMsgAccountLogin send_msg;

	std::string query = StringTool::Format("SELECT * FROM `account` "
		"WHERE `user_name`='%s' AND `user_pwd`='%s' LIMIT 1;",
		name.c_str(), pwd.c_str());
	m_cmd->SetCommandText(query);
	std::shared_ptr<DataReader> reader = m_cmd->ExecuteReader();
	if (reader && reader->HasRow()) {
		std::shared_ptr<DataTable> table = reader->GetDataTable();
		std::shared_ptr<DataRow> row = table->GetRow(0);
		row->SetStringItem("login_ip", ip);
		row->SetIntItem("login_time", time(nullptr));
		if (row->Update(m_cmd)) {
			send_msg.setResult(SMsgAccountLogin::LR_SUCCESS);
		}
		else {
			send_msg.setResult(SMsgAccountLogin::LR_FAIL);
		}
	}
	else {
		send_msg.setResult(SMsgAccountLogin::LR_INVALID_USER_OR_PWD);
	}

	char* buf = send_msg.getBuffer(send_msg.getLen());
	SendBuf(buf, send_msg.getLen());
	delete[] buf;
}

void LoginRequest::RegHandle(SOCKET_MSG* socket_msg)
{
	CMsgAccountReg msg;
	msg.setBuffer(ibuf.GetStart(), socket_msg->len);

	std::string name = msg.getUserName();
	std::string pwd = msg.getUserPwd();
	std::string pwd2 = msg.getUserConfirmPwd();
	std::string ip = msg.getUserIP();

	SMsgAccountReg send_msg;
	if (pwd != pwd2) {
		send_msg.setResult(SMsgAccountReg::RR_PWD_DIFFERENT);
	}
	else {
		std::string query = StringTool::Format("SELECT * FROM `account` "
			"WHERE `user_name`='%s' LIMIT 1;", name.c_str());
		m_cmd->SetCommandText(query);
		std::shared_ptr<DataReader> reader = m_cmd->ExecuteReader();
		if (reader) {
			if (reader->HasRow()) {
				send_msg.setResult(SMsgAccountReg::RR_EXIST_USER);
			}
			else {
				std::shared_ptr<DataTable> table = reader->GetDataTable();
				std::shared_ptr<DataRow> row = table->CreateNewRow();
				row->SetStringItem("user_name", name);
				row->SetStringItem("user_pwd", pwd);
				row->SetIntItem("create_time", time(nullptr));
				row->SetIntItem("login_time", time(nullptr));
				row->SetStringItem("login_ip", ip);
				if (row->Insert(m_cmd)) {
					send_msg.setResult(SMsgAccountReg::RR_SUCCESS);
				}
			}
		}
	}
	char* buf = send_msg.getBuffer(send_msg.getLen());
	SendBuf(buf, send_msg.getLen());
	delete[] buf;
}
