#ifndef SELECTABLECARDWIDGET_H
#define SELECTABLECARDWIDGET_H

#include <QWidget>
#include <QSize>
#include <QString>
#include <Application/card.h>
#include "smartqtlogger.h"

namespace Ui {
class SelectableCardWidget;
}

class SelectableCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectableCardWidget(SelectableCardMode mode, std::shared_ptr<CommonCardViewData> data, QWidget *parent = nullptr);
    ~SelectableCardWidget();

private:
    Ui::SelectableCardWidget *ui;

private:

    Logger logger;

private:

    CardToBeShownInSellMenu* _dataSellCards;
    CommonCardViewData* _cardData;

signals:

    void SignalReportSelected(bool selected);

private slots:

    void SlotReportSelected(bool selected);

private:

    void SetUpSignalsSlotsConnection();

public:

    void DisableChecker();

};

#endif // SELECTABLECARDWIDGET_H
