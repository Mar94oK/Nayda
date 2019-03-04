#include "PlayMenu.h"
#include "ui_playMenu.h"

#include <munchkinglobaldefines.h>

#include <QDesktopWidget>
#include <QStandardPaths>
#include <QDir>
#include <QThread>
#include <QPaintEvent>

#include <QStyle>


PlayMenu::PlayMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startNewRoom)
{
    DECLARE_NAMED_LOGGER(PlayMenu);

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
    SetUpInitilButtonsStates();

    emit SignalUserHaveChangedGameSettings(_gameSettings);
}

PlayMenu::~PlayMenu()
{
    delete ui;
}

void PlayMenu::SlotShowRoomConnectionQuestions()
{
    connectionToRoomQuestions = new ConnectionToRoomQuestions();
    connectionToRoomQuestions->setModal(true);
    emit SignalUserHaveChangedGameSettings(_gameSettings);
    connectionToRoomQuestions->show();

    QObject::connect(connectionToRoomQuestions, &ConnectionToRoomQuestions::SignalSendClientConnectionToRoomRequest, this, &PlayMenu::SlotSendClientConnectionToRoomRequest);
}

void PlayMenu::SlotSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data)
{
    emit SignalLockUserButtonsWhileConnnectingToRoom();
    emit SignalSendClientConnectionToRoomRequest(data);
}


void PlayMenu::slot_startGameWithDefaults()
{
    emit sig_dbgBtnPlayWithDefaultsPressed(true);
}

void PlayMenu::SlotShowServerSettings()
{
    logger.Debug() << "Slot SlotShowServerSettings() called once.";
    serverSettingsWindow = new ServerSettings();
    QObject::connect(serverSettingsWindow, &ServerSettings::sig_userHaveChangedServerSettings, this, &PlayMenu::SlotUserHaveChangedServerSettings);
    serverSettingsWindow->setModal(true);
    serverSettingsWindow->show();
}

void PlayMenu::SlotUserHaveChangedServerSettings(serverSettings settings)
{
    _connectionState = ConnectionState::CompleteServerSettings;
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressSetUp, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotSetUpConnection);
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    qDebug() << "NAY-001 SlotShowServerSettings() disconnected! ";
    ui->lbl_Connection->setText("Сервер: " + settings.first + '\n'+
                                "Порт: " + settings.second + '\n' +
                                "Нажмите ещё раз для соединения с сервером!");
    _serverSettings.first = settings.first;
    _serverSettings.second = settings.second;
    emit sig_userHaveChangedServerSettings(settings);
}

void PlayMenu::SlotSetUpConnection()
{
    emit SignalSetUpConnection();
}

void PlayMenu::slot_sendTestDataToServer()
{
    emit sig_sendTestDataToServer();
}

void PlayMenu::SlotShowGameSettingsWindow()
{
    gameSettingsWindow = new GameSettingsWindow(_gameSettings);
    QObject::connect(gameSettingsWindow, &GameSettingsWindow::SignalUserHaveChangedSettings, this, &PlayMenu::SlotUserHaveChangedGameSettings);
    gameSettingsWindow->setModal(true);
    gameSettingsWindow->show();
}

void PlayMenu::SlotUserHaveChangedGameSettings(const GameSettings & settings)
{
    _gameSettings.applyNewSettings(settings);
    setUpButtonPicture(ui->btn_GameSettings, _gameSettingsButtonPictureAddressSetUp, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    emit SignalUserHaveChangedGameSettings(settings);
}

void PlayMenu::SlotProcessServerQueryReplyData(ServerQueryReplyData data)
{
    if (data._connectionToRoomAllowed)
    {
        setUpButtonPicture(ui->btn_JoinToExistingLobby, _joinRoomButtonPictureAddressAllowed, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
        ui->btn_JoinToExistingLobby->setEnabled(true);
    }
    if (data._roomCreationAllowed)
    {
        setUpButtonPicture(ui->btn_CreateLobby, _createRoomButtonPictureAddressAllowed, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
        ui->btn_CreateLobby->setEnabled(true);
    }
    ui->lbl_Connection->setText("Сервер: " + _serverSettings.first + '\n'+
                                "Порт: " + _serverSettings.second + '\n' +
                                "Имя сервера: " + data._serverName);

    //Disabling new connection attempts till some Errors occured.
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotSetUpConnection);
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressConnected, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
}

void PlayMenu::SlotAbortingConnectionByUserInitiative()
{
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotSetUpConnection);
//?
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    qDebug() << "NAY-001: SlotShowServerSettings() connected! SlotAbortingConnectionByUserInitiative()";
    ui->lbl_Connection->setText("Вы отключились от сервера! Соединитесь заново, пожалуйста.");
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->btn_CreateLobby->setEnabled(false);
    setUpButtonPicture(ui->btn_CreateLobby, _createRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->btn_JoinToExistingLobby->setEnabled(false);
    setUpButtonPicture(ui->btn_JoinToExistingLobby, _joinRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
}

void PlayMenu::SlotShowConnectionToRoomRejectedWindow(bool noRooms)
{
    connectionRejected = new ConnectionToRoomRejectedMessageWindow();
    connectionRejected->setModal(true);
    connectionRejected->show();
}

void PlayMenu::SlotShowServerQueueOversizedWindow()
{
    serverQueryOversized = new ServerQueryOversizedWindow();
    serverQueryOversized->setModal(true);
    serverQueryOversized->show();
    QObject::connect(serverQueryOversized, &ServerQueryOversizedWindow::SignalUnlockUserButtonsAfterConnectionToRoomReply,
                     this, &PlayMenu::SlotUnlockUserButtonsAfterConnectingToRoomReply);
}

void PlayMenu::SlotUnlockUserButtonsAfterConnectingToRoomReply()
{
    ui->btn_Connection->setEnabled(true);
    ui->btn_CreateLobby->setEnabled(true);
    ui->btn_JoinToExistingLobby->setEnabled(true);
}

void PlayMenu::SlotLockUserButtonsWhileConnnectingToRoom()
{
    ui->btn_Connection->setEnabled(false);
    ui->btn_CreateLobby->setEnabled(false);
    ui->btn_JoinToExistingLobby->setEnabled(false);
}

void PlayMenu::SlotProcessRemoteHostClosedErrorReport()
{
    ui->btn_Connection->setEnabled(true);
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotSetUpConnection);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    qDebug() << "NAY-001: SlotShowServerSettings() connected! SlotProcessRemoteHostClosedErrorReport()";
    ui->btn_CreateLobby->setEnabled(false);
    setUpButtonPicture(ui->btn_CreateLobby, _createRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->btn_JoinToExistingLobby->setEnabled(false);
    setUpButtonPicture(ui->btn_JoinToExistingLobby, _joinRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->lbl_Connection->setText("Сервер отключился!\n Пожалуйста, заново настройте подключение и попробуйте соединиться!");
}

void PlayMenu::SlotProcessRemoteHostConnectionRefusedErrorReport()
{
    ui->btn_Connection->setEnabled(true);
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotSetUpConnection);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    qDebug() << "NAY-001: SlotShowServerSettings() connected! SlotProcessRemoteHostConnectionRefusedErrorReport()";
    ui->lbl_Connection->setText("Сервер отклонил попытку соединения!\n Пожалуйста, убедитесь, что подключаетесь к нужному серверу\n"
                                "и проверьте порт подключения.");
}

void PlayMenu::SlotProcessRemoteHostNotFoundErrorReport()
{
    ui->btn_Connection->setEnabled(true);
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    QObject::disconnect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotSetUpConnection);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    qDebug() << "NAY-001: SlotShowServerSettings() connected! SlotProcessRemoteHostNotFoundErrorReport()";
    ui->lbl_Connection->setText("Сервер не обнаружен!\nПожалуйста, укажите другой сервер, или проверьте доступность текущего.\n"
                                "Возможно, на нём не запущен Манчкин?");
}

void PlayMenu::SlotProcessLockingConnectionButtonWhileConnecting()
{
    ui->btn_Connection->setEnabled(false);
}

void PlayMenu::SlotProcessUnlockConnectionButtonAfterConnection()
{
    ui->btn_Connection->setEnabled(true);
}

void PlayMenu::SlotProcessRoomCreationReplyError(ClientRoomCreationReplyData data)
{
    ui->lbl_CreateLObby->setText("В процессе создания зала произошла ошибка! ");
    if (data._errors.incorrectSettings)
        ui->lbl_CreateLObby->setText("В процессе создания зала произошла ошибка! Неверные настройки. Пожалуйста, проверьте их.");
    if (data._errors.rulesAreNotSupported)
        ui->lbl_CreateLObby->setText("Тип правил не поддерживается сервером. Пожалуйста, обновите сервер, или используйте другие правила.");
    if (data._errors.noFreeSlots)
        ui->lbl_CreateLObby->setText("В процессе создания зала произошла ошибка! На сервере нет свободных слотов!");

}

void PlayMenu::setUpUiGeometricRelations()
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

void PlayMenu::setUpSignalsSlotsConnections()
{
    QObject::connect(ui->btn_DebugStart, SIGNAL(clicked(bool)), this, SLOT(slot_startGameWithDefaults()));
    QObject::connect(ui->btn_ServerSettings, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    QObject::connect(ui->btn_GameSettings, &QPushButton::clicked, this, &PlayMenu::SlotShowGameSettingsWindow);
    QObject::connect(ui->btn_SendTestData, &QPushButton::clicked, this, &PlayMenu::slot_sendTestDataToServer);
    QObject::connect(ui->btn_Connection, &QPushButton::clicked, this, &PlayMenu::SlotShowServerSettings);
    QObject::connect(ui->btn_CreateLobby, &QPushButton::clicked, this, &PlayMenu::SlotSendClientRoomCreationRequest);
    QObject::connect(ui->btn_JoinToExistingLobby, &QPushButton::clicked, this, &PlayMenu::SlotShowRoomConnectionQuestions);
    QObject::connect(this, &PlayMenu::SignalLockUserButtonsWhileConnnectingToRoom, this, &PlayMenu::SlotLockUserButtonsWhileConnnectingToRoom);
}

void PlayMenu::setUpUiPicturesAddresses()
{

#ifndef USE_RESOURCES

    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);


#ifdef Q_OS_WIN
//NAY-001: EXPECTED_ERROR
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Pictures/playMenu";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Nayda/Pictures/playMenu";
#endif

    QString picturesLocationBasis = homeDirectory + uiPlayMenuFilesLocation + "/";

    _connectionButtonPictureAddressDefault = picturesLocationBasis + "cloud_gray.png";
    _connectionButtonPictureAddressSetUp = picturesLocationBasis + "cloud_blue.png";
    _connectionButtonPictureAddressConnected = picturesLocationBasis + "cloud_green.png";

    _gameSettingsButtonPictureAddressDefault = picturesLocationBasis + "gears_gray.png";
    _gameSettingsButtonPictureAddressSetUp = picturesLocationBasis + "gears_green.png";

    _createRoomButtonPictureAddressDefault = picturesLocationBasis + "crown_gray.png";
    _createRoomButtonPictureAddressAllowed = picturesLocationBasis + "crown_ready.png";

    _joinRoomButtonPictureAddressDefault = picturesLocationBasis + "binocular_gray.png";
    _joinRoomButtonPictureAddressAllowed = picturesLocationBasis + "binocular_ready.png";

#else

    _connectionButtonPictureAddressDefault = ":/Pictures/playMenu/cloud_gray.png";
    _connectionButtonPictureAddressSetUp = ":/Pictures/playMenu/cloud_blue.png";
    _connectionButtonPictureAddressConnected = ":/Pictures/playMenu/cloud_green.png";

    _gameSettingsButtonPictureAddressDefault = ":/Pictures/playMenu/gears_gray.png";
    _gameSettingsButtonPictureAddressSetUp = ":/Pictures/playMenu/gears_green.png";

    _createRoomButtonPictureAddressDefault = ":/Pictures/playMenu/crown_gray.png";
    _createRoomButtonPictureAddressAllowed = ":/Pictures/playMenu/crown_ready.png";

    _joinRoomButtonPictureAddressDefault = ":/Pictures/playMenu/binocular_gray.png";
    _joinRoomButtonPictureAddressAllowed = ":/Pictures/playMenu/binocular_ready.png";

#endif



}

void PlayMenu::setUpButtonPicture(QPushButton* const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
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

void PlayMenu::setUpUiVisualizationParameters()
{
    setUpUiGeometricRelations();
    setUpUiPicturesAddresses();

    setUpButtonPicture(ui->btn_GameSettings, _gameSettingsButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_Connection, _connectionButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_JoinToExistingLobby, _joinRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_CreateLobby, _createRoomButtonPictureAddressDefault, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
}

void PlayMenu::SetUpInitilButtonsStates()
{
    ui->btn_JoinToExistingLobby->setDisabled(true);
    ui->btn_CreateLobby->setDisabled(true);
}

void PlayMenu::closeEvent(QCloseEvent *event)
{
    emit sig_userIsClosingStartNewRoomWindow(true);
}
