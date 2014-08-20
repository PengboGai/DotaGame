#ifndef _LOGIN_HANDLER_H_
#define _LOGIN_HANDLER_H_

#include "Response.h"
#include "Command.h"
#include "DataTable.h"

using namespace MySql;

class CMsgAccountLogin;
class CMsgAccountReg;
class LoginResponse : public Response
{
public:
	LoginResponse(ISocketHandler& h);
	~LoginResponse();

protected:
	virtual void OnMessage(const char* msg) override;

private:
	void LoginHandle(CMsgAccountLogin* msg);
	void RegisterHandle(CMsgAccountReg* msg);
	void ServerList();

	const std::shared_ptr<Command>& GetCommand();

private:
	std::shared_ptr<Command> m_cmd;
	std::shared_ptr<DataTable> m_server_table;
};

#endif // _LOGIN_HANDLER_H_