#include "Server/server.h"
#include "QDebug"



//Before_The_Game::Before_The_Game(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::Before_The_Game)
//{

Server::Server(QObject *parent) : QObject(parent) { m_value = 0; }

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

