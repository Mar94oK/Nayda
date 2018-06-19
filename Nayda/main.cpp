#include "main_application.h"
#include <QApplication>
#include "Application/Before_The_Game/Before_The_Game.h"
#include "Application/The_Game/The_Game.h"
#include "System_Manager/system_manager.h"
#include "Server/server.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server obj_Server;
    Before_The_Game obj_Before_The_Game;
    The_Game obj_The_Game;
    SystemManager obj_System_Manager(&obj_Before_The_Game, &obj_Server, &obj_The_Game);
    //Main_Application w;
    //w.show();

    obj_Before_The_Game.show();
    obj_The_Game.hide();

    return a.exec();
}
