#ifndef _SYS_MESSAGE_H_
#define _SYS_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////
// 游戏分服请求玩家是否登入
class SysMsgAccountLogined : public BaseMsg
{
public:
    enum LoginResult
    {
        LR_FAIL,                    // 失败
        LR_LOGINED,                 // 玩家已登入
        LR_UNLOGIN,                 // 玩家未登入
    };

public:
    SysMsgAccountLogined();
    ~SysMsgAccountLogined();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned char result;
        unsigned long long userid;
    };
    MSG_INFO* m_info;
};

#pragma pack(pop)

#endif // _SYS_MESSAGE_H_