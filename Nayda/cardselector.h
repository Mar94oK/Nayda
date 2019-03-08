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
    explicit CardSelector(CardSelectorMode mode = CardSelectorMode::Normal,
                          SelectionMode selectionMode = SelectionMode::Single,
                          NecessityOfChoice choice = NecessityOfChoice::UserCan,
                          QWidget *parent = 0);
    ~CardSelector();

private:
    Ui::CardSelector *ui;

private:

    std::vector<SimpleCard> _selectableCards;
    std::vector<SelectableCardWidget*> _cardsToBeSelected; //к сожалению, этот класс плохо спроектирован - ему нужно передавать тип CardToBeShownInSellMenu
                                                           //придётся либо переработать его, либо написать новый
    std::vector<SimpleCard> _selectedCards;


};

#endif // CARDSELECTOR_H
