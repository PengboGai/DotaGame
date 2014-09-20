#ifndef _ACTION_1000_H_
#define _ACTION_1000_H_

#include "Action.h"

// 客户端->服务端 登入请求
class Action1000 : public Action
{
public:
    Action1000(Entry& entry);
    ~Action1000();

public:
    virtual void onMessage(MSG_HEAD* head) override;
};

#endif // _ACTION_1000_H_