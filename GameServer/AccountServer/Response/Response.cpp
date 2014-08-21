#include "Response.h"
#include "BaseMsg.h"

Response::Response(ISocketHandler& h)
: TcpSocket(h)
{
}

Response::Response(ISocketHandler& h, size_t isize, size_t osize)
: TcpSocket(h, isize, osize)
{
}

Response::~Response()
{
}

void Response::OnRead()
{
    TcpSocket::OnRead();

    const char* buf = ibuf.GetStart();
    if (buf) {
        OnMessage(buf);
        ibuf.Remove(((MSG_HEAD*)buf)->len);
    }
}

void Response::OnMessage(const char* msg)
{
}
