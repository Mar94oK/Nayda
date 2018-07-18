#include "playMenu.h"
#include "ui_playMenu.h"

#include <munchkinglobaldefines.h>

#include <QDesktopWidget>



playMenu::playMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{
    ui->setupUi(this);
    setWindowTitle(tr("Подготовка игры"));

    setUpSignalsSlotsConnections();

    setUpGeometricRelations();
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

void playMenu::setUpGeometricRelations()
{
    QRect HwScreenSize = QApplication::desktop()->screenGeometry();
    int HwScreenSizeWidth = HwScreenSize.width();
    int HwScreenSizeHeight = HwScreenSize.height();

    setGeometry(0,0,
                static_cast<uint32_t> (HwScreenSizeWidth * GeometricLimitations::beforeTheGameWindowsSize),
                static_cast<uint32_t> (HwScreenSizeHeight * GeometricLimitations::beforeTheGameWindowsSize));


    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    QApplication::desktop()->availableGeometry()));

    std::vector<QPushButton*> buttons;
    buttons.push_back(ui->btn_DebugStart);
    buttons.push_back(ui->btn_GameSettings);
    buttons.push_back(ui->btn_SendTestData);
    buttons.push_back(ui->btn_ServerSettings);
    buttons.push_back(ui->btn_StartTheGame);

    foreach (QPushButton* btn, buttons)
    {
        btn->setMaximumWidth(GeometricLimitations::beforeTheGameButtonsSize*HwScreenSizeWidth);
    }

}

void playMenu::setUpSignalsSlotsConnections()
{
    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)), this, SLOT(slot_startGameWithDefaults()));
    QObject::connect(ui->btn_ServerSettings, &QPushButton::clicked, this, &playMenu::slot_showServerSettings);
    QObject::connect(ui->btn_StartTheGame, &QPushButton::clicked, this, &playMenu::slot_openRoomForConnection);
    QObject::connect(ui->btn_SendTestData, &QPushButton::clicked, this, &playMenu::slot_sendTestDataToServer);
}

void playMenu::closeEvent(QCloseEvent *event)
{
    emit sig_userIsClosingStartNewRoomWindow(true);
}
