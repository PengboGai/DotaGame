#include "OnlineOvertime.h"

// 玩家在线超时时间（毫秒）
const static int ONLINE_OVERTIME = 60 * 1000;

OnlineOvertime::OnlineOvertime()
{
}

OnlineOvertime::~OnlineOvertime()
{
}

void OnlineOvertime::AddUser(unsigned long long userid)
{
    m_list[userid] = ONLINE_OVERTIME;
}

bool OnlineOvertime::IsUserOnline(unsigned long long userid)
{
    return m_list.find(userid) != m_list.end();
}

void OnlineOvertime::Tick(time_t dt)
{
    auto iter = m_list.begin();
    for (; iter != m_list.end();) {
        iter->second -= dt;
        if (iter->second <= 0) {
            iter = m_list.erase(iter);
        }
        else {
            ++iter;
        }
    }
}
