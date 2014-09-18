#ifndef _SYS_MESSAGE_H_
#define _SYS_MESSAGE_H_

#include "BaseMsg.h"

#pragma pack(push, 1)

//////////////////////////////////////////////////////////////////////////
// ��Ϸ�ַ���������Ƿ����
class SysMsgAccountLogined : public BaseMsg
{
public:
    enum LoginResult
    {
        LR_FAIL,                    // ʧ��
        LR_LOGINED,                 // ����ѵ���
        LR_UNLOGIN,                 // ���δ����
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