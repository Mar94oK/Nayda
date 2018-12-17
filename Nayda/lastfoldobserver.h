#ifndef LASTFOLDOBSERVER_H
#define LASTFOLDOBSERVER_H

#include <QDialog>
#include <Application/card.h>
#include <QPushButton>
#include <QLabel>



enum class FoldObsreverState
{
    Enabled,
    Disabled
};

namespace Ui {
class LastFoldObserver;
}

class LastFoldObserver : public QDialog
{
    Q_OBJECT

public:
    explicit LastFoldObserver(AllDecksToBePassed decksData,
                              QSize mainWindowSize,
                              const std::vector<SimpleCard>& data,
                              QWidget *parent = nullptr);
    ~LastFoldObserver();

private:
    Ui::LastFoldObserver *ui;

private:

    QString _nameBaseText = "Карты, ушедшие в сброс последними: ";

private:

    std::vector<QPushButton* > _cardsLastFoldedRepresenter;
    std::vector<SimpleCard>    _cardsLastFolded;

public:

    void ClearFoldObserver();
    void SetNewCards(std::vector<SimpleCard> cards);

private:

    FoldObsreverState _state = FoldObsreverState::Disabled;

public:

    void SetState(FoldObsreverState state) { _state = state; }
    FoldObsreverState GetState() { return _state; }

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

private:

    void SetDecks(const AllDecksToBePassed& data);
    void AddCard(SimpleCard card);
    QString GetCardPictureAddress(SimpleCard card);

    void SetFontAndAlignment(QLabel* lbl);

    CardPosition GetCurrentCardPosition();

    void SetUpButtonPicture(QPushButton* const btn, const QString& picturePath, QSize size);

signals:

    void SignalUserIsClosingLastFoldObserver();


};

#endif // LASTFOLDOBSERVER_H
