#ifndef _USER_MESSAGE_H_
#define _USER_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////
// 客户端->服务端 登入请求
class CMsgUserLogin : public BaseMsg
{
public:
    CMsgUserLogin();
    ~CMsgUserLogin();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned long long userid;
        char ip[16];
    };
    MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
// 服务端->客户端 登入请求
class SMsgUserLogin : public BaseMsg
{
public:
    enum LoginResult
    {
        LR_FAIL,            // 登入失败
        LR_SUCCESS,         // 登入成功
        LR_OVERTIME,        // 登入超时
        LR_FREEZE           // 账户冻结
    };

public:
    SMsgUserLogin();
    ~SMsgUserLogin();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned long long userid;
        unsigned char result;
    };
    MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
// 服务端->客户端 玩家信息
class SMsgUserInfo : public BaseMsg
{
public:
    SMsgUserInfo();
    ~SMsgUserInfo();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned long long userid;
        char nick_name[20];                     // 玩家昵称
        unsigned long long change_name_time;    // 改名时间
        unsigned int team_level;                // 战队等级
        unsigned int team_exp;                  // 战队经验
        unsigned short head_id;                 // 头像编号
        unsigned long long gold_coin;           // 金币
        unsigned long long gem;                 // 宝石
        unsigned long long expedition_coin;     // 远征币
        unsigned short power;                   // 体力
        unsigned long long power_time;          // 体力值恢复时间
        unsigned char skill_point;              // 技能点
        unsigned long long skill_point_time;    // 技能点恢复时间
        unsigned char new_guide;                // 新手引导步骤
    };
    MSG_INFO* m_info;
};

#pragma pack(pop)

#endif // _USER_MESSAGE_H_