#ifndef _ACTION_9000_H_
#define _ACTION_9000_H_

#include "Action.h"

// ����Ƿ���루��Ϸ�ַ�->�˺ŷ�������
class Action9000 : public Action
{
public:
    Action9000(Entry& entry);
    virtual ~Action9000();

public:
    virtual void onMessage(MSG_HEAD* head) override;
};

#endif // _ACTION_9000_H_