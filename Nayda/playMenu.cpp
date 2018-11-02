#include "playMenu.h"
#include "ui_playMenu.h"

#include <munchkinglobaldefines.h>

#include <QDesktopWidget>
#include <QStandardPaths>
#include <QDir>
#include <QThread>
#include <QPaintEvent>


playMenu::playMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{
    ui->setupUi(this);
    setWindowTitle(tr("Подготовка игры"));

    setUpSignalsSlotsConnections();

    _uiButtons.push_back(ui->btn_DebugStart);
    _uiButtons.push_back(ui->btn_GameSettings);
    _uiButtons.push_back(ui->btn_SendTestData);
    _uiButtons.push_back(ui->btn_ServerSettings);
    _uiButtons.push_back(ui->btn_Connection);

    setUpUiVisualizationParameters();

    _connectionState = ConnectionState::NoServerSettingsProvided;
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
    QObject::connect(serverSettingsWindow, &ServerSettings::sig_userHaveChangedServerSettings, this, &playMenu::slot_userHaveChangedServerSettings);
    serverSettingsWindow->setModal(true);
    serverSettingsWindow->show();
}

void playMenu::slot_userHaveChangedServerSettings(serverSettings settings)
{
    _connectionState = ConnectionState::CompleteServerSettings;
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressSetUp, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &playMenu::slot_openRoomForConnection);
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &playMenu::slot_showServerSettings);
    ui->lbl_Connection->setText("Сервер: " + settings.first + " Порт: " + settings.second);
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

void playMenu::setUpUiGeometricRelations()
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

    foreach (QPushButton* btn, _uiButtons)
        btn->setMaximumWidth(GeometricLimitations::beforeTheGameButtonsSize*HwScreenSizeWidth);
}

void playMenu::setUpSignalsSlotsConnections()
{
    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)), this, SLOT(slot_startGameWithDefaults()));
    QObject::connect(ui->btn_ServerSettings, &QPushButton::clicked, this, &playMenu::slot_showServerSettings);
    //QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &playMenu::slot_openRoomForConnection);
    QObject::connect(ui->btn_SendTestData, &QPushButton::clicked, this, &playMenu::slot_sendTestDataToServer);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &playMenu::slot_showServerSettings);
}

void playMenu::setUpUiPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Nayda/Pictures/playMenu";
    QString picturesLocationBasis = homeDirectory + uiPlayMenuFilesLocation + "/";

    _connectionButtonPictureAddressDefault = picturesLocationBasis + "cloud_gray.png";
    _connectionButtonPictureAddressSetUp = picturesLocationBasis + "cloud_blue.png";
    _connectionButtonPictureAddressConnected = picturesLocationBasis + "cloud_green.png";

    _gameSettingsButtonPictureAddressDefault = picturesLocationBasis + "gears_gray.png";
    _gameSettingsButtonPictureAddressSetUp = picturesLocationBasis + "gears_green.png";

    _createRoomButtonPictureAddressDefault = picturesLocationBasis + "crown_gray.png";
    _createRoomButtonPictureAddressAllowed = picturesLocationBasis + "crown_ready.png";

    _joinRoomButtonPictureAddressDefault = picturesLocationBasis + "binocular_gray.png";
    _joinRoomButtonPictureAddressAllowed = picturesLocationBasis + "binocular_read.png";
}

void playMenu::setUpButtonPicture(QPushButton* const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
{
    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());
    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*widthCoeff,
                                            geometry().width()*widthCoeff*heightWidthRelatio,
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    btn->setMinimumWidth(geometry().width()*widthCoeff);
    btn->setMinimumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
 }

void playMenu::setUpUiVisualizationParameters()
{
    setUpUiGeometricRelations();
    setUpUiPicturesAddresses();

    setUpButtonPicture(ui->btn_GameSettings, _gameSettingsButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_JoinToExistingLobby, _joinRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_CreateLobby, _createRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
}

void playMenu::closeEvent(QCloseEvent *event)
{
    emit sig_userIsClosingStartNewRoomWindow(true);
}
