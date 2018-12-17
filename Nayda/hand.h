#ifndef HAND_H
#define HAND_H

#include <QWidget>
#include <QDesktopWidget>
#include <QRect>
#include <QPushButton>
#include "Application/card.h"
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QPoint>
#include <rejectedcardmessage.h>

//defines of how many pixels to move the card on Hand upper to be ready for being played.
#define movingUpCardDelta 10

struct CardIsReadyToBePlayed {
    unsigned int cardID;
    SimpleCard card;
    bool thereIsCardToBePulledDown = false;

};

namespace Ui {
class Hand;
}

class Hand : public QWidget
{
    Q_OBJECT

public:
    explicit Hand(QWidget *parent = 0);
    ~Hand();


signals:
    void cardIsPlayingByPlayer(bool);
    void cardIsReplacingByPlayer(bool);
    void cardIsFoldingByPlayer(bool);

public slots:




private:
    Ui::Hand *ui;
    std::vector<QPushButton*>_cardsVector;

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

    void SetDecks(const AllDecksToBePassed& data);

public:

    void addNewCardToHands(SimpleCard card);

private:

    QTimer *_showCardsTimer;
    uint32_t _timeToShowTheCard = 100; //ms
    SimpleCard _currentCardToShowInCentre;
    PositionedCard _currentCardToShowNearItsPosition;
    std::vector<SimpleCard> _cardsOnHandsHandsWidgetProperty;

#ifdef __linux__
    QTimer  *_debounceTimer;
    uint32_t _debounceTime = 500;

    void SlotDebounceTimerHandler()
    {
        qDebug() << "Inside SlotDebounceTimerHandler(): ";
        if (_showCardsTimer->isActive()) _showCardsTimer->stop();
        emit SignalHideTheCard(true);
    }
#endif

signals:

    void SignalShowTheCard(PositionedCard card);
    void SignalHideTheCard(bool);

public slots:

    void SlotShowTheCardInCentreSlot();

public:

    bool eventFilter(QObject *o, QEvent *e);

public slots:

    void SlotCardIsPreparedToBePlayedFromHand(unsigned int cardId);

signals:

    void SignalCardIsPreparedToBePlayed(unsigned int);

private:

    CardIsReadyToBePlayed _cardIsReadyToBePlayed;


signals:

    void adjustSize(bool);

    void SignalCardIsSendedToTheGameCheck(PositionedCard card);

public slots:

    void SlotCardIsRejectedToBePlayed(bool rejected);


public slots:

    void SlotRemoveCardFromHand(SimpleCard card);

public:

    PositionedCard GetCardPosition(SimpleCard card);
    std::vector<PositionedCard> GetPositionedCards(const std::vector<SimpleCard> &cards);

public slots:

    void SlotGetCardPostion(SimpleCard card)
    { emit SignalReportCardPosition(GetCardPosition(card));}

signals:

    void SignalReportCardPosition(PositionedCard card);

public:

    QSize ProvideCardSize();

private:

    QSize _cardSize;

};

#endif // HAND_H
