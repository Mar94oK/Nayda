#include "cardselector.h"
#include "ui_cardselector.h"

CardSelector::CardSelector(const std::vector<SimpleCard> &cards, CardSelectorMode mode,
                           SelectionMode selectionMode,
                           NecessityOfChoice choice,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardSelector),
    _selectorMode(mode),
    _selectionMode(selectionMode),
    _typeOfChoice(choice),
    _selectableCards(cards)
{
    ui->setupUi(this);
}

CardSelector::~CardSelector()
{
    delete ui;
}
