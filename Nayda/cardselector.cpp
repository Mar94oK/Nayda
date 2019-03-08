#include "cardselector.h"

CardSelector::CardSelector(const std::vector<SimpleCard> &cards, QWidget *parent) :
    _selectableCards(cards), QWidget(parent)
{

}
