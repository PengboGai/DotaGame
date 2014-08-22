#include "LoginOverTime.h"

// 玩家登入超时时间（毫秒）
const static int LOGIN_OVERTIME = 60 * 1000;

LoginOverTime::LoginOverTime()
{
}

LoginOverTime::~LoginOverTime()
{
}

void LoginOverTime::AddUserLogin(unsigned long long userid)
{
    m_list[userid] = LOGIN_OVERTIME;
}

bool LoginOverTime::IsUserLogined(unsigned long long userid)
{
    return m_list.find(userid) != m_list.end();
}

void LoginOverTime::Tick(time_t dt)
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
