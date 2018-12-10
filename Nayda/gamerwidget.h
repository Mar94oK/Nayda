#ifndef GAMERWIDGET_H
#define GAMERWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>

#include "Application/card.h"
#include <QTimer>

#include "munchkinglobaldefines.h"
#include "cardsingameobserver.h"

#define DEBUG_GAMER_WIDGET

namespace Ui {
class GamerWidget;
}

class GamerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GamerWidget(QWidget *parent = 0);
    ~GamerWidget();

    bool is_MainPlayer() const;
    void setIs_MainPlayer(bool is_MainPlayer);
    void RedrawAsASecondaryPlayer();

    void SetDecks(const AllDecksToBePassed &data);

private:

    Ui::GamerWidget *ui;
    bool _isMainPlayer;
    bool _isRoomMaster;

    CardsInGameObserver* _cardsInGameObserver = nullptr;



public:

    void SetIsRoomMaster();

    std::map<int, gameCardDoorMonster> _monstersDeck;
    std::map<int, gameCardDoorAmplifier> _amplifiersDeck;
    std::map<int, gameCardDoorCurse> _cursesDeck;
    std::map<int, gameCardDoorProfession> _professionsDeck;
    std::map<int, gameCardDoorRace> _racesDeck;
    std::map<int, gameCardDoorSpecialMechanic> _specialMechanicsDeck;

    std::map<int, gameCardTreasureArmor> _armorDeck;
    std::map<int, gameCardTreasureArmorAmplifier> _armorAmplifiersDeck;
    std::map<int, gameCardTreasureBattleAmplifier> _battleAmplifiersDeck;
    std::map<int, gameCardTreasureLevelUp> _levelUpDeck;
    std::map<int, gameCardTreasureSpecialMechanic> _specialMechanicsTreasureDeck;
    std::map<int, gameCardTreasureThingsAmplifiers> _thingsAmplifiersDeck;
    std::map<int, gameCardTreasureWeapon> _weaponsDeck;

    std::map<int, gameCardDoorMonster> :: const_iterator  _monstersIterator;
    std::map<int, gameCardDoorAmplifier> :: const_iterator _amplifiersIterator;
    std::map<int, gameCardDoorCurse> :: const_iterator _cursesIterator;
    std::map<int, gameCardDoorProfession> :: const_iterator _professionsIterator;
    std::map<int, gameCardDoorRace> :: const_iterator _racesIterator;
    std::map<int, gameCardDoorSpecialMechanic> :: const_iterator _specialMechanicsIterator;

    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

public:

    void passCardsDecksToHandsWidget();
    void addTheCardToHandsWidget(SimpleCard card);

    bool eventFilter(QObject *o, QEvent *e);

private:

    unsigned int _totalDoorsOnHands = 0;
    unsigned int _totalTreasuresOnHands = 0;

private:

    QTimer *_showCardsTimer;
    unsigned int _timeToShowTheCard = 100; //ms
    SimpleCard _currentCardToShowInCentre;
    PositionedCard _currentCardToShowNearItsPosition;

    std::vector<SimpleCard> _cardsOnHandsGamerWidgetProperty;
    std::vector<SimpleCard> _cardsRacesClassesGamerWidgetProperty;
    std::vector<SimpleCard> _cardsInGameWidgetGamerProperty;

signals:

    void SignalRepresentTheCardInCentre(PositionedCard);
    void SignalHideTheCardInCentre(bool);

public slots:

    void SlotRepresentTheCardInCentre();
    void SlotRepresentTheCardFromHandsInCentre(PositionedCard);
    void SlotHideTheCardInCentre(bool);

private:
#ifndef USE_RESOURCES
    std::vector<QString> _levelsPictures = {{"Pictures/levels/match1_transparent.png"},
                                            {"Pictures/levels/match2_transparent.png"},
                                            {"Pictures/levels/match3_transparent.png"},
                                            {"Pictures/levels/match4_transparent.png"},
                                            {"Pictures/levels/match5_transparent.png"},
                                            {"Pictures/levels/match6_transparent.png"},
                                            {"Pictures/levels/match7_transparent.png"},
                                            {"Pictures/levels/match8_transparent.png"},
                                            {"Pictures/levels/match9_transparent.png"},
                                            {"Pictures/levels/match10_transparent.png"}};
#else
    std::vector<QString> _levelsPictures = {{":/Pictures/levels/match1_transparent.png"},
                                            {":/Pictures/levels/match2_transparent.png"},
                                            {":/Pictures/levels/match3_transparent.png"},
                                            {":/Pictures/levels/match4_transparent.png"},
                                            {":/Pictures/levels/match5_transparent.png"},
                                            {":/Pictures/levels/match6_transparent.png"},
                                            {":/Pictures/levels/match7_transparent.png"},
                                            {":/Pictures/levels/match8_transparent.png"},
                                            {":/Pictures/levels/match9_transparent.png"},
                                            {":/Pictures/levels/match10_transparent.png"}};
#endif

    int _gamerLevel = 1;

public slots:

    void SlotChangeTheGamerLevel(int levelDelta);

private:

    //setup the koefficients;
    const float _race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float _race_class_btn_size_width = 0.035f;
    const float _race_class_btn_size_height = _race_class_btn_size_geometric_width_to_height_ratio*_race_class_btn_size_width;

private:

    QTimer* _testTimer;
    bool _testBtnIsPressed = false;

private slots:

    void DEBUGSlotTestGamerLevels();
    void DEBUGSlotStartTestCards();

private:

    int _battlePower = 1;

#ifndef USE_RESOURCES
    std::vector<QString> _battlePowerPictures = {{"Pictures/battlePowers/BattlePower_1.png"},
                                                 {"Pictures/battlePowers/BattlePower_2.png"},
                                                 {"Pictures/battlePowers/BattlePower_3.png"},
                                                 {"Pictures/battlePowers/BattlePower_4.png"},
                                                 {"Pictures/battlePowers/BattlePower_5.png"},
                                                 {"Pictures/battlePowers/BattlePower_6.png"},
                                                 {"Pictures/battlePowers/BattlePower_7.png"}};
#else
    std::vector<QString> _battlePowerPictures = {{":/Pictures/battlePowers/BattlePower_1.png"},
                                                 {":/Pictures/battlePowers/BattlePower_2.png"},
                                                 {":/Pictures/battlePowers/BattlePower_3.png"},
                                                 {":/Pictures/battlePowers/BattlePower_4.png"},
                                                 {":/Pictures/battlePowers/BattlePower_5.png"},
                                                 {":/Pictures/battlePowers/BattlePower_6.png"},
                                                 {":/Pictures/battlePowers/BattlePower_7.png"}};
#endif

public slots:

    void SlotChangeTheGamerBattlePower(int battlePowerDelta);

private slots:

    void DEBUGSlotTestGamerBattlePower();

private:

    unsigned int _currentDeltaToBattlePower = 0;

public slots:

    void HideHandSecondaryPlayerWidget();
    void _adjustSizeSlot();

signals:

    void SignalAdjustSize(bool);

public slots:

    void SlotSendTheCardToTheGameCheck(PositionedCard card);

signals:

    void SignalSendTheCardToTheGameCheck(PositionedCard);

public slots:

    void SlotCardIsRejectedToBePlayed(bool);

signals:

    void SignalCardIsRejectedToBePlayed(bool);

//SellMenu-Related:

private:

    bool _isSecondaryPlayer = false;

signals:

   void SignalTradeButtonWasPressed();

public slots:

   void SlotHideTradeButton();
   void SlotShowTradeButton();

signals:

   void SignalReportPostionedCard(PositionedCard card);
   void SignalGetPositionedCard(SimpleCard card);

public slots:

   void SlotGetPositionedCard (SimpleCard card)
    { emit SignalGetPositionedCard(card); }

public:

   std::vector<PositionedCard> GetPositionedCards(const std::vector<SimpleCard> cards);
    void RemoveCardFromHand(SimpleCard card);

public:

   QPoint ProvideSelfPosition();
   QPoint ProvideHandPosition();
   void SetGamerName(const QString& gamerName);


};

#endif // GAMERWIDGET_H
