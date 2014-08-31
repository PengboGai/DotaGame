#ifndef _GAME_SERVERS_H_
#define _GAME_SERVERS_H_

#include <memory>
#include <string>
#include <vector>
#include <map>

class GameServers
{
public:
    struct Item
    {
        unsigned int id;
        char name[20];
        char ip[16];
        unsigned short port;
    };

public:
    GameServers();
    ~GameServers();
    
    bool AddItem(unsigned int id, char name[20], char ip[20], unsigned short port);
    void RemoveItem(unsigned int id);
    bool ExistItem(unsigned int id);

    std::vector<GameServers::Item*> GetList();
    
    void Clear();

private:
    std::map<int, Item*> m_servers;
};

#endif // _GAME_SERVERS_H_