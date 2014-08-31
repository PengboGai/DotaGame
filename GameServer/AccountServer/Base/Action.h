#ifndef _BASE_ACTION_H_
#define _BASE_ACTION_H_

#include "BaseMsg.h"
#include "Connection.h"
#include "Command.h"
#include "DataField.h"
#include "DataItem.h"
#include "DataRow.h"
#include "DataTable.h"
#include "DataReader.h"
#include "TimerManager.h"

using namespace MySql;
using namespace Utilities;

class Entry;

class Action
{
public:
    Action(Entry& entry);
    virtual ~Action();

public:
    virtual void onMessage(MSG_HEAD* head) = 0;

protected:
    void Send(BaseMsg* msg);

    TimerManager& GetTimerManager();
    std::shared_ptr<Command> GetCommand();

protected:
    Entry& m_entry;
    std::shared_ptr<Command> m_cmd;
};

#endif // _BASE_ACTION_H_