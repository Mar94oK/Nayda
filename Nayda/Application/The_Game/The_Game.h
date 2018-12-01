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

#include "popupcard.h"
#include "trianglecardpointer.h"
#include "rejectedcardmessage.h"
#include "handcardpointer.h"

#include "gamesettings.h"

#include <QPropertyAnimation>
#include <QAbstractAnimation>

#include "MessagesDefinitions.h"

#define PC_VERSION //begin with PC
#define DEBUG_MESSAGES //start with debug enabled
#define DEBUG_NO_SERVER
#define DEBUG_NO_DIALOG
#define DEBUG_NO_RETURN_TO_MENU

//Fake commit

//These definitions are ruling the Widgets of Gamers (the areas for them)
#define MainGamerWidgetWidthExpansion 0.2
#define SecondaryGamerWidgetWidthExpansion 0.05


//For the Diplomacy there should be another timer.
enum class GamePhase {  GameInitialization,
                        StartOfTheMove,
                        Theft,
                        AfterOpenDoorNoMonster,
                        Battle,
                        Diplomacy,
                        WaitingForAnOpponentToMove,
                        HandAlignment,
                        CardProcessing
                      };

//Таймеров всего четыре:
//1. Общий таймер на ход
//2. Таймер "подумать"  - время на размышления персонажа перед ходом - открывать дверь, воровать, продавать, и т. д.
// Во время действия этого таймера оппоненты не могут предпринимать никаких (!) враждебных действий.
// По истечении этого времени решение будет принято автоматически - это всегда "открытие следующей карты"
//3. Таймер дипломатии - максимальное время, котрое даётся игроку на принятие/непринятие помощи.
//   По желанию игрока эта фаза может быть полностью пропущена.
//
//4. Таймер для принятия решения оппонентами - (пусть будет 3 секунды).
//Это время, которое даётся оппонентам, чтобы попытаться помешать игроку победить после того, как он побеждает.
//Запускается автоматически(? или по нажатию кнопки) после того, как сила игрока первышает силу монстра.




namespace Ui
{
class The_Game;
}

struct strongAgainst
{
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

struct isOnlyFor
{
    bool isOnlyForGnome;
    bool isOnlyForDwarf;
    bool isOnlyForHuman;
    bool isOnlyForWizard;

    bool isRestrictedToGnome;
    bool isRestrictedToWizard;

};

struct isOnlyFor_ThingsAmplifiers
{
    bool isOnlyForHalfling;
    bool isOnlyForCleric;
    bool isOnlyForWizard;
    bool isOnlyForThief;
    bool isRestrictedToWarrior;
    bool isRestrictedToCleric;
    bool isRestrictedtoThief;
};

struct isOnlyFor_Weapon
{
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

    void _debugShowAllTheCards();
    void PassDecksToBattleField();
    void passDecksToPlayerWidgets();
    void PassDecksToPopUpCardWidget();
    void PassDecksToCardsStacksWidget();
    void PassDecksToCardsInspectorWidget();

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


    //Initial Decks;
    //Their exact values should be stored on the SERVER SIDE
    std::vector<SimpleCard> _treasuresDeck;
    std::vector<SimpleCard> _doorsDeck;

    std::vector<SimpleCard> _treasuresFold;
    std::vector<SimpleCard> _doorsFold;

    //this process is responsible for giving cards to players, setting the Four Decks.
    //in the Debug Version the Game Holds controll on each and every card Stack Action;
    //remember to place prototypes for server-based functionality in all such places (where Cards Stack Action Takes place)
    //first, make the as commented strings, to provide funtionality further...

    //void initialCardsProcess();

    //This process should take place on the Server Side.
    //Instead of forming an exact array of digits here, the Server should pass them one-by-one on clients requests..
    //But for now, in Debug version, the procedure is executed on the clients' side.

    //SERVREW
    void DEBUGformingInitialDecks();

    unsigned int randUnsignedInt(unsigned int low, unsigned int high);

    //SERVREW
    //this method also sets the cards values (how many left in the deck)
    void GivingCardsToPlayers();

    void ShowInitialCardsOnHands();

    unsigned int treasuresLeft() const;
    void setTreasuresLeft(unsigned int treasuresLeft);

    unsigned int doorsLeft() const;
    void setDoorsLeft(unsigned int doorsLeft);

signals:
    void DEBUG_SignalToBeShown(bool);
    void DEBUG_ReturnToBeforeTheGame(bool);

public slots:

    void DEBUG_SlotWasPushedToGameMode();
    void dbg_return_to_the_main_window();

public slots:

    void SlotShowTheCardInCentre(PositionedCard card);
    void SlotShowTheCardInGameInspector(PositionedCard card);
    //void showTheCardNearItsPosition(PositionedCard card);
    void SlotHideTheCardInCentre(bool);
    //void hideTheCardNearItsPosition(bool);
    
private:

    Ui::The_Game *ui;

    //special option will allow to be more than 5 opponents
    std::vector <GamerWidget*> _widgets4Opponents; //make as controlled unique_ptr;

    Player _mainPlayer; // In common case might not be the ROOM Master.
    //This entity is responsible only for the mainWidget Selection.

    Player _opponent0;
    Player _opponent1;
    Player _opponent2;
    Player _opponent3;
    Player _opponent4;

    std::vector <Player> _playersOpponents; //5 at all - Maximum according to current settings.

    std::vector <QString> _playersOrder; //The first one in this list is an actual MASTER!
    //This entity is expected to be initialized before any action.

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

private:

    PopUpCard* _popUpCardWidget;

    TriangleCardPointer* _cardPointer;

private:

    unsigned int _treasuresLeft;
    unsigned int _doorsLeft;

private:

    GamePhase _currentGamePhase = GamePhase::GameInitialization;

public slots:

    void SlotAdjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace();
    void SlotCheckThePossibilityForTheCardToBePlayed(PositionedCard card);

signals:

    //looks like it is only the Hand from where the card can be played
    //there are some sepecial functions, like Theft or upcoming from the cards,
    //but all of them are targeted the cards to be fold or to be given to another Players.
    //Not To Be Played! (at least, as how it looks for me now, this moment)
    void SignalCardIsRejectedToBePlayed(bool); //not necessary to send the card back;
                                          //the Hand property "CardIsReadyToBePlayed" is saving the current card;


//ServerRelated
public slots:

    void SlotServerReportsTheGameIsAboutToStart(const TheGameIsAboutToStartData& data);
    void SlotProcessChartMessageReceived(const QStringList& message)
    { emit  SignalChartMessageReceived(message); }
    void SlotProcessChartMessageSending(const QString& message)
    { emit SignalChartMessageSending(message);}

//ServerRelated
signals:

    void SignalChartMessageReceived(const QStringList& message);
    void SignalChartMessageSending(const QString& message);

private:

    RejectedCardMessage* _rejectionCardMessage;
    HandCardPointer* _handCardPointer;

private slots:

    void SlotShowTheRejectedCardMessage(PositionedCard);

private:

    void PassTheCardToTheBattleField(PositionedCard);

public:

    QString findTheCardPicture(SimpleCard);

    GameSettings gameSettings() const;
    void setGameSettings(const GameSettings &gameSettings);

private:

    GameSettings _gameSettings;

public slots:

    //Initializing cards and etc
    void SlotGameInitialization(TheGameIsAboutToStartData data);

    //The_Game should allways have correct settings
    void SlotSetUpGameSettings(const GameSettings& settings);

    void SlotInitialAnimationCompleted()
    { _currentGamePhase = GamePhase::StartOfTheMove; }

private:

    void FormingInitialDecks(const std::vector<uint32_t>& doorsVector,
                             const std::vector<uint32_t>& treasuresVector);

    void RedrawGUIAccordingToCurrentSettings(uint32_t windowHeight, uint32_t windowWidth);
    void SetUpOpponents(uint32_t windowHeight, uint32_t windowWidth);
    void SetUpWidgetsProperties(uint32_t windowHeight, uint32_t windowWidth);
    void MainParser();


//Set-up Signal-Slots Connections
    void SetUpSignalSlotsConnections();



    void InitializePopUpWidgets();
    void SetUpBackgroundPicture();
    void PassCardsToWidgets();

//Game Process
//Процесс раздачи карт могут проводить клиенты, т.к. каждый клиент знает,
//какие карты и в какой послеовательности лежат в колоде.
//Требуется передавать через сервер только сыгранную карту.
//Общий алгоритм определяется следующим образом:
//Игрок нажимает на карту. Игра проверяет, можно ли её сыграть в настоящий момент.
//Если нет - карта возвращается на место (можно ничего не сообщать об этом).
//Если да - карта разыгрывается
//          карта передаётся на сервер
//          события по карте должны отражаться в графическом интерфейсе

    bool CheckTheCardIsPossibleToBePlayed(SimpleCard card);

signals:

    void SignalTheCardWasPlayed(SimpleCard card);

public:

private slots:

    void SlotAddPlayedCardToTheBattleField(SimpleCard card);

//Game Processing entities
private:

    uint32_t _currentOpponentToMoveId = 0;
    QString  _currentOpponentToMoveName = "";

private:

    bool CheckThePlayerIsAbleToSell(const Player &player);





private:

    uint32_t _roomID = ROOM_ID_NOT_DEFINED;

public:

    //Setting up coefficients
    constexpr static float koeff_GameField_size = 0.5f;

    constexpr static float koeff_GamerWidget_size_Height = (1 - koeff_GameField_size)/2;
    constexpr static float koeff_GamerWidget_size_Width = koeff_GameField_size/3;

    constexpr static float koeff_GameTimers_size_Height = koeff_GamerWidget_size_Height; // should be the same
    constexpr static float koeff_GameTimers_size_Width = koeff_GameField_size/3;
    constexpr static float koeff_GameInfoBox_size_Height = 0.66f; //why it is impossible 2/3???
    constexpr static float koeff_GameInfoBox_size_Width = (1 - koeff_GameField_size) / 2;

};

#endif // THE_GAME_H
