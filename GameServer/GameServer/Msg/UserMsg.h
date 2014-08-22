#ifndef _USER_MESSAGE_H_
#define _USER_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////
// �ͻ���->����� ��������
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
// �����->�ͻ��� ��������
class SMsgUserLogin : public BaseMsg
{
public:
    enum LoginResult
    {
        LR_FAIL,            // ����ʧ��
        LR_SUCCESS,         // ����ɹ�
        LR_OVERTIME,        // ���볬ʱ
        LR_FREEZE           // �˻�����
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
// �����->�ͻ��� �����Ϣ
class SMsgUserInfo : public BaseMsg
{
public:
    SMsgUserInfo();
    ~SMsgUserInfo();

public:
    struct MSG_INFO : MSG_HEAD
    {
        unsigned long long userid;
        char nick_name[20];                     // ����ǳ�
        unsigned long long change_name_time;    // ����ʱ��
        unsigned int team_level;                // ս�ӵȼ�
        unsigned int team_exp;                  // ս�Ӿ���
        unsigned short head_id;                 // ͷ����
        unsigned long long gold_coin;           // ���
        unsigned long long gem;                 // ��ʯ
        unsigned long long expedition_coin;     // Զ����
        unsigned short power;                   // ����
        unsigned long long power_time;          // ����ֵ�ָ�ʱ��
        unsigned char skill_point;              // ���ܵ�
        unsigned long long skill_point_time;    // ���ܵ�ָ�ʱ��
        unsigned char new_guide;                // ������������
    };
    MSG_INFO* m_info;
};

#pragma pack(pop)

#endif // _USER_MESSAGE_H_