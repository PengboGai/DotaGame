#include "Action1000.h"
#include "AccountMsg.h"
#include "StringTool.h"
#include "Entry.h"

// 一个包所允许存储的最大分服数
const static int MAX_SERVER_SIZE = 20;

Action1000::Action1000(Entry& entry)
: Action(entry)
{
}

Action1000::~Action1000()
{
}

void Action1000::onMessage(MSG_HEAD* head)
{
    CMsgAccountLogin msg;
    msg.SetBuffer((const char*)head, head->len);

    std::string name = msg.m_info->name;
    std::string pwd = msg.m_info->pwd;

    unsigned char result = 0;
    unsigned long long userid = 0;
    std::string query = StringTool::Format("SELECT * FROM `account` "
        "WHERE `user_name`='%s' AND `user_pwd`='%s' LIMIT 1;", name.c_str(), pwd.c_str());
    GetCommand()->SetCommandText(query);
    std::shared_ptr<DataReader> reader = GetCommand()->ExecuteReader();
    if (reader && reader->HasRow()) {
        std::shared_ptr<DataTable> table = reader->GetDataTable();
        std::shared_ptr<DataRow> row = table->GetRow(0);
        row->SetStringItem("login_ip", msg.m_info->ip);
        row->SetIntItem("login_time", time(nullptr));
        if (row->Update(GetCommand())) {
            result = SMsgAccountLogin::LR_SUCCESS;
            userid = row->GetIntItem("id");
        }
        else {
            result = SMsgAccountLogin::LR_FAIL;
        }
    }
    else {
        result = SMsgAccountLogin::LR_INVALID_USER_OR_PWD;
    }

    SMsgAccountLogin send_msg;
    send_msg.m_info->result = result;
    send_msg.m_info->userid = userid;
    Send(&send_msg);

    if (result == SMsgAccountLogin::LR_SUCCESS) {
        SendServerList();
    }
}

void Action1000::SendServerList()
{
    //std::shared_ptr<SMsgServerList> send_msg(new SMsgServerList());
    //const std::vector<ServerList::Item*>& list = m_entry.GetServerList();
    //for (unsigned int i = 0; i < list.size(); ++i) {
    //    ServerList::Item* item = list[i];
    //    if (send_msg->m_info->count >= MAX_SERVER_SIZE) {
    //        if ((i + 1) == list.size()) {
    //            send_msg->m_info->end = 1;
    //        }
    //        Send(send_msg.get());
    //        send_msg.reset(new SMsgServerList());
    //    }
    //    send_msg->AddServer(item->name, SMsgServerList::SS_GOOD, item->ip, item->port);
    //}
    //if (send_msg->m_info->count > 0) {
    //    send_msg->m_info->end = 1;
    //    Send(send_msg.get());
    //}
}
