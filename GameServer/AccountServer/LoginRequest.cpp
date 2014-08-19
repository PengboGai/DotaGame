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
	Application* app = Application::GetInstance();
	m_cmd = app->GetDbConn()->CreateCommand();
}

LoginRequest::LoginRequest(ISocketHandler& h, size_t isize, size_t osize)
: TcpSocket(h, isize, osize)
{
	Application* app = Application::GetInstance();
	m_cmd = app->GetDbConn()->CreateCommand();
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
			CMsgAccountLogin msg;
			msg.setBuffer(ibuf.GetStart(), socket_msg->len);
			
			std::string name = msg.getUserName();
			std::string pwd = msg.getUserPwd();
			std::string ip = msg.getUserIP();
			
			std::string query = StringTool::Format("SELECT * FROM `account` WHERE `user_name`='%s' "
				"AND `user_pwd`='%s' LIMIT 1;", name.c_str(), pwd.c_str());
			m_cmd->SetCommandText(query);
			std::shared_ptr<DataReader> reader = m_cmd->ExecuteReader();
			if (reader && reader->HasRow()) {
				std::shared_ptr<DataTable> table = reader->GetDataTable();
				std::shared_ptr<DataRow> row = table->GetRow(0);
				row->SetStringItem("login_ip", ip);
				row->SetIntItem("login_time", time(nullptr));
				row->Update(m_cmd);
			}
		}
		else if (socket_msg->type == MSG_ACCOUNT_REG_C) {

		}
		ibuf.Remove(socket_msg->len);
	}
}
