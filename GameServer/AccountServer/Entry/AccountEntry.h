#ifndef _ACCOUNT_ENTRY_H_
#define _ACCOUNT_ENTRY_H_

#include "Entry.h"

class AccountEntry : public Entry
{
public:
    AccountEntry(ISocketHandler& h);
    AccountEntry(ISocketHandler& h, size_t isize, size_t osize);
    ~AccountEntry();

protected:
    virtual std::shared_ptr<IActionFactory> GetActionFactory() override;
};

#endif // _ACCOUNT_ENTRY_H_