#include <iostream>
#include <TcpSocket.h>
#include <SocketHandler.h>
#include <ListenSocket.h>

class DisplaySocket : public TcpSocket
{
public:
	DisplaySocket(ISocketHandler& handler);

protected:
	void OnDisconnect();
	void OnRead();
	void OnAccept();
	void OnRawData(const char *buf, size_t len);
};

DisplaySocket::DisplaySocket(ISocketHandler& handler)
: TcpSocket(handler)
{
}

void DisplaySocket::OnDisconnect()
{
	TcpSocket::OnDisconnect();
	std::cout << "on disconnect" << std::endl;
}

void DisplaySocket::OnRead()
{
	TcpSocket::OnRead();
	std::cout << "on read" << std::endl;
}

void DisplaySocket::OnAccept()
{
	TcpSocket::OnAccept();
	std::cout << "on accept" << std::endl;
}

void DisplaySocket::OnRawData(const char *buf, size_t len)
{
	/*char* c = new char[len + 1];
	memset(c, 0, len + 1);
	memcpy(c, buf, len);
	std::cout << "[RECV DATA]" << c << std::endl;
	delete[] c;*/

	TcpSocket::OnRawData(buf, len);

	std::cout << "[RECV DATA] " << ibuf.ReadString(len).c_str() << std::endl;
}

int main()
{
	//========================================================================
	// 一个GameServer对应一个服
	//========================================================================

	SocketHandler h;
	ListenSocket<DisplaySocket> l(h);
	if (l.Bind(6220)) {
		return 0;
	}
	h.Add(&l);
	h.Select(1, 0);
	while (true) {
		h.Select(1, 0);
	}

	return 0;
}