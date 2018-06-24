#include "startnewroom.h"
#include "ui_start_new_room.h"

startNewRoom::startNewRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{
    ui->setupUi(this);

    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)), this, SLOT(slot_startGameWithDefaults()));
    QObject::connect(ui->btn_ServerSettings, &QPushButton::clicked, this, &startNewRoom::slot_showServerSettings);

}

startNewRoom::~startNewRoom()
{
    delete ui;
}

void startNewRoom::slot_startGameWithDefaults()
{
    emit sig_dbgBtnPlayWithDefaultsPressed(true);
}

void startNewRoom::slot_showServerSettings()
{
   serverSettingsWindow = new ServerSettings();
   QObject::connect(serverSettingsWindow, &ServerSettings::sig_userHaveChangedServerSettings, this, &startNewRoom::slot_userhaveChangedServerSetting);
   serverSettingsWindow->setModal(true);
   serverSettingsWindow->show();
}

void startNewRoom::slot_userhaveChangedServerSetting(serverSettings settings)
{
    emit sig_userHaveChangedServerSettings(settings);
}

void startNewRoom::closeEvent(QCloseEvent *event)
{
    emit sig_userIsClosingStartNewRoomWindow(true);
}
