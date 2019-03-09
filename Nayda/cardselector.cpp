#include "cardselector.h"
#include "ui_cardselector.h"

CardSelector::CardSelector(const std::vector<SimpleCard> &cards,
                           QSize windowSize,
                           const AllDecksToBePassed &data,
                           CardSelectorMode mode,
                           SelectionMode selectionMode,
                           NecessityOfChoice choice,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardSelector),
    _selectorMode(mode),
    _selectionMode(selectionMode),
    _typeOfChoice(choice),
    _selectableCards(cards),
    _windowSize(windowSize)
{
    ui->setupUi(this);
    SetDecks(data);
}

CardSelector::~CardSelector()
{
    delete ui;
}

void CardSelector::SetDecks(const AllDecksToBePassed &data)
{
    _monstersDeck = data._monstersDeck;
    _amplifiersDeck = data._amplifiersDeck;
    _cursesDeck = data._cursesDeck;
    _professionsDeck = data._professionsDeck;
    _racesDeck = data._racesDeck;
    _specialMechanicsDeck = data._specialMechanicsDeck;

    _armorDeck = data._armorDeck;
    _armorAmplifiersDeck = data._armorAmplifiersDeck;
    _battleAmplifiersDeck = data._battleAmplifiersDeck;
    _levelUpDeck = data._levelUpDeck;
    _specialMechanicsTreasureDeck = data._specialMechanicsTreasureDeck;
    _thingsAmplifiersDeck = data._thingsAmplifiersDeck;
    _weaponsDeck = data._weaponsDeck;
}
