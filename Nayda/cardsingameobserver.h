#ifndef CARDSINGAMEOBSERVER_H
#define CARDSINGAMEOBSERVER_H

#include <QWidget>
#include <QLabel>
#include <Application/card.h>
#include <QPushButton>

namespace Ui {
class CardsInGameObserver;
}

class CardsInGameObserver : public QWidget
{
    Q_OBJECT

public:
    //Due to cards-set-up mode, decks of this widget should be passed a little bit later then constructor.
    explicit CardsInGameObserver(QSize mainWindowSize,
                                 const QString& playerName,
                                 QWidget *parent = 0);
    ~CardsInGameObserver();

private:
    Ui::CardsInGameObserver *ui;


private:

    QString _widgetName = "Карты на руке";
    QString _playerName = "";


    std::vector <CardInGame> _cardsInGameHolder;
    std::vector <SimpleCard> _disabledCards;
    std::vector <SimpleCard> _activeCards;

    std::vector <QPushButton* > _cardsAsButtonsRepresenter;

private:

    void RemoveCardFromDisabledCards(SimpleCard card);
    void RemoveCardFromActiveCards(SimpleCard card);


public:

    void AddCard(CardInGame card);
    void RemoveCard(SimpleCard card);
    void DisableCard(SimpleCard card);
    void SetPlayerName(const QString& name) { _playerName = name; }

private:

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

//Visualization. The same as in the CardInspector Size.
private:

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.12f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    uint32_t _windowSizeHeight;
    uint32_t _widnowSizeWidth;
    QSize    _mainWindowSize;

public:

    void SetDecks(const AllDecksToBePassed& data);

private:

    QString GetCardPictureAddress(SimpleCard card);
    void SetFontAndAlignment(QLabel* lbl);
    CardPosition GetCurrentCardPosition(bool disabledActive);

    void SetUpButtonPicture(QPushButton* const btn, const QString& picturePath, QSize size);

signals:

    void SignalUserIsClosingCardsInGameObserver();
    void SignalNoCardsLeft(); //Disable Button On this event

public slots:

private:

    bool CheckCardsInGameStackIsEmpty() { return _cardsInGameHolder.size(); }


};

#endif // CARDSINGAMEOBSERVER_H
