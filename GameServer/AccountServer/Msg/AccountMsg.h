#ifndef _ACCOUNT_MESSAGE_H_
#define _ACCOUNT_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

class CMsgAccountLogin : public BaseMsg
{
public:
    CMsgAccountLogin();
    ~CMsgAccountLogin();

public:
    struct MSG_INFO : MSG_HEAD
    {
        char name[20];
        char pwd[20];
        char ip[16];
    };
    MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
class SMsgAccountLogin : public BaseMsg
{
public:
    enum LoginResult
    {
        LR_FAIL,                    // 失败
        LR_SUCCESS,                 // 成功
        LR_INVALID_USER_OR_PWD      // 用户名或密码错误
    };

public:
    SMsgAccountLogin();
    ~SMsgAccountLogin();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned char result;
        unsigned long long userid;
    };
    MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
class CMsgAccountReg : public BaseMsg
{
public:
    CMsgAccountReg();
    ~CMsgAccountReg();

public:
    struct MSG_INFO : MSG_HEAD
    {
        char name[20];
        char pwd[20];
        char pwd2[20];
        char ip[16];
    };
    MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
class SMsgAccountReg : public BaseMsg
{
public:
    enum RegResult
    {
        RR_FAIL,                    // 失败
        RR_SUCCESS,                 // 注册成功
        RR_EXIST_USER,              // 用户名已存在
        RR_PWD_DIFFERENT,           // 两次密码不一样
    };

public:
    SMsgAccountReg();
    ~SMsgAccountReg();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned char result;
    };
    MSG_INFO* m_info;
};

//////////////////////////////////////////////////////////////////////////
// 分服列表消息
class SMsgServerList : public BaseMsg
{
public:
    enum ServerStatus
    {
        SS_NEW,     // 新服
        SS_GOOD,    // 良好
        SS_HOT,     // 火爆
    };

public:
    SMsgServerList();
    ~SMsgServerList();

    void AddServer(char name[20], ServerStatus status, char ip[16], unsigned short port);

public:
    struct SERVER_INFO
    {
        char name[20];          // 分服名称
        char ip[16];            // IP地址
        unsigned char status;   // 状态
        unsigned short port;    // 端口号
    };

    struct MSG_INFO : MSG_HEAD
    {
        unsigned char end;      // 是否最后一条消息
        unsigned short count;   // 列表数量
        SERVER_INFO servers[1]; // 分服列表
    };
    MSG_INFO* m_info;
};

#pragma pack(pop)

#endif // _ACCOUNT_MESSAGE_H_