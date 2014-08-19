#include <iostream>
#include "ClientSocket.h"

int main()
{
	SocketHandler h;
	ClientSocket* s = new ClientSocket(h);
	s->SetDeleteByHandler();
	s->Open("localhost", 6220);
	h.Add(s);
	h.Select(1, 0);
	while (h.GetCount()) {
		h.Select(0, 300 * 1000);
	}
	getchar();

	return 0;
}