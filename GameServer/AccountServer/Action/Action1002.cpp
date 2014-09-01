#include "Action1002.h"
#include "AccountMsg.h"
#include "StringTool.h"

Action1002::Action1002(Entry& entry)
: Action(entry)
{
}

Action1002::~Action1002()
{
}

void Action1002::onMessage(MSG_HEAD* head)
{
    CMsgAccountReg msg;
    msg.SetBuffer((const char*)head, head->len);

    std::string name = msg.m_info->name;
    std::string pwd = msg.m_info->pwd;
    std::string pwd2 = msg.m_info->pwd2;

    unsigned char result = 0;
    if (pwd != pwd2) {
        result = SMsgAccountReg::RR_PWD_DIFFERENT;
    }
    else {
        std::string query = StringTool::Format("SELECT * FROM `account` "
            "WHERE `user_name`='%s' LIMIT 1;", name.c_str());
        GetCommand()->SetCommandText(query);
        std::shared_ptr<DataReader> reader = GetCommand()->ExecuteReader();
        if (reader) {
            if (reader->HasRow()) {
                result = SMsgAccountReg::RR_EXIST_USER;
            }
            else {
                std::shared_ptr<DataTable> table = reader->GetDataTable();
                std::shared_ptr<DataRow> row = table->CreateNewRow();
                row->SetStringItem("user_name", name);
                row->SetStringItem("user_pwd", pwd);
                row->SetIntItem("create_time", time(nullptr));
                row->SetIntItem("login_time", time(nullptr));
                row->SetStringItem("login_ip", msg.m_info->ip);
                if (row->Insert(GetCommand())) {
                    result = SMsgAccountReg::RR_SUCCESS;
                }
            }
        }
    }

    SMsgAccountReg send_msg;
    send_msg.m_info->result = result;
    Send(&send_msg);
}
