#ifndef _BASE_MESSAGE_H_
#define _BASE_MESSAGE_H_

#include <memory>

#pragma pack(push, 1)

#define MSG_MAX_SIZE		2 * 1024
#define MSG_HEAD_SIZE		sizeof(MSG_HEAD)

struct MSG_HEAD
{
    unsigned short len;
    unsigned short type;
};

class BaseMsg
{
public:
    BaseMsg();
    virtual ~BaseMsg();

    unsigned short GetLen();
    void SetLen(unsigned short len);

    unsigned short GetType();
    void SetType(unsigned short type);

    MSG_HEAD* GetHead();
    const char* GetBuffer();
    bool SetBuffer(const char* buf, unsigned int len);

private:
    MSG_HEAD* m_head;
    char m_buffer[MSG_MAX_SIZE];
};

#pragma pack(pop)

#endif // _BASE_MESSAGE_H_