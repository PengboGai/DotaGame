#ifndef _MESSAGE_TYPE_H_
#define _MESSAGE_TYPE_H_

#define MSG_ACCOUNT_LOGIN_C                     1000    // 玩家登录（客户端->服务端）
#define MSG_ACCOUNT_LOGIN_S                     1001    // 玩家登录（服务端->客户端）
#define MSG_ACCOUNT_REG_C                       1002    // 玩家注册（客户端->服务端）
#define MSG_ACCOUNT_REG_S                       1003    // 玩家注册（服务端->客户端）
#define MSG_SERVER_LIST_S                       1004    // 分服列表（服务端->客户端）

#define SYS_MSG_USER_HAS_LOGINED                9000    // 玩家是否登入（游戏分服->账号服务器）

#endif // _MESSAGE_TYPE_H_