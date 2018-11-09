#include "System_Manager/system_manager.h"


SystemManager::SystemManager(Before_The_Game * beforeTheGame,
                               Server * server, The_Game * theGame)
{
    m_beforeTheGamePtr = beforeTheGame;
    m_serverPtr = server;
    m_theGamePtr = theGame;
    
    //QObject::connect((m_before_the_game_ptr->getUi()));
    QObject::connect(m_beforeTheGamePtr, SIGNAL(dbg_switch_to_game_mode(bool)),
                     m_theGamePtr, SLOT(dbg_was_pushed_to_game_mode()));
    QObject::connect(m_theGamePtr, SIGNAL(dbg_return_to_before_the_game(bool)),m_beforeTheGamePtr, SLOT(show()));
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

}
