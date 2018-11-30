#include "System_Manager/system_manager.h"


SystemManager::SystemManager(Before_The_Game * beforeTheGame,
                               Server * server, The_Game * theGame)
{
    m_beforeTheGamePtr = beforeTheGame;
    m_serverPtr = server;
    m_theGamePtr = theGame;
    
    //QObject::connect((m_before_the_game_ptr->getUi()));
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::DEBUG_SignalSwitchToGameMode, m_theGamePtr, &The_Game::DEBUG_SlotWasPushedToGameMode);
    QObject::connect(m_theGamePtr, &The_Game::DEBUG_ReturnToBeforeTheGame, m_beforeTheGamePtr, &Before_The_Game::show);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::sig_userHaveChangedServerSettings, m_serverPtr, &Server::slot_saveServerSettings);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalSetUpConnection, m_serverPtr, &Server::SlotSetUpConnection);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::sig_sendTestDataToServer, m_serverPtr, &Server::SlotSendTestDataToServer);
    QObject::connect(m_serverPtr, &Server::SignalServerHasChangedGameSettings, m_beforeTheGamePtr, &Before_The_Game::SlotApplyNewGameSettings);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalUserHaveChagedGameSettigs, m_serverPtr, &Server::SlotUserHaveChangedGameSettings);
    QObject::connect(m_serverPtr, &Server::SignalReportServerQueryReplyData, m_beforeTheGamePtr, &Before_The_Game::SlotProcessServerQueryReplyData);
    QObject::connect(m_serverPtr, &Server::SignalRemoteHostClosedErrorReport, m_beforeTheGamePtr, &Before_The_Game::SlotProcessRemoteHostClosedErrorReport);

    QObject::connect(m_serverPtr, &Server::SignalRemoteHostNotFoundErrorReport, m_beforeTheGamePtr, &Before_The_Game::SlotProcessRemoteHostNotFoundErrorReport);
    QObject::connect(m_serverPtr, &Server::SignalRemoteHostConnectionRefusedErrorReport, m_beforeTheGamePtr, &Before_The_Game::SlotProcessRemoteHostConnectionRefusedErrorReport);
    QObject::connect(m_serverPtr, &Server::SignalLockConnectionButtonWhileConnecting, m_beforeTheGamePtr, &Before_The_Game::SlotProcessConnectionButtonLockingWhileConnecting);
    QObject::connect(m_serverPtr, &Server::SignalUnlockConnectionButtonAfterConnection, m_beforeTheGamePtr, &Before_The_Game::SlotProcessUnlockConnectionButtonAfterConnection);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalSendClientRoomCreationRequest, m_serverPtr, &Server::SlotSendClientRoomCreationRequest);
    QObject::connect(m_serverPtr, &Server::SignalReportClientRoomCreationReplyData, m_beforeTheGamePtr, &Before_The_Game::SlotProcessClientRoomCreationReplyData);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalAbortingConnectionByUserInitiative, m_serverPtr, &Server::SlotCloseConnectionByUserInitiative);
    QObject::connect(m_serverPtr, &Server::SignalServerReportsOpponentIsEnteringRoom, m_beforeTheGamePtr, &Before_The_Game::SlotProcessServerReportsOpponentIsEnteringRoom);
    QObject::connect(m_serverPtr, &Server::SignalChartMessageReceived, m_beforeTheGamePtr, &Before_The_Game::SlotProcessChartMessageReceived);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalChartMessageSending, m_serverPtr, &Server::SlotSendChartMessage);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalSendClientConnectionToRoomRequest, m_serverPtr, &Server::SlotSendClientConnectionToRoomRequest);
    QObject::connect(m_serverPtr, &Server::SignalServerQueryOversize, m_beforeTheGamePtr, &Before_The_Game::SlotServerQueryOversize);
    QObject::connect(m_serverPtr, &Server::SignalProcessClientConnectionToRoomReply, m_beforeTheGamePtr, &Before_The_Game::SlotProcessClientConnectionToRoomReply);
    QObject::connect(m_serverPtr, &Server::SignalProcessServerRoomChangesInSelectableList, m_beforeTheGamePtr, &Before_The_Game::SlotProcessServerRoomChangesInSelectableList);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalProcessClientWantedToEnterTheRoom, m_serverPtr, &Server::SlotSendClientWantedToEnterTheRoom);
    QObject::connect(m_serverPtr, &Server::SignalProcessServerClientWantedToEnterTheRoomReply, m_beforeTheGamePtr, &Before_The_Game::SlotProcessServerClientWantedToEnterTheRoomReply);
    QObject::connect(m_serverPtr, &Server::SignalProcessServerReportsClientIsLeaving, m_beforeTheGamePtr, &Before_The_Game::SlotProcessServerReportsClientIsLeaving);
    QObject::connect(m_serverPtr, &Server::SignalProcessServerReportsRoomHasChangedOwner, m_beforeTheGamePtr, &Before_The_Game::SlotProcessServerReportsRoomHasChangedOwner);
    QObject::connect(m_serverPtr, &Server::SignalServerReportsTheGameIsAboutToStart, m_beforeTheGamePtr, &Before_The_Game::SlotServerReportsTheGameIsAboutToStart);

    //Set-Up Settings
    QObject::connect(m_serverPtr, &Server::SignalServerHasChangedGameSettings, m_theGamePtr, &The_Game::SlotSetUpGameSettings);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalUserHaveChagedGameSettigs, m_theGamePtr, &The_Game::SlotSetUpGameSettings);
    //Start The Game
    //From Before The Game, to be able to provide additional settings!
    //Ofcourse, I can give them form the Server, but it is not good idea as I suppose to store them there, at the server's side.
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalServerReportsTheGameIsAboutToStart, m_theGamePtr, &The_Game::SlotServerReportsTheGameIsAboutToStart);

    //Chart System
    QObject::connect(m_theGamePtr, &The_Game::SignalChartMessageSending, m_serverPtr, &Server::SlotSendChartMessage);
    QObject::connect(m_serverPtr, &Server::SignalChartMessageReceived, m_theGamePtr, &The_Game::SlotProcessChartMessageReceived);

}
