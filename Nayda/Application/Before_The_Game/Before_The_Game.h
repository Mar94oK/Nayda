#ifndef BEFORE_THE_GAME_H
#define BEFORE_THE_GAME_H

#include <QMainWindow>
#include "Server/server.h"
#include <QDebug>
#include "playMenu.h"
#include "gamesettings.h"
#include "MessagesDefinitions.h"
#include "roomcreationwaitinglobby.h"
#include "serverhadclosedconnectionwindow.h"
#include "roomcreationwaitinglobby.h"
#define DEBUG_MESSAGES



enum class StateOfBeforeTheGame
{
    InitialMenu,
    PlayMenu,
    RoomCreationWaitingLobby,
    GameInProgress
};


namespace Ui {
class Before_The_Game;
}

class Before_The_Game :  public QMainWindow
{
    Q_OBJECT

public:

    explicit Before_The_Game (QWidget *parent = 0);
    ~Before_The_Game();
    Ui::Before_The_Game *getUi() const;

    GameSettings getGameSettings() const;
    void setGameSettings(const GameSettings &gameSettings);

signals:

    void dbg_switch_to_game_mode(bool);
    void dbg_the_game_begins(bool);

    void update_game_options_number_of_players (int number_of_players);
    void update_game_options_ (int game_type);
    void update_game_options_card_stack_type (int card_stack_type);

    void start_game_with_default_settings(bool);
    void sig_userHaveChangedServerSettings(serverSettings);
    void SignalSetUpConnection();
    void sig_sendTestDataToServer();

    void SignalUserHaveChagedGameSettigs(const GameSettings&);

    void SignalServerQueryReplyData(ServerQueryReplyData data);

    void SignalRoomCreationAllowed(ClientRoomCreationReplyData data);
    void SignalRoomCreationForbidden(ClientRoomCreationReplyData data);

    void SignalRemoteHostClosedErrorReport();
    void SignalRemoteHostConnectionRefusedErrorReport();
    void SignalRemoteHostNotFoundErrorReport();

    void SignalLockConnectionButtonWhileConnecting();
    void SignalUnclockConnectionButtonAfterConnection();

    void SignalSendClientRoomCreationRequest();

    void SignalAbortingConnectionByUserInitiative();

    void SignalServerReportsOpponentIsEnteringRoom(const QString& opponentName);

    void SignalChartMessageReceived(const QStringList& message);
    void SignalChartMessageSending(const QString& message);

    void SignalSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data);

    void SignalServerQueryOversize();

    void SignalUpdateQueryOrder(uint32_t queryOrder);
    void SignalUpdateQuerySize(uint32_t querySize);

    void SignalProcessServerRoomChangesInSelectableList(const ServerRoomReadyToConnectData& data );
    void SignalProcessClientWantedToEnterTheRoom(uint32_t roomId);

public slots:

    void dbg_switch_to_game_mode_button_pressed(void);
    void dbg_start_the_game_with_default_settings(void);
    void slot_userHaveChangedServerSettings(serverSettings settings);
    void SlotSetUpConnection();
    void slot_sendTestDataToServer();
    void SlotApplyNewGameSettings(GameSettings settings);

    void SlotProcessServerQueryReplyData(ServerQueryReplyData data);
    void SlotProcessClientRoomCreationReplyData(ClientRoomCreationReplyData data);

    void SlotSendClientRoomCreationRequest() { emit SignalSendClientRoomCreationRequest(); }

    void SlotCreateNewRoomCreationWaitingLobby();

    void SlotAbortingConnectionByUserInitiative() {emit SignalAbortingConnectionByUserInitiative(); }

    void SlotProcessServerReportsOpponentIsEnteringRoom(const QString& opponentName)
    { emit SignalServerReportsOpponentIsEnteringRoom(opponentName); }

    void SlotProcessChartMessageReceived(const QStringList& message)
    { emit  SignalChartMessageReceived(message); }

    void SlotProcessChartMessageSending(const QString& message)
    { emit SignalChartMessageSending(message);}

    void SlotSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data)
    {
        emit SignalSendClientConnectionToRoomRequest(data);
    }

    void SlotProcessClientWantedToEnterTheRoom(uint32_t roomId)
    { emit SignalProcessClientWantedToEnterTheRoom(roomId); }

    void SlotServerQueryOversize() { emit SignalServerQueryOversize(); }

    //in fact, it report to gui if only eberything is ok and there are rooms, and it is necessary to show
    void SlotProcessClientConnectionToRoomReply(ClientConnectionToRoomReplyData data);
    void SlotProcessUpdateQueryOrder(ClientConnectionToRoomReplyData data);

    void SlotProcessServerRoomChangesInSelectableList(const ServerRoomReadyToConnectData& data)
    { emit SignalProcessServerRoomChangesInSelectableList(data); }

//error processing
    void SlotProcessRemoteHostClosedErrorReport();
    void SlotProcessRemoteHostConnectionRefusedErrorReport() { emit SignalRemoteHostConnectionRefusedErrorReport();
                                                             qDebug() << "NAY-001: RemoteHostConnectionRefusedError()! ";}
    void SlotProcessRemoteHostNotFoundErrorReport() { emit SignalRemoteHostNotFoundErrorReport(); }

    void SlotProcessConnectionButtonLockingWhileConnecting() { emit SignalLockConnectionButtonWhileConnecting();
                                                                qDebug() << "Locking the button! "; }
    void SlotProcessUnlockConnectionButtonAfterConnection() { emit SignalUnclockConnectionButtonAfterConnection();
                                                                qDebug() << "Unlocking the Button! "; }




private:

    Ui::Before_The_Game *ui;
    Server* m_server_ptr;

    GameSettings _gameSettings;
    playMenu* newRoomDialog;

    RoomCreationWaitingLobby* _roomCreationWaitingLobby = nullptr;
    ServerHadClosedConnectionWindow* _serverHadClosedConnectionWindow = nullptr;
    RoomSelectionLobby* _roomSelectionLobby = nullptr;

    uint32_t roomID = ROOM_ID_NOT_DEFINED;

private:

    void setUpGeometricRelations();
    void setUpSignalsSlotsConnections();


};

#endif // BEFORE_THE_GAME_H
