#include "start_new_room.h"
#include "ui_start_new_room.h"

start_new_room::start_new_room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start_new_room)
{
    ui->setupUi(this);

    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)),this,SLOT(start_game_with_defaults()));

}

start_new_room::~start_new_room()
{
    delete ui;
}

void start_new_room::start_game_with_defaults()
{
    emit dbg_btn_play_with_defaults_pressed(true);
    qDebug() << "pressed!";
}

void start_new_room::closeEvent(QCloseEvent *event)
{
    emit userIsClosingStartNewRoomWindow(true);
}
