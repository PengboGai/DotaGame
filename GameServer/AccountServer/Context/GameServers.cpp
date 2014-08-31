#include "GameServers.h"
#include "DataItem.h"

GameServers::GameServers()
{
}

GameServers::~GameServers()
{
    Clear();
}

bool GameServers::AddItem(unsigned int id, char name[20], char ip[20], unsigned short port)
{
    if (ExistItem(id)) {
        return false;
    }

    Item* item = new Item();
    memset(item, 0, sizeof(Item));

    item->id = id;
    item->port = port;
    memcpy(item->name, name, sizeof(item->name));
    memcpy(item->ip, ip, sizeof(item->ip));

    m_servers[id] = item;

    return true;
}

void GameServers::RemoveItem(unsigned int id)
{
    auto iter = m_servers.find(id);
    if (iter != m_servers.end()) {
        delete iter->second;
        iter->second = nullptr;
        m_servers.erase(iter);
    }
}

bool GameServers::ExistItem(unsigned int id)
{
    return m_servers.find(id) != m_servers.end();
}

std::vector<GameServers::Item*> GameServers::GetList()
{
    std::vector<GameServers::Item*> list;
    auto iter = m_servers.begin();
    for (; iter != m_servers.end(); ++iter) {
        list.push_back(iter->second);
    }
    return std::move(list);
}

void GameServers::Clear()
{
    auto iter = m_servers.begin();
    for (; iter != m_servers.end(); ++iter) {
        delete iter->second;
        iter->second = nullptr;
    }
    m_servers.clear();
}
