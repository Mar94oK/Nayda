#include "playMenu.h"
#include "ui_playMenu.h"

#include <munchkinglobaldefines.h>

#include <QDesktopWidget>
#include <QStandardPaths>
#include <QDir>


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


    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString uiFilesLocation = "Munchkin/Nayda/Nayda/Pictures/playMenu";
    QString picturesLocationBasis = homeDirectory + uiFilesLocation;
    qDebug() <<"NAY-0001: playMenu pictures location: " << picturesLocationBasis;
    QString fileName = "cloud_blue.png";

    //qDebug() <<"NAY-0001: trying to locate picture: " = QStandardPaths::locate(picturesLocationBasis, QString("cloud_blue.png"),QStandardPaths::LocateFile);

    QString fullFilePath = picturesLocationBasis + fileName;

    QString gameSettingsPictureAddressDefault = ":/Pictures/playMenu/playMenu_oblako_connection_gray.jpg";
    QString gameSettingsPictureAddressSet = fullFilePath;
    QString gameSettingsPictureAddressConnected = ":/Pictures/playMenu/playMenu_oblako_connection_green.jpg";

    QPixmap pxmpBtnMainRepresenter(gameSettingsPictureAddressSet);
    QPalette plteBtnMainRepresenter;
    plteBtnMainRepresenter.setBrush(ui->btn_GameSettings->backgroundRole(),
    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*0.33,
                                        geometry().width()*0.33*0.66,
                                        Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_GameSettings->setMinimumWidth(geometry().width()*0.33);
    ui->btn_GameSettings->setMinimumHeight(geometry().width()*0.33*0.66);
    ui->btn_GameSettings->setFlat(true);
    ui->btn_GameSettings->setAutoFillBackground(true);
    ui->btn_GameSettings->setPalette(plteBtnMainRepresenter);


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
