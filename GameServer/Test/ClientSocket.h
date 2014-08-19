#include <TcpSocket.h>
#include <SocketHandler.h>

class ClientSocket : public TcpSocket
{
public:
	ClientSocket(ISocketHandler& handler);

protected:
	virtual void OnRead();
	virtual void OnConnect();
};