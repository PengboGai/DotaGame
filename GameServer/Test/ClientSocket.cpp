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

	SOCKET_MSG* socket_msg = (SOCKET_MSG*)ibuf.GetStart();
	if (socket_msg) {
		if (socket_msg->type == MSG_ACCOUNT_LOGIN_S) {
			SMsgAccountLogin msg;
			msg.setBuffer(ibuf.GetStart(), socket_msg->len);

			if (msg.getResult() == SMsgAccountLogin::LR_FAIL) {
				Debug::Log("=======login failed");
			}
			else if (msg.getResult() == SMsgAccountLogin::LR_SUCCESS) {
				Debug::Log("=======login success");
			}
			else if (msg.getResult() == SMsgAccountLogin::LR_INVALID_USER_OR_PWD) {
				Debug::Log("=======user name or pwd error");
			}
		}
		else if (socket_msg->type == MSG_ACCOUNT_REG_S) {
			SMsgAccountReg msg;
			msg.setBuffer(ibuf.GetStart(), socket_msg->len);

			if (msg.getResult() == SMsgAccountReg::RR_FAIL) {
				Debug::Log("=======reg failed");
			}
			else if (msg.getResult() == SMsgAccountReg::RR_SUCCESS) {
				Debug::Log("=======reg success");
			}
			else if (msg.getResult() == SMsgAccountReg::RR_EXIST_USER) {
				Debug::Log("=======exist user");
			}
			else if (msg.getResult() == SMsgAccountReg::RR_PWD_DIFFERENT) {
				Debug::Log("=======different pwd");
			}
		}
		ibuf.Remove(socket_msg->len);
	}
}

void ClientSocket::OnConnect()
{
	TcpSocket::OnConnect();

	std::string name = "xubinbin";
	std::string pwd = "23285155xbb";
	std::string pwd2 = "23285155xbb";
	std::string ip = "192.168.1.101";

#if 0
	CMsgAccountLogin login;
	login.setUserName(name.c_str(), name.size());
	login.setUserPwd(pwd.c_str(), pwd.size());
	login.setUserIP(ip.c_str(), ip.size());

	char* buf = login.getBuffer(login.getLen());
	SendBuf(buf, login.getLen());
	delete[] buf;
#endif

	CMsgAccountReg reg;
	reg.setUserName(name.c_str(), name.size());
	reg.setUserPwd(pwd.c_str(), pwd.size());
	reg.setUserConfirmPwd(pwd2.c_str(), pwd2.size());
	reg.setUserIP(ip.c_str(), ip.size());

	char* buf = reg.getBuffer(reg.getLen());
	SendBuf(buf, reg.getLen());
	delete[] buf;
}