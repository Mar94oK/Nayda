#include "System_Manager/system_manager.h"


System_Manager::System_Manager(Before_The_Game * befr_the_game, 
                               Server * srvr, The_Game * the_game) {
    
    m_before_the_game_ptr = befr_the_game;
    m_server_ptr = srvr;
    m_the_game_ptr = the_game;
    
    //QObject::connect((m_before_the_game_ptr->getUi()));
    QObject::connect(m_before_the_game_ptr, SIGNAL(dbg_switch_to_game_mode(bool)),
                     m_the_game_ptr, SLOT(dbg_was_pushed_to_game_mode()));
    QObject::connect(m_the_game_ptr, SIGNAL(dbg_return_to_before_the_game(bool)),m_before_the_game_ptr, SLOT(show()));
    QObject::connect(m_before_the_game_ptr, SIGNAL(dbg_switch_to_game_mode(bool)),
                    m_server_ptr, SLOT(dbg_the_game_begins_state_received(bool)));

}
