#include "Application/Before_The_Game/Before_The_Game.h"
#include "ui_Before_The_Game.h"
#include <QDesktopWidget>
#include <munchkinglobaldefines.h>



Before_The_Game::Before_The_Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Before_The_Game),
    newRoomDialog(new playMenu)
{
    ui->setupUi(this);

    newRoomDialog->hide();
    setUpGeometricRelations();
    setUpSignalsSlotsConnections();
}


Before_The_Game::~Before_The_Game()
{
    delete ui;
}


void Before_The_Game::dbg_switch_to_game_mode_button_pressed()
{
    emit dbg_switch_to_game_mode(true);
    emit dbg_the_game_begins(true);
    //emit update_game_options_card_stack_type(this->card_stack_mode);
    qDebug() << "Start with debug button. ONLY VIEW!!!!";
    //emit update_game
}


void Before_The_Game::dbg_start_the_game_with_default_settings()
{
    emit dbg_switch_to_game_mode(true);
    emit dbg_the_game_begins(true);
    //emit update_game_options_card_stack_type(this->card_stack_mode);
    qDebug() << "Start with debug button. DEFAULT SETTING ARE PROVIDED!!!!";
}


void Before_The_Game::slot_userHaveChangedServerSettings(serverSettings settings)
{
    emit sig_userHaveChangedServerSettings(settings);
}


void Before_The_Game::SlotSetUpConnection()
{
    emit SignalSetUpConnection();
}


void Before_The_Game::slot_sendTestDataToServer()
{
    emit sig_sendTestDataToServer();
}


void Before_The_Game::SlotApplyNewGameSettings(GameSettings settings)
{
    _gameSettings.applyNewSettings(settings);
    emit SignalUserHaveChagedGameSettigs(settings);
}

void Before_The_Game::SlotProcessServerQueryReplyData(ServerQueryReplyData data)
{
    emit SignalServerQueryReplyData(data);
}

void Before_The_Game::SlotProcessClientRoomCreationReplyData(ClientRoomCreationReplyData data)
{
    qDebug() << "NAY-0001: Processing SlotProcessClientRoomCreationReplyData";
    //parse
    if (data._connectionAllowed)
    {
        //if Ok emit close signal to PlayMenu
        //and emit Creation Signal for RoomCreationWaitingLobby
        qDebug() << "NAY-0001: RoomCreation Allowed!";
        emit SignalRoomCreationAllowed(data);
    }
    else
    {
        //if not Ok emit ErrorSignal to playMenu
        if (data._errors.incorrectSettings
            || data._errors.noFreeSlots
            || data._errors.rulesAreNotSupported)
        {
             qDebug() << "NAY-0001: RoomCreation Restricted!";
             qDebug() << "data._errors.incorrectSettings: " << data._errors.incorrectSettings;
             qDebug() << "data._errors.noFreeSlots: " << data._errors.noFreeSlots;
             qDebug() << "data._errors.rulesAreNotSupported: " << data._errors.rulesAreNotSupported;
             emit SignalRoomCreationForbidden(data);
        }
    }
}


GameSettings Before_The_Game::getGameSettings() const
{
    return _gameSettings;
}


void Before_The_Game::setGameSettings(const GameSettings &gameSettings)
{
    _gameSettings = gameSettings;
}


void Before_The_Game::setUpGeometricRelations()
{
    QRect HwScreenSize = QApplication::desktop()->screenGeometry();
    int HwScreenSizeWidth = HwScreenSize.width();
    int HwScreenSizeHeight = HwScreenSize.height();

    ui->About_Authors->setMaximumWidth(GeometricLimitations::beforeTheGameButtonsSize*HwScreenSizeWidth);
    ui->btn_Play->setMaximumWidth(GeometricLimitations::beforeTheGameButtonsSize*HwScreenSizeWidth);
    ui->Settings->setMaximumWidth(GeometricLimitations::beforeTheGameButtonsSize*HwScreenSizeWidth);
    ui->btnHide->setMaximumWidth(GeometricLimitations::beforeTheGameButtonsSize*HwScreenSizeWidth);

    setGeometry(0,0,
                static_cast<uint32_t> (HwScreenSizeWidth * GeometricLimitations::beforeTheGameWindowsSize),
                static_cast<uint32_t> (HwScreenSizeHeight * GeometricLimitations::beforeTheGameWindowsSize));

    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    QApplication::desktop()->availableGeometry()));

}


void Before_The_Game::setUpSignalsSlotsConnections()
{
    QObject::connect( ui->btnHide, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect (ui->btnHide, SIGNAL(clicked(bool)), this, SLOT(dbg_switch_to_game_mode_button_pressed()));

    QObject::connect(newRoomDialog, &playMenu::sig_userHaveChangedServerSettings, this, &Before_The_Game::slot_userHaveChangedServerSettings);
    QObject::connect(newRoomDialog, &playMenu::SignalUserHaveChangedGameSettings, this, &Before_The_Game::SlotApplyNewGameSettings);
    QObject::connect(newRoomDialog, &playMenu::SignalSetUpConnection, this, &Before_The_Game::SlotSetUpConnection);
    QObject::connect(newRoomDialog, &playMenu::sig_sendTestDataToServer, this, &Before_The_Game::slot_sendTestDataToServer);

    QObject::connect(ui->btn_Play, &QPushButton::clicked, newRoomDialog, &playMenu::show);
    QObject::connect(ui->btn_Play, &QPushButton::clicked, this, &Before_The_Game::hide);
    QObject::connect(newRoomDialog, &playMenu::sig_userIsClosingStartNewRoomWindow, this, &Before_The_Game::show);

    connect(newRoomDialog, &playMenu::sig_dbgBtnPlayWithDefaultsPressed, this, &Before_The_Game::dbg_start_the_game_with_default_settings);
    connect(newRoomDialog, &playMenu::sig_dbgBtnPlayWithDefaultsPressed, this, &Before_The_Game::hide);

    QObject::connect(this, &Before_The_Game::SignalServerQueryReplyData, newRoomDialog, &playMenu::SlotProcessServerQueryReplyData);
    QObject::connect(this, &Before_The_Game::SignalRemoteHostClosedErrorReport, newRoomDialog, &playMenu::SlotProcessRemoteHostClosedErrorReport);
    QObject::connect(this, &Before_The_Game::SignalRemoteHostNotFoundErrorReport, newRoomDialog, &playMenu::SlotProcessRemoteHostNotFoundErrorReport);
    QObject::connect(this, &Before_The_Game::SignalRemoteHostConnectionRefusedErrorReport, newRoomDialog, &playMenu::SlotProcessRemoteHostConnectionRefusedErrorReport);
    QObject::connect(this, &Before_The_Game::SignalUnclockConnectionButtonAfterConnection, newRoomDialog, &playMenu::SlotProcessUnlockConnectionButtonAfterConnection);
    QObject::connect(this, &Before_The_Game::SignalLockConnectionButtonWhileConnecting, newRoomDialog, &playMenu::SlotProcessLockingConnectionButtonWhileConnecting);
    QObject::connect(newRoomDialog, &playMenu::SignalSendClientRoomCreationRequest, this, &Before_The_Game::SlotSendClientRoomCreationRequest);

    QObject::connect(this, &Before_The_Game::SignalRoomCreationAllowed, newRoomDialog, &playMenu::close);
    QObject::connect(this, &Before_The_Game::SignalRoomCreationAllowed, this, &Before_The_Game::SlotCreateNewRoomCreationWaitingLobby);
    QObject::connect(this, &Before_The_Game::SignalRoomCreationForbidden, newRoomDialog, &playMenu::SlotProcessRoomCreationReplyError);
    QObject::connect(this, &Before_The_Game::SignalRoomCreationAllowed, this, &Before_The_Game::close);
    QObject::connect(this, &Before_The_Game::SignalAbortingConnectionByUserInitiative, newRoomDialog, &playMenu::SlotAbortingConnectionByUserInitiative);
    QObject::connect(newRoomDialog, &playMenu::SignalSendClientConnectionToRoomRequest, this, &Before_The_Game::SlotSendClientConnectionToRoomRequest);


}

void Before_The_Game::SlotCreateNewRoomCreationWaitingLobby()
{
    _roomCreationWaitingLobby = new RoomCreationWaitingLobby();
    _roomCreationWaitingLobby->show();
    _roomCreationWaitingLobby->SetUpInitalState(_gameSettings);
    QObject::connect(_roomCreationWaitingLobby, &RoomCreationWaitingLobby::SignalUserIsClosingRoomCreationLobby, newRoomDialog, &playMenu::show);
    QObject::connect(_roomCreationWaitingLobby, &RoomCreationWaitingLobby::SignalUserIsClosingRoomCreationLobby, this, &Before_The_Game::SlotAbortingConnectionByUserInitiative);
    QObject::connect(this, &Before_The_Game::SignalRemoteHostClosedErrorReport, _roomCreationWaitingLobby, &RoomCreationWaitingLobby::SlotProcessRemoteHostClosedErrorReport);
    QObject::connect(this, &Before_The_Game::SignalChartMessageReceived, _roomCreationWaitingLobby, &RoomCreationWaitingLobby::SlotProcessChartMessageReceived);
    QObject::connect(_roomCreationWaitingLobby, &RoomCreationWaitingLobby::SignalChartMessageToBeSend, this, &Before_The_Game::SlotProcessChartMessageSending);
    QObject::connect(this, &Before_The_Game::SignalServerReportsOpponentIsEnteringRoom, _roomCreationWaitingLobby, &RoomCreationWaitingLobby::SlotProcessServerReportsOpponentIsEnteringRoom);

}

void Before_The_Game::SlotProcessRemoteHostClosedErrorReport()
{
    qDebug() << "NAY-001: Processing HostClosedConnectionError!";
    emit SignalRemoteHostClosedErrorReport();
    _serverHadClosedConnectionWindow = new ServerHadClosedConnectionWindow(this);
    _serverHadClosedConnectionWindow->setModal(true);
    _serverHadClosedConnectionWindow->show();
}
