#ifndef CARDSINGAME_H
#define CARDSINGAME_H

#include <QWidget>
#include <Application/card.h>
#include <QPushButton>
#include "munchkinglobaldefines.h"



enum class CardsInGameWidgetMode {
    MainPlayer,
    SecondaryPlayer
};


namespace Ui {
class CardsInGame;
}

class CardsInGame : public QWidget
{
    Q_OBJECT

public:
    explicit CardsInGame(QWidget *parent = nullptr);
    ~CardsInGame();

private:
    Ui::CardsInGame *ui;

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

    void AddCardToCardsInGame(CardInGame card);

private:

    QString GetCardPictureAddress(SimpleCard card);

private:

    std::vector <CardInGame> _cardsInGameHolder;
    std::vector <SimpleCard> _disabledCards;
    std::vector <SimpleCard> _activeCards;

    std::vector <QPushButton* > _cardsAsButtonsRepresenter;

private:

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.12f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    uint32_t _windowSizeHeight;
    uint32_t _widnowSizeWidth;
    QSize    _mainWindowSize;

    void SetUpButtonPicture(QPushButton* const btn, const QString& picturePath, QSize size, bool active = true);

public:

    void SetUpMainWindowSize(QSize size) { _mainWindowSize = size;}

private:

    //Если карт больше, чем указанное число,
    //То карты начинают копиться во второй строке
    //Если произходйёт переполнение и второй строки,
    //Карты должн ыбудут добавляться по одной то в верхнюю строку, то в нижню.
    const uint32_t _maximumActiveCardsInLine = 5;

private:

    CardsInGameWidgetMode _mode = CardsInGameWidgetMode::MainPlayer;

public:

    void SetUpCardInGameWidgetMode(CardsInGameWidgetMode mode) { _mode = mode; }
};

#endif // CARDSINGAME_H
