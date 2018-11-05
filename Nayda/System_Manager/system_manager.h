#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
//defines the Before_The_Game, Server and The_Game interactions
//takes three pointers
#include "Application/Before_The_Game/Before_The_Game.h"
#include "Application/The_Game/The_Game.h"
#include "Server/server.h"
 
//They all are singltones


/* This class is responsible for all interactions of the Layers (The_Game, Before_The_Game and Sever).
 * It doesn't strore any information, but working as post system between the Lyers.
 * */

class SystemManager
{
private:
    
    //make 'em all unique???
    Before_The_Game* m_beforeTheGamePtr;
    The_Game* m_theGamePtr;
    Server* m_serverPtr;
    
public:
    SystemManager(Before_The_Game*, Server*, The_Game*);
};

#endif // SYSTEM_MANAGER_H
