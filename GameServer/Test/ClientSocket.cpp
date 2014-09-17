#include "ClientSocket.h"
#include "Msg/AccountMsg.h"
#include "Msg/MsgType.h"
#include "Debug.h"

using namespace Utilities;

ClientSocket::ClientSocket(ISocketHandler& handler)
: TcpSocket(handler)
{
}

void ClientSocket::OnRead()
{
	TcpSocket::OnRead();

	MSG_HEAD* socket_msg = (MSG_HEAD*)ibuf.GetStart();
	if (socket_msg) {
		if (socket_msg->type == MSG_ACCOUNT_LOGIN_S) {
			SMsgAccountLogin msg;
			msg.SetBuffer(ibuf.GetStart(), socket_msg->len);

			if (msg.m_info->result == SMsgAccountLogin::LR_FAIL) {
				Debug::Log("=======login failed");
			}
			else if (msg.m_info->result == SMsgAccountLogin::LR_SUCCESS) {
				Debug::Log("=======login success");
			}
			else if (msg.m_info->result == SMsgAccountLogin::LR_INVALID_USER_OR_PWD) {
				Debug::Log("=======user name or pwd error");
			}
		}
		else if (socket_msg->type == MSG_ACCOUNT_REG_S) {
			SMsgAccountReg msg;
			msg.SetBuffer(ibuf.GetStart(), socket_msg->len);

			if (msg.m_info->result == SMsgAccountReg::RR_FAIL) {
				Debug::Log("=======reg failed");
			}
			else if (msg.m_info->result == SMsgAccountReg::RR_SUCCESS) {
				Debug::Log("=======reg success");
			}
			else if (msg.m_info->result == SMsgAccountReg::RR_EXIST_USER) {
				Debug::Log("=======exist user");
			}
			else if (msg.m_info->result == SMsgAccountReg::RR_PWD_DIFFERENT) {
				Debug::Log("=======different pwd");
			}
		}
		else if (socket_msg->type == MSG_SERVER_LIST_S) {
			SMsgServerList msg;
			msg.SetBuffer(ibuf.GetStart(), socket_msg->len);
			for (unsigned short i = 0; i < msg.m_info->count; ++i) {
				Debug::Log("[SERVER_NAME]: %s, [SERVER_IP]:%s, [SERVER_PORT]: %d, [SERVER_STATUS]: %d", 
					msg.m_info->servers[i].name, msg.m_info->servers[i].ip, 
					msg.m_info->servers[i].port, msg.m_info->servers[i].status);
			}
		}
		ibuf.Remove(socket_msg->len);
	}
}

void ClientSocket::OnConnect()
{
	TcpSocket::OnConnect();

	std::string name = "www";
	std::string pwd = "123456";
	std::string pwd2 = "123456";
	std::string ip = "192.168.1.101";

#if 0
	CMsgAccountLogin login;
	memcpy(login.m_info->name, name.c_str(), name.size());
	memcpy(login.m_info->pwd, pwd.c_str(), pwd.size());
	memcpy(login.m_info->ip, ip.c_str(), ip.size());

	SendBuf(login.GetBuffer(), login.GetLen());
#endif

#if 1
	CMsgAccountReg reg;
	memcpy(reg.m_info->name, name.c_str(), name.size());
	memcpy(reg.m_info->pwd, pwd.c_str(), pwd.size());
	memcpy(reg.m_info->pwd2, pwd2.c_str(), pwd2.size());
	memcpy(reg.m_info->ip, ip.c_str(), ip.size());

	SendBuf(reg.GetBuffer(), reg.GetLen());
#endif
}