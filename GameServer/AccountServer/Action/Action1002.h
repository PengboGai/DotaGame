#ifndef _ACTION_1002_H_
#define _ACTION_1002_H_

#include "Action.h"

// ���ע��
class Action1002 : public Action
{
public:
    Action1002(Entry& entry);
    virtual ~Action1002();

public:
    virtual void onMessage(MSG_HEAD* head) override;
};

#endif // _ACTION_1002_H_