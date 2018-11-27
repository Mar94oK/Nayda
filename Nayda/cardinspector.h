#ifndef CARDINSPECTOR_H
#define CARDINSPECTOR_H

#include <QWidget>
#include <Application/card.h>
#include <Application/The_Game/The_Game.h>

namespace Ui {
class CardInspector;
}

class CardInspector : public QWidget
{
    Q_OBJECT

public:
    explicit CardInspector(QWidget *parent = 0);
    ~CardInspector();

private:
    Ui::CardInspector *ui;

public:

    void SetUpPopUpCard(DecksPointersData data);


public slots:

    void SlotSetUpSimpleCardToShow(PositionedCard card);





};

#endif // CARDINSPECTOR_H
