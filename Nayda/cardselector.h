#ifndef CARDSELECTOR_H
#define CARDSELECTOR_H

#include <QWidget>
#include <Application/card.h>

//Архитектура:
//Общий для всех процедур класс, который позволяет создавать
//Массив видимых пользователю "выбираемых" карт.
//Он будет поддерживать несколько типов конструкторов
//Который может подсвечивать некоторые (например неактивные) карты
//И, возможно, иметь некоторые другие особенности


//Селектор регулирует положение карт только относительно самого себя
//Сигнал о финализированном выборе передаётся наружу (Игре).


//Прерывания по проклятию НЕ ПОПАДАЮТ в объект этого класса.
//С ними разбирается сама игра

class CardSelector : public QWidget
{
    Q_OBJECT
public:
    explicit CardSelector(const std::vector<SimpleCard>& cards, QWidget *parent = nullptr);

private:

    std::vector<SimpleCard> _selectableCards;

signals:

    void SignalCardSelected(SimpleCard card);

public slots:


};

#endif // CARDSELECTOR_H
