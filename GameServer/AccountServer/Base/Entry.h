#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "TcpSocket.h"

class IActionFactory;
class Entry : public TcpSocket
{
public:
    Entry(ISocketHandler& h);
    Entry(ISocketHandler& h, size_t isize, size_t osize);
    virtual ~Entry();

protected:
    virtual void OnRead() override;
    virtual void OnMessage(const char* msg);

    virtual std::shared_ptr<IActionFactory> GetActionFactory() = 0;
};

#endif // _ENTRY_H_