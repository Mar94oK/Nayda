#ifndef SELLMENU_H
#define SELLMENU_H

#include <QWidget>
#include <Application/card.h>
#include <selectablecardwidget.h>

namespace Ui {
class SellMenu;
}

class SellMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SellMenu(const std::vector<SimpleCard>& data, QWidget *parent = nullptr);
    ~SellMenu();

private:
    Ui::SellMenu *ui;

private:

    QString _nameBaseText = "Продажа карт ";
    QString _sumBaseText = "Сумма: ";
    QString _cardsToSellBaseText = "Карт на продажу: ";

    void AddCard(SimpleCard card);

};

#endif // SELLMENU_H
