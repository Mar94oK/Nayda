#ifndef THE_GAME_H
#define THE_GAME_H

#include <QMainWindow>
#include "gamerwidget.h"

#include "Server/server.h"
#include "Application/player.h"
#include <map>
#include "Application/card.h"
#include <QFile>




#include <QPixmap>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QDebug>


#define PC_VERSION //begin with PC
#define DEBUG_MESSAGES //start with debug enabled
#define DEBUG_NO_SERVER

namespace Ui {
class The_Game;
}



struct strongAgainst {

    int strongAgainstHuman;
    int strongAgainstElf;
    int strongAgainstHalfling;
    int strongAgainstDwarf;
    int strongAgainstOrk;
    int strongAgainstGnome;
    int strongAgainstNoClass;
    int strongAgainstHalfBreed;
    int strongAgainstSuperMunchkin;
    int strongAgainstWoman;
    int strongAgainstWarrior;
    int strongAgainstWizard;
    int strongAgainstThief;
    int strongAgainstBard;
    int strongAgainstCleric;
    int strongAgainstSaturday;

};




struct isOnlyFor {

    bool isOnlyForGnome;
    bool isOnlyForDwarf;
    bool isOnlyForHuman;
    bool isOnlyForWizard;

    bool isRestrictedToGnome;
    bool isRestrictedToWizard;


};

struct isOnlyFor_ThingsAmplifiers {

    bool isOnlyForHalfling;
    bool isOnlyForCleric;
    bool isOnlyForWizard;
    bool isOnlyForThief;

    bool isRestrictedToWarrior;
    bool isRestrictedToCleric;
    bool isRestrictedtoThief;


};


struct isOnlyFor_Weapon {

    bool isOnlyForElf;
    bool isOnlyForMan;
    bool isOnlyForDwarf;
    bool isOnlyForHuman;
    bool isOnlyForWizard;
    bool isOnlyForWoman;
    bool isOnlyForWarrior;
    bool isOnlyForOrk;
    bool isOnlyForThief;
    bool isOnlyForHalfling;
    bool isOnlyForGnome;
    bool isOnlyForBard;
    bool isOnlyForCleric;


};







class The_Game :  public QMainWindow
{
    Q_OBJECT

public:
    explicit The_Game (QWidget *parent = 0);
    ~The_Game();

    //Ui::The_Game *getUi() const;

    void theMonstersParser(const QString& filename);
    gameCardDoorMonster monsterStringParser(const QString& monster_string);
    strongAgainst theMonsterStrongAgainstParser (const QString& strongAgainstString);

    void theAmplifiersParser(const QString& filename);
    gameCardDoorAmplifier amplifierStringParser (const QString& amplifier_string);

    void theCursesParser(const QString& filename);
    gameCardDoorCurse curseStringParser(const QString& curse_string);

    void theProfessionsParser(const QString& filename);
    gameCardDoorProfession professionStringParser(const QString& profession_string);

    void theRacesParser(const QString& filename);
    gameCardDoorRace racesStringParser(const QString& race_string);

    void theSpecialMechanicsParser(const QString& filename);
    gameCardDoorSpecialMechanic specialMechanicStringParser(const QString& specialMechanic_string);


    void theArmorsParser (const QString& filename);
    gameCardTreasureArmor armorsStringParser (const QString& armor_string);
    isOnlyFor TheArmorIsForParser (const QString& isFor_string);

    void theArmorAmplifiersParser (const QString& filename);
    gameCardTreasureArmorAmplifier armorAmplifierStringParser (const QString& armorAmplifier_string);

    void theBattleAmplifiersParser (const QString& filename);
    gameCardTreasureBattleAmplifier battleAmplifierStringParser(const QString& battleAmplifier_string);

    void theLevelUpParser (const QString& filename);
    gameCardTreasureLevelUp levelUpStringParser(const QString& levelUp_string);

    Additional_Request theAdditionalRequestParser (const QString& additionalRequest_string);
    Time_To_Use theTimeToUseParser (const QString& timeTouse_string);
    void theSpecialMechanicTreasureParser (const QString& filename);
    gameCardTreasureSpecialMechanic SpecialMechanicTreasureStringParser(const QString& specialMechanicsTreasure_string);


    isOnlyFor_ThingsAmplifiers TheThingsAmplifiersIsForParser (const QString& isFor_string);
    void theThingsAmplifiersParser (const QString& filename);
    gameCardTreasureThingsAmplifiers ThingsAmplifiersStringParser (const QString& thingsAmplifiers_string);

    isOnlyFor_Weapon TheWeaponIsForParser (const QString& isFor_string);
    void theWeaponParser (const QString& filename);
    gameCardTreasureWeapon WeaponStringParser (const QString& weapons_string);


    void showTheCards();
    void passMapsToBattleField();



    const std::map<int, gameCardDoorMonster> * monstersDeck();
    const std::map<int, gameCardDoorAmplifier> *amplifiersDeck();
    const std::map<int, gameCardDoorCurse> *cursesDeck();
    const std::map<int, gameCardDoorProfession> *professionsDeck();
    const std::map<int, gameCardDoorRace> *racesDeck();
    const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck();

    const std::map<int, gameCardTreasureArmor> *armorDeck();
    const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck();
    const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck();
    const std::map<int, gameCardTreasureLevelUp> *levelUpDeck();
    const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck();
    const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck();
    const std::map<int, gameCardTreasureWeapon> *weaponsDeck();



    //this process is responsible for giving cards to players, setting the Four Decks.
    //in the Debug Version the Game Holds controll on each and every card Stack Action;
    //remember to place prototypes for server-based functionality in all such places (where Cards Stack Action Takes place)
    //first, make the as commented strings, to provide funtionality further...

    //void initialCardsProcess();

    void givingCardsToPlayers();




signals:
    void dbg_to_be_shown(bool);
    void dbg_return_to_before_the_game(bool);

public slots:

    void dbg_was_pushed_to_game_mode();
    void dbg_return_to_the_main_window();

    
private:


    Ui::The_Game *ui;

    //game_settings
    int m_time_to_think;
    int m_time_for_move;
    unsigned int m_number_of_players;

    //special option will allow to be more than 5 opponents
    std::vector <GamerWidget*> opponents; //make as controlled unique_ptr;

    std::vector <player> _players_opponents; //5 at all
    player _main_player;


    //this stock depends on the Game Mode;
    //Nonetheless, it is allways the same through all the game, since its only function is
    //to store the whole amount of cards that can be played and to display them on widgets
    //The real card stock is the VECTOR!!! And it should never been stored on the client side
    //during debug stage it will be generated and stored alltogether in the game constructor

    //Game_Cards are filled inside the Game.cpp (constructor)

    //std::map <int, Game_Card> _basisStock;
    std::map <int, gameCardDoorMonster> _monstersDeck;
    std::map <int, gameCardDoorAmplifier> _amplifiersDeck;
    std::map <int, gameCardDoorCurse> _cursesDeck;
    std::map <int, gameCardDoorProfession> _professionsDeck;
    std::map <int, gameCardDoorRace> _racesDeck;
    std::map <int, gameCardDoorSpecialMechanic> _specialMechanicsDeck;

    std::map <int, gameCardTreasureArmor> _armorDeck;
    std::map <int, gameCardTreasureArmorAmplifier> _armorAmplifiersDeck;
    std::map <int, gameCardTreasureBattleAmplifier> _battleAmplifiersDeck;
    std::map <int, gameCardTreasureLevelUp> _levelUpDeck;
    std::map <int, gameCardTreasureSpecialMechanic> _specialMechanicsTreasureDeck;
    std::map <int, gameCardTreasureThingsAmplifiers> _thingsAmplifiersDeck;
    std::map <int, gameCardTreasureWeapon> _weaponsDeck;


};







#endif // THE_GAME_H
