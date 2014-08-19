#include "AccountMsg.h"
#include "MsgType.h"

CMsgAccountLogin::CMsgAccountLogin()
{
	setType(MSG_ACCOUNT_LOGIN_C);
	setLen(sizeof(SM_DATA_IN));
}

CMsgAccountLogin::~CMsgAccountLogin()
{
}

const char* CMsgAccountLogin::getUserName()
{
	return getDataIn()->name;
}

void CMsgAccountLogin::setUserName(const char* username, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->name, 0, sizeof(data_in->name));
	memcpy(data_in->name, username, len);
}

const char* CMsgAccountLogin::getUserPwd()
{
	return getDataIn()->pwd;
}

void CMsgAccountLogin::setUserPwd(const char* password, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->pwd, 0, sizeof(data_in->pwd));
	memcpy(data_in->pwd, password, len);
}

const char* CMsgAccountLogin::getUserIP()
{
	return getDataIn()->ip;
}

void CMsgAccountLogin::setUserIP(const char* ip, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->ip, 0, sizeof(data_in->ip));
	memcpy(data_in->ip, ip, len);
}

//////////////////////////////////////////////////////////////////////////
SMsgAccountLogin::SMsgAccountLogin()
{
	setType(MSG_ACCOUNT_LOGIN_S);
	setLen(sizeof(SM_DATA_IN));
}

SMsgAccountLogin::~SMsgAccountLogin()
{
}

void SMsgAccountLogin::setResult(LoginResult result)
{
	getDataIn()->result = (unsigned char)result;
}

SMsgAccountLogin::LoginResult SMsgAccountLogin::getResult()
{
	return (SMsgAccountLogin::LoginResult)getDataIn()->result;
}

//////////////////////////////////////////////////////////////////////////
CMsgAccountReg::CMsgAccountReg()
{
	setType(MSG_ACCOUNT_REG_C);
	setLen(sizeof(SM_DATA_IN));
}

CMsgAccountReg::~CMsgAccountReg()
{
}

const char* CMsgAccountReg::getUserName()
{
	return getDataIn()->name;
}

void CMsgAccountReg::setUserName(const char* username, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->name, 0, sizeof(data_in->name));
	memcpy(data_in->name, username, len);
}

const char* CMsgAccountReg::getUserPwd()
{
	return getDataIn()->pwd;
}

void CMsgAccountReg::setUserPwd(const char* pwd, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->pwd, 0, sizeof(data_in->pwd));
	memcpy(data_in->pwd, pwd, len);
}

const char* CMsgAccountReg::getUserConfirmPwd()
{
	return getDataIn()->pwd2;
}

void CMsgAccountReg::setUserConfirmPwd(const char* pwd, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->pwd2, 0, sizeof(data_in->pwd2));
	memcpy(data_in->pwd2, pwd, len);
}

const char* CMsgAccountReg::getUserIP()
{
	return getDataIn()->ip;
}

void CMsgAccountReg::setUserIP(const char* ip, unsigned int len)
{
	SM_DATA_IN* data_in = getDataIn();
	memset(data_in->ip, 0, sizeof(data_in->ip));
	memcpy(data_in->ip, ip, len);
}

//////////////////////////////////////////////////////////////////////////
SMsgAccountReg::SMsgAccountReg()
{
	setType(MSG_ACCOUNT_REG_S);
	setLen(sizeof(SM_DATA_IN));
}

SMsgAccountReg::~SMsgAccountReg()
{
}

void SMsgAccountReg::setResult(RegResult result)
{
	getDataIn()->result = (unsigned char)result;
}

SMsgAccountReg::RegResult SMsgAccountReg::getResult()
{
	return (SMsgAccountReg::RegResult)getDataIn()->result;
}