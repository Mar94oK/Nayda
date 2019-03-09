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


};

#endif // CARDSELECTOR_H
