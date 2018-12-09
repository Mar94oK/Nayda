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

#include "sellmenu.h"

#include "lastfoldobserver.h"

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
enum class GamePhase {
                        GameInitialization,
                        OtherPlayerMove,
                        StartOfTheMove,
                        Theft,
                        AfterOpenDoorNoMonster,
                        Battle,
                        Diplomacy,
                        WaitingForAnOpponentToMove,
                        HandAlignment,
                        CardProcessing,
                        AfterBattleWin,
                        AfterBattleLoose //запрещено подкидывать игроку что-нибудь, пока он разбирается с непотребством
                      };
//Фазы:
//Инициализация:
// В этой фазе игра запускается. Она длится до тех пор, пока не отрисуется анимация.
// Её завершением является SlotInitialAnimationCompleted(), который делает void The_Game::RealGameStart()
// После этого игра переходит в фазу StartOfTheMove,
// Где клиент проверяет, чей сейчас ход, и, в зависимости от этого переключает игру в фазу
// "Не свой ход" OtherPlayerMove или ведёт игрока (по сути, только своего клиента) далее, через фазы
// В фазе "Дипломатия" у всех игроков появляются дополнительные кнопки (принять помощь и своё специальное меню)
// При подключении игрока вор воремя дипломатии к бою, он перелючается во все остальные сопуствующие фазы
// Если его не выключат из игры картой
// Во всех остальных случаях игрок находится в фазе OtherPlayerMove, где набор его действий весьма ограничен


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



//===DECKS PROCESSING
    //Initial Decks;
    //Their exact values should be stored on the SERVER SIDE
    //07.12.2018
    //Нет никакой необходимости хранить их на сервере
    std::vector<SimpleCard> _treasuresDeck;
    std::vector<SimpleCard> _doorsDeck;

    std::vector<SimpleCard> _treasuresFold;
    std::vector<SimpleCard> _doorsFold;

signals:

    void SignalPassTheCardToTheFoldStack(SimpleCard card);
    void SignalEnableFoldProcessButton();
    void SignalDisableFoldProcessButton();
    void SignalCloseFoldObserver();

private:


    void AddCardToFoldStack(SimpleCard card);

    LastFoldObserver* _foldObserver = nullptr;
    void ProcessFoldObserver(const std::vector<SimpleCard> foldedCards);

    std::vector<SimpleCard> _lastFold;

//DECKS PROCESSING===



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

    void dbg_return_to_the_main_window();

public slots:

    void SlotShowTheCardInCentre(PositionedCard card);
    void SlotShowTheCardInGameInspector(PositionedCard card);

    void SlotHideTheCardInCentre(bool);

    
private:

    Ui::The_Game *ui;

    //special option will allow to be more than 5 opponents
    std::vector <GamerWidget*> _widgets4Opponents; //make as controlled unique_ptr;

    Player* _mainPlayer; // In common case might not be the ROOM Master.
    //This entity is responsible only for the mainWidget Selection.

    bool _isRoomMaster = false;
    void SetIsRoomMaster(bool master);
    bool GetIsRoomMaster() { return _isRoomMaster; }
    bool CheckIsMainPlayerTheRoomMaster(const QString& master)
    {return _mainPlayer->GetPlayersName() == master; }

    QString _roomMasterName;

    std::vector <Player*> _playersOpponents; //5 at all - Maximum according to current settings.

    std::vector <QString> _playersOrder; //The first one in this list is an actual MASTER!
    std::vector <Player*> _orderOfMove;
    std::map<uint32_t, GamerWidget*> _GamerWidgetsWithIDs;

    uint32_t _mainGamerOrderOfMove;
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
    GamePhase _storedGamePhase = GamePhase::GameInitialization;

    void SaveGamePhase() { _storedGamePhase = _currentGamePhase; }
    void RestoreGamePhase() { _currentGamePhase = _storedGamePhase; }

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


///////////////START THE GAME


    void SlotServerReportsTheGameIsAboutToStart(const TheGameIsAboutToStartData& data);
    void DEBUG_SlotWasPushedToGameMode();

    void RealGameStart();


//////////////START THE GAME



    void SlotProcessChartMessageReceived(const QStringList& message)
    { emit  SignalChartMessageReceived(message); }
    void SlotProcessChartMessageSending(const QString& message)
    { emit SignalChartMessageSending(message);}

//===SERVER-RELATED SIGNALS AND SLOTS
signals:

    void SignalChartMessageReceived(const QStringList& message);
    void SignalChartMessageSending(const QString& message);

    void SignalMainGamerHasSoldCards(TheGameMainGamerHasSoldCards data);

public slots:

    void SlotProcessOpponentHasSoldCards(TheGameMainGamerHasSoldCards data);
    void SlotRoomIdHasBeenChanged(uint32_t roomID) { _roomID = roomID; }
    void SlotRoomNameHasBeenChanged(QString roomName) { _roomName = roomName; }

private:

    RejectedCardMessage* _rejectionCardMessage;
    HandCardPointer* _handCardPointer;

private slots:

    void SlotShowTheRejectedCardMessage(PositionedCard);

private:

    void DEBUGPassTheCardToTheBattleField(PositionedCard);

    //moving to centre
    void Animation_StartPassSoldCardsFromHandToTreasureFold_Phase1(std::vector<PositionedCard> cards);
    //leaving at centre
    void Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2(std::vector<QPushButton *> movedCards, const std::vector<PositionedCard> &cards);
    //moving to treasures fold
    void Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3(std::vector<QPushButton *> movedCards, const std::vector<PositionedCard> &cards);


public:

    QString findTheCardPicture(SimpleCard);

    GameSettings gameSettings() const;
    void setGameSettings(const GameSettings &gameSettings);

private:

    GameSettings _gameSettings;

public slots:

    void SlotClientIsEnteringToRoom(const QString& name)
    { _playersOrder.push_back(name); }

    void SlotClientIsLeavingTheRoom(const QString& name);

    void SlotProcessServerReportsRoomHasChangedOwner(const QString& previousOwner, const QString& currentOwner);

signals:

    //NAY-002: ADD_LATER
    //Соединить этот сигнал со всплывающим окном об изменении мастера
    void SignalRoomHasChangedOwner(const QStringList& previousCurrentNames);


public slots:

    //Initializing cards and etc
    void SlotGameInitialization(TheGameIsAboutToStartData data);

    //The_Game should allways have correct settings
    void SlotSetUpGameSettings(const GameSettings& settings);

    void SlotInitialAnimationCompleted();

private:

    void FormingInitialDecks(const std::vector<uint32_t>& doorsVector,
                             const std::vector<uint32_t>& treasuresVector);

    void SetUpPlayersAndWidgets(uint32_t windowHeight, uint32_t windowWidth, const std::vector<QString>& playersOrder);
    void SetUpOpponents(uint32_t windowHeight, uint32_t windowWidth, const std::vector<QString>& opponents);
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

//Related to SellMenu:
private:

    SellMenu* _sellMenu = nullptr;
    std::vector<SimpleCard> _cardsAreReadyToBeSoldHolder;
    void RemoveCardFromCardsAreAbleToBeSold(SimpleCard card);

private:

    void RemoveTheCardFromHand(GamerWidget* wt, SimpleCard card);

signals:

    void SignalShowTradeButton();
    void SignalHideTradeButton();
    void SignalGetPostionedCard(SimpleCard card);



public slots:

    void SlotShowTradeMenu();
    void SlotHideTradeMenu();
    void SlotProcessCardsSelectedToBeSold(const std::vector<SimpleCard> cards);

private:

    std::vector<PositionedCard> _soldCards;
    std::vector<PositionedCard> GetPositionedCards(GamerWidget *wt, const std::vector<SimpleCard>& cards);
    void SoldProcess(const std::vector<PositionedCard>& soldCards);


public:

private slots:

    void SlotAddPlayedCardToTheBattleField(SimpleCard card);
    void SlotShowAllSoldCardsInCentre(const std::vector<SimpleCard> cards, uint32_t msTime);

//Game Processing entities
private:

    uint32_t _currentOpponentToMoveId = 0;
    QString  _currentOpponentToMoveName = "";


//===SELLPROCESS
private:

    bool CheckThePlayerIsAbleToSell(Player *player);
    uint32_t GetCardPrice(SimpleCard card);
    uint32_t GetLevelPurchased(uint32_t totalMoneySpent);

//SELLPROCESS===


    //В самом начале игра должна проверить, кто сейчас ходит.
    //Если ходит не главный игрок - для начальной проверки клиенту
    //не нужно получать от сервера дополнительных сообщений -
    //требуется сличить имя игрока из настроек с именем мастера.
    //Для всех последующих итераций сервер также стартует таймеры,
    //но только для того, чтобы по таймауту отключить игрока.
    //клиент же при молчании игрока делает ход сам (самый простой  - открывает дверь)
    //больше он не делает ничего.
    //сервер (по идее - сам поймёт, что клиент отключился).
    //т.к. произойти это может в любой момент времени,
    //клиент, получив подобное сообщение, должен сам произвести все действия, которые
    //за этим следуют.
    //По сути для клиента есть два состояния - "свой ход" и "не свой ход"
    //1. Сначала полностью отладить "свой ход" без противодействия /действия других игроков
    //2. Добавить воздействие других игроков "не свой ход"
    //3. Обеспечить корректные действия сервера по таймаутам -
    //   Сервер передаёт сообщения, по которым сменяются фазы.
    //   Клиенты в этот момент находятся в фазе "ожидание ответа сервера"
    //   Т.е. у главного клиента должен сработать "таймаут", он должен передать сообщение на сервер
    //   Не позднее, чем общее время хода игрока (или какое-нибудь другое время).
    //   Если клиент ничего не прислал, сервер должен выкинуть его по таймауту,
    //   Т.к. во всех остальных случаях клиент пришлёт репорт
    //   Если какой-нибудь клиент три раза подряд пришлёт "автоматический" ход
    //   Этот клиент будет автоматически отключен от сервера.


    void InitializeMainPlayerMove();
    void InitializeOpponentMove(const QString& opponentsName);

    //these functions are setting timers settings, since they are able to have normal settiungs
    //use them only after server's connection
    void StartMoveTimer();
    void StartPhaseTimer(GamePhase phase);

    QTimer * _moveTimer;
    QTimer * _phaseTimer;

    QTimer * _secondsMoveTimer;
    QTimer * _secondsPhaseTimer;

    uint32_t _secondsLeftMoveTimer = 0;
    uint32_t _secondsLeftPhaseTimer = 0;

    void InitializeTicksTimers();

    void InitializeMoveTimer();
    void InitializePhaseTimer();

private slots:

    //These slots are not set the intervals!
    //It will be done later.
    void SlotMoveTimerHandler();
    void SlotPhaseTimerHandler();

    void SlotSecondsMoveTimerHandler();
    void SlotSecondsPhaseTimerHandler();

private:

    uint32_t _roomID = ROOM_ID_NOT_DEFINED;
    QString  _roomName = "";

public:

    //Setting up coefficients
    constexpr static float koeff_GameField_size = 0.5f;

    constexpr static float koeff_GamerWidget_size_Height = (1 - koeff_GameField_size)/2;
    constexpr static float koeff_GamerWidget_size_Width = koeff_GameField_size/3;

    constexpr static float koeff_GameTimers_size_Height = koeff_GamerWidget_size_Height; // should be the same
    constexpr static float koeff_GameTimers_size_Width = koeff_GameField_size/3;
    constexpr static float koeff_GameInfoBox_size_Height = 0.66f; //why it is impossible 2/3???
    constexpr static float koeff_GameInfoBox_size_Width = (1 - koeff_GameField_size) / 2;

    GamePhase GetCurrentGamePhase() const;
    void SetCurrentGamePhase(const GamePhase &GetCurrentGamePhase);

//Visualization Engine
private:

//Positions are top left.
//Looks like will be used for only MainPlayer widget.
    QPoint GetMainGamerWidgetPostion();
    QPoint GetMainGamerHandPosition();
    QPoint GetCardsStackPosition();

    QPoint GetTreasuresFoldPosition();
    QPoint GetDoorsFoldPosition();
    QPoint GetTreasuresStackPosition();
    QPoint GetDoorsStackPosition();

    QPoint GetCenterPosition();

    QSize GetTreasuresFoldSize();
    QSize GetDoorsFoldSize();


//Settings not given in the settings Selection menu:
private:
    //Animation timings
    uint32_t _msTimeForTradeAnimationPhase1 = 1500; //Moving to centre
    uint32_t _msTimeForTradeAnimationPhase2 = 1500; //Standing at the centre
    uint32_t _msTimeForTradeAnimationPhase3 = 500;  //Moving to Treasure Fold



};

#endif // THE_GAME_H
