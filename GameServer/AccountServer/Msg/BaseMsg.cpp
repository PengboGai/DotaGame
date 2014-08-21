#include "BaseMsg.h"

BaseMsg::BaseMsg()
{
    memset(m_buffer, 0, sizeof(m_buffer));
    m_head = (MSG_HEAD*)m_buffer;
}

BaseMsg::~BaseMsg()
{
}

unsigned short BaseMsg::GetLen()
{
    return m_head->len;
}

void BaseMsg::SetLen(unsigned short len)
{
    if (m_head) {
        m_head->len = len;
    }
}

unsigned short BaseMsg::GetType()
{
    return m_head->type;
}

void BaseMsg::SetType(unsigned short type)
{
    if (m_head) {
        m_head->type = type;
    }
}

const char* BaseMsg::GetBuffer()
{
    return m_buffer;
}

MSG_HEAD* BaseMsg::GetHead()
{
    return m_head;
}

bool BaseMsg::SetBuffer(const char* buf, unsigned int len)
{
    if (buf == nullptr || len < 4 || len > MSG_MAX_SIZE) {
        return false;
    }
    memset(m_buffer, 0, sizeof(m_buffer));
    memcpy(m_buffer, buf, len);
    return true;
}
