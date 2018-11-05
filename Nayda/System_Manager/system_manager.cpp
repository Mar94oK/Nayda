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
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::sig_openRoomForConnection, m_serverPtr, &Server::slot_openConnection);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::sig_sendTestDataToServer, m_serverPtr, &Server::slot_sendTestDataToServer);
    QObject::connect(m_serverPtr, &Server::SignalServerHasChangedGameSettings, m_beforeTheGamePtr, &Before_The_Game::SlotApplyNewGameSettings);
    QObject::connect(m_beforeTheGamePtr, &Before_The_Game::SignalUserHaveChagedGameSettigs, m_serverPtr, &Server::SlotUserHaveChangedGameSettings);

}
