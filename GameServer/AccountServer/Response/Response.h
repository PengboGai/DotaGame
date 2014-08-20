#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "TcpSocket.h"

class Response : public TcpSocket
{
public:
	Response(ISocketHandler& h);
	Response(ISocketHandler& h, size_t isize, size_t osize);
	~Response();

protected:
	virtual void OnRead() override;
	virtual void OnMessage(const char* msg);
};

#endif // _RESPONSE_H_