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
    explicit SelectableCardWidget(SelectableCardMode mode, CardToBeShownInSellMenu data, QWidget *parent = nullptr);
    ~SelectableCardWidget();

private:
    Ui::SelectableCardWidget *ui;

private:

    CardToBeShownInSellMenu* _dataSellCards;

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
