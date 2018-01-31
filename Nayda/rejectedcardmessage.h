#ifndef REJECTEDCARDMESSAGE_H
#define REJECTEDCARDMESSAGE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include "Application/card.h"

#include <QDebug>
#include <QPoint>


#include <QDialog>
#include <QPainter>
#include <QPolygon>
#include <QPainterPath>


#define HIDE_THE_CARD_REJECTED_MESSAGE_ON_TIMEOUT
#define CARD_REJECTED_MESSAGE_FADING_TIME 100


namespace Ui {
class RejectedCardMessage;
}

class RejectedCardMessage : public QWidget
{
    Q_OBJECT

    // Свойство полупрозрачности
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;



public:
    explicit RejectedCardMessage(QWidget *parent = 0);
    ~RejectedCardMessage();

private:
    Ui::RejectedCardMessage *ui;



protected:
    void paintEvent(QPaintEvent *event);    // Фон будет отрисовываться через метод перерисовки


public slots:

    void setPopupText(const QString& text); // Установка текста в уведомление
    void show();                            /* Собственный метод показа виджета
                                               * Необходимо для преварительной настройки анимации
                                              * */
    void show(QPoint positionTopLeft, QPoint positionBottomRight);

    //void setUpPopUpCard (SimpleCard card);
    //void setUpPopUpCard (PositionedCard card);
    //void setUpPointsForPoly(QPoint topLeft, QPoint botRight);



public slots:
    void hideAnimation();                   // Слот для запуска анимации скрытия
    void hide();                            /* По окончании анимации, в данном слоте делается проверка,
                                             * виден ли виджет, или его необходимо скрыть
                                             * */



private:


    QLabel label;           // Label с сообщением
    QGridLayout layout;     // Размещение для лейбла
    QPropertyAnimation animation;   // Свойство анимации для всплывающего сообщения
    float popupOpacity;     // Свойства полупрозрачности виджета
    QTimer *timer;          // Таймер, по которому виджет будет скрыт

    QPoint _positionBottomRight;
    QPoint _positionTopLeft;






};

#endif // REJECTEDCARDMESSAGE_H
