#include "Server/server.h"
#include "QDebug"



Server::Server(QObject *parent) : QObject(parent)
{
    m_value = 0;
    _srvrSettings.first = "";
    _srvrSettings.second = "";
}

bool Server::something()
{
    int i = 1;
    return true;
}

void Server::dbgTheGameBeginsStateReceived(bool begins)
{
    if (begins)
    qDebug() << endl << "Server_received_the_game_begins_state";
}

