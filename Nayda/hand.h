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
//#include <QApllication>


//defines of how many pixels to move the card on Hand upper to be ready for being played.
#define movingUpCardDelta 10


struct CardIsReadyToBePlayed {
    unsigned int cardID;
    SimpleCard card;

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




    const std::map<int, gameCardDoorMonster> *_monstersDeck;
    const std::map<int, gameCardDoorAmplifier> *_amplifiersDeck;
    const std::map<int, gameCardDoorCurse> *_cursesDeck;
    const std::map<int, gameCardDoorProfession> *_professionsDeck;
    const std::map<int, gameCardDoorRace> *_racesDeck;
    const std::map<int, gameCardDoorSpecialMechanic> *_specialMechanicsDeck;

    const std::map<int, gameCardTreasureArmor> *_armorDeck;
    const std::map<int, gameCardTreasureArmorAmplifier> *_armorAmplifiersDeck;
    const std::map<int, gameCardTreasureBattleAmplifier> *_battleAmplifiersDeck;
    const std::map<int, gameCardTreasureLevelUp> *_levelUpDeck;
    const std::map<int, gameCardTreasureSpecialMechanic> *_specialMechanicsTreasureDeck;
    const std::map<int, gameCardTreasureThingsAmplifiers> *_thingsAmplifiersDeck;
    const std::map<int, gameCardTreasureWeapon> *_weaponsDeck;



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

    void setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck);
    void setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck);
    void setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck);
    void setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck);
    void setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck);
    void setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck);
    void setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck);
    void setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck);
    void setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck);
    void setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck);
    void setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck);
    void setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck);
    void setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck);


public:

    void addNewCardToHands(SimpleCard card);


private:

    QTimer *_showCardsTimer;
    unsigned int _timeToShowTheCard = 100; //ms
    SimpleCard _currentCardToShowInCentre;
    PositionedCard _currentCardToShowNearItsPosition;
    std::vector<SimpleCard> _cardsOnHandsHandsWidgetProperty;



signals:

    void _showTheCard(PositionedCard card);
    void _hideTheCard(bool);

public slots:

    void _showTheCardInCentreSlot();

public:

    bool eventFilter(QObject *o, QEvent *e);

public slots:

    void _slotCardIsPreparedToBePlayedFromHand(unsigned int cardId);

signals:

    void _cardIsPreparedToBePlayed(unsigned int);

private:

    CardIsReadyToBePlayed _cardIsReadyToBePlayed;



};

#endif // HAND_H
