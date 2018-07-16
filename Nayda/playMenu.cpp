#include "playMenu.h"
#include "ui_start_new_room.h"

#include <munchkinglobaldefines.h>

#include <QDesktopWidget>



playMenu::playMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{

    ui->setupUi(this);

//Signals-slots connections
    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)), this, SLOT(slot_startGameWithDefaults()));
    QObject::connect(ui->btn_ServerSettings, &QPushButton::clicked, this, &playMenu::slot_showServerSettings);
    QObject::connect(ui->btn_StartTheGame, &QPushButton::clicked, this, &playMenu::slot_openRoomForConnection);
    QObject::connect(ui->btn_SendTestData, &QPushButton::clicked, this, &playMenu::slot_sendTestDataToServer);
//Signals-slots connections

//Window-settings
    setWindowTitle(tr("Подготовка игры"));
    setGeometry(0,0,
                static_cast<uint32_t> (QApplication::desktop()->availableGeometry().width() * GeometricLimitations::beforeTheGameWindowsSize),
                static_cast<uint32_t> (QApplication::desktop()->availableGeometry().height() * GeometricLimitations::beforeTheGameWindowsSize));


    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    QApplication::desktop()->availableGeometry()));
//Window-settings

}

playMenu::~playMenu()
{
    delete ui;
}

void playMenu::slot_startGameWithDefaults()
{
    emit sig_dbgBtnPlayWithDefaultsPressed(true);
}

void playMenu::slot_showServerSettings()
{
    serverSettingsWindow = new ServerSettings();
    QObject::connect(serverSettingsWindow, &ServerSettings::sig_userHaveChangedServerSettings, this, &playMenu::slot_userhaveChangedServerSetting);
    serverSettingsWindow->setModal(true);
    serverSettingsWindow->show();
}

void playMenu::slot_userhaveChangedServerSetting(serverSettings settings)
{
    emit sig_userHaveChangedServerSettings(settings);
}

void playMenu::slot_openRoomForConnection()
{
    emit sig_openRoomForConnection();
}

void playMenu::slot_sendTestDataToServer()
{
    emit sig_sendTestDataToServer();
}

void playMenu::closeEvent(QCloseEvent *event)
{
    emit sig_userIsClosingStartNewRoomWindow(true);
}
