#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>
#include <serversettings.h>
#include <Server/server.h>
#include <gamesettingswindow.h>
#include <gamesettings.h>
#include <MessagesDefinitions.h>
#include "connectiontoroomquestions.h"
#include "connectiontoroomrejectedmessagewindow.h"
#include "serverqueryoversizedwindow.h"
#include "roomselectionlobby.h"

namespace Ui {
class startNewRoom;
}

enum class ConnectionState { NoServerSettingsProvided,
                             CompleteServerSettings,
                             Connection,
                             ConnectionTimeout };

class playMenu : public QWidget
{
    Q_OBJECT

private:

    Ui::startNewRoom *ui;
    ServerSettings* serverSettingsWindow = nullptr;
    GameSettingsWindow* gameSettingsWindow = nullptr;
    ConnectionToRoomQuestions* connectionToRoomQuestions = nullptr;
    ConnectionToRoomRejectedMessageWindow* connectionRejected = nullptr;
    ServerQueryOversizedWindow* serverQueryOversized = nullptr;

    void closeEvent(QCloseEvent *event);

    QString _gameSettingsButtonPictureAddressDefault;
    QString _gameSettingsButtonPictureAddressSetUp;

    QString _connectionButtonPictureAddressDefault;
    QString _connectionButtonPictureAddressSetUp;
    QString _connectionButtonPictureAddressConnected;

    QString _createRoomButtonPictureAddressDefault;
    QString _createRoomButtonPictureAddressAllowed;

    QString _joinRoomButtonPictureAddressDefault;
    QString _joinRoomButtonPictureAddressAllowed;

    std::vector<QPushButton*> _uiButtons;

private:

    const double buttonsWidthCoefficient = 0.2;
    const double buttonsHeightWidthRelatio = 0.66;

private:

    ConnectionState _connectionState;
    GameSettings    _gameSettings;
    serverSettings  _serverSettings;

private:

    QString _roomCreationLobbyBaseText = "Создать новый зал!";

public:

    explicit playMenu(QWidget *parent = 0);
    ~playMenu();

signals:

    void sig_dbgBtnPlayWithDefaultsPressed(bool);
    void sig_userIsClosingStartNewRoomWindow(bool);
    void sig_userHaveChangedServerSettings(serverSettings settings);
    void SignalSetUpConnection();
    void sig_sendTestDataToServer();

    void SignalUserHaveChangedGameSettings(const GameSettings&);

    void SignalSendClientRoomCreationRequest();

    void SignalSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data);
    void SignalLockUserButtonsWhileConnnectingToRoom();

private slots:

    void SlotShowRoomConnectionQuestions();
    void SlotSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data);



public slots:

    void slot_startGameWithDefaults(void);
    void SlotShowServerSettings(void);
    void SlotUserHaveChangedServerSettings(serverSettings settings);
    void SlotSetUpConnection();
    void slot_sendTestDataToServer();
    void SlotShowGameSettingsWindow();
    void SlotUserHaveChangedGameSettings(const GameSettings& settings);

    void SlotProcessServerQueryReplyData(ServerQueryReplyData data);

    void SlotSendClientRoomCreationRequest() { emit SignalSendClientRoomCreationRequest(); }

    void SlotAbortingConnectionByUserInitiative();

    void SlotShowConnectionToRoomRejectedWindow(bool noRooms);
    void SlotShowServerQueueOversizedWindow();

    void SlotUnlockUserButtonsAfterConnectingToRoomReply();
    void SlotLockUserButtonsWhileConnnectingToRoom();

//erorrs processing

    void SlotProcessRemoteHostClosedErrorReport();
    void SlotProcessRemoteHostConnectionRefusedErrorReport();
    void SlotProcessRemoteHostNotFoundErrorReport();

    void SlotProcessLockingConnectionButtonWhileConnecting();
    void SlotProcessUnlockConnectionButtonAfterConnection();

    void SlotProcessRoomCreationReplyError(ClientRoomCreationReplyData data);

private:

    void setUpUiGeometricRelations();
    void setUpSignalsSlotsConnections();
    void setUpUiPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);
    void setUpUiVisualizationParameters();
    void SetUpInitilButtonsStates();


};

#endif // START_NEW_ROOM_H
