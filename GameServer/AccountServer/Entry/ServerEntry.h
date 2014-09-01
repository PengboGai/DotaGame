#ifndef _SERVER_ENTRY_H_
#define _SERVER_ENTRY_H_

#include "Entry.h"

class ServerEntry : public Entry
{
public:
    ServerEntry(ISocketHandler& h);
    ServerEntry(ISocketHandler& h, size_t isize, size_t osize);
    ~ServerEntry();

protected:
    virtual std::shared_ptr<IActionFactory> GetActionFactory() override;
};

#endif // _SERVER_ENTRY_H_