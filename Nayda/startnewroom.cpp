#include "startnewroom.h"
#include "ui_start_new_room.h"

start_new_room::start_new_room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{
    ui->setupUi(this);

    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)),this,SLOT(startGameWithDefaults()));

}

start_new_room::~start_new_room()
{
    delete ui;
}

void start_new_room::startGameWithDefaults()
{
    emit dbgBtnPlayWithDefaultsPressed(true);
}

void start_new_room::showServerSettings()
{

}

void start_new_room::closeEvent(QCloseEvent *event)
{
    emit userIsClosingStartNewRoomWindow(true);
}
