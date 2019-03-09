#ifndef CARDSELECTOR_H
#define CARDSELECTOR_H

#include <QDialog>

#include <Application/card.h>
#include <selectablecardwidget.h>


enum class CardSelectorMode
{
   Normal,
   Extended //пока сам не знаю, что будет под ним подразумеваться
};


enum class SelectionMode
{
    Single,
    Group
};

enum class NecessityOfChoice
{
    UserCan,
    UserShould
};

namespace Ui {
class CardSelector;
}

class CardSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CardSelector(const std::vector<SimpleCard>& cards,
                          QSize windowSize,
                          const AllDecksToBePassed &data,
                          CardSelectorMode mode = CardSelectorMode::Normal,
                          SelectionMode selectionMode = SelectionMode::Single,
                          NecessityOfChoice choice = NecessityOfChoice::UserCan,
                          QWidget *parent = nullptr);
    ~CardSelector();

private:
    Ui::CardSelector *ui;

private:

    CardSelectorMode _selectorMode;
    SelectionMode _selectionMode;
    NecessityOfChoice _typeOfChoice;

    std::vector<SimpleCard> _selectableCards;
    std::vector<SelectableCardWidget*> _cardsToBeSelected;

    //В общем случае может быть и одна.
    //По размеру этого вектора можно делать видимой/скрывать кнопку "Ок"
    std::vector<SimpleCard> _selectedCards;

private:

    QSize _windowSize;

private:
    //колоды и у него должны быть

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

    void SetDecks(const AllDecksToBePassed& data);



};

#endif // CARDSELECTOR_H
