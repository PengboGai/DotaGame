#ifndef _ONLINE_OVERTIME_H_
#define _ONLINE_OVERTIME_H_

#include <time.h>
#include <map>

class OnlineOvertime
{
public:
    OnlineOvertime();
    ~OnlineOvertime();

    void AddUser(unsigned long long userid);
    bool IsUserOnline(unsigned long long userid);

    void Tick(time_t dt);

private:
    std::map<unsigned long long, time_t> m_list;
};

#endif // _ONLINE_OVERTIME_H_