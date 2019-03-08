#include "cardselector.h"
#include "ui_cardselector.h"

CardSelector::CardSelector(CardSelectorMode mode,
                           SelectionMode selectionMode,
                           NecessityOfChoice choice,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardSelector)
{
    ui->setupUi(this);
}

CardSelector::~CardSelector()
{
    delete ui;
}
