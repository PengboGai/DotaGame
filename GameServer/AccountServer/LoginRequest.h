#ifndef _LOGIN_HANDLER_H_
#define _LOGIN_HANDLER_H_

#include <memory>
#include "TcpSocket.h"
#include "Command.h"

using namespace MySql;

class LoginRequest : public TcpSocket
{
public:
	LoginRequest(ISocketHandler& h);
	LoginRequest(ISocketHandler& h, size_t isize, size_t osize);
	~LoginRequest();

protected:
	virtual void OnRead() override;

private:


private:
	std::shared_ptr<Command> m_cmd;
};

#endif // _LOGIN_HANDLER_H_