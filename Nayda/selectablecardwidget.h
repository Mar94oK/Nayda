#ifndef SELECTABLECARDWIDGET_H
#define SELECTABLECARDWIDGET_H

#include <QWidget>
#include <QSize>
#include <QString>
#include <Application/card.h>

namespace Ui {
class SelectableCardWidget;
}

class SelectableCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectableCardWidget(SelectableCardMode mode, CommonCardViewData data, QWidget *parent = nullptr);
    ~SelectableCardWidget();

private:
    Ui::SelectableCardWidget *ui;

private:

    CardToBeShownInSellMenu data;

};

#endif // SELECTABLECARDWIDGET_H
