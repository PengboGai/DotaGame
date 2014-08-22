#ifndef _LOGIN_OVERTIME_H_
#define _LOGIN_OVERTIME_H_

#include <time.h>
#include <unordered_map>

class LoginOverTime
{
public:
    LoginOverTime();
    ~LoginOverTime();

    void AddUserLogin(unsigned long long userid);
    bool IsUserLogined(unsigned long long userid);

    void Tick(time_t dt);

private:
    std::unordered_map<unsigned long long, time_t> m_list;
};

#endif // _LOGIN_OVERTIME_H_