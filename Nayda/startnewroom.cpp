#include "startnewroom.h"
#include "ui_start_new_room.h"

startNewRoom::startNewRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{
    ui->setupUi(this);

    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)), this, SLOT(startGameWithDefaults()));
    QObject::connect(ui->btn_ServerSettings, &QPushButton::clicked, this, &startNewRoom::showServerSettings);

}

startNewRoom::~startNewRoom()
{
    delete ui;
}

void startNewRoom::startGameWithDefaults()
{
    emit dbgBtnPlayWithDefaultsPressed(true);
}

void startNewRoom::showServerSettings()
{
    qDebug() << "Show server settings";
}

void startNewRoom::closeEvent(QCloseEvent *event)
{
    emit userIsClosingStartNewRoomWindow(true);
}
