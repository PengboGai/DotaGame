#ifndef _IACTION_FACTORY_H_
#define _IACTION_FACTORY_H_

class Action;
class Entry;

class IActionFactory
{
public:
    IActionFactory() {}
    virtual ~IActionFactory() {}

public:
    virtual Action* GetAction(int msg_type, Entry& entry) = 0;
};

#endif // _IACTION_FACTORY_H_