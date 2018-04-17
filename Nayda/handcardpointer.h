#ifndef HANDCARDPOINTER_H
#define HANDCARDPOINTER_H

#include <QWidget>
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
#include <QDesktopWidget>
#include <rejectedcardmessage.h>

namespace Ui {
class HandCardPointer;
}

class HandCardPointer : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)


    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

public:
    explicit HandCardPointer(QWidget *parent = 0);
    ~HandCardPointer();

private:
    Ui::HandCardPointer *ui;

protected:
    void paintEvent(QPaintEvent *event);    // Фон будет отрисовываться через метод перерисовки

public slots:

    void show();                            /* Собственный метод показа виджета
                                               * Необходимо для преварительной настройки анимации
                                              * */
    void show(QPoint positionTopLeft, QPoint positionBottomRight);

    void hideAnimation();                   // Слот для запуска анимации скрытия
    void hide();                            /* По окончании анимации, в данном слоте делается проверка,
                                             * виден ли виджет, или его необходимо скрыть
                                             * */

    void setUpHandCardPointer(QPoint positionTopLeft, QPoint positionBottomRight);

private:

    QLabel label;           // Label с сообщением
    QGridLayout layout;     // Размещение для лейбла
    QPropertyAnimation animation;   // Свойство анимации для всплывающего сообщения
    float popupOpacity;     // Свойства полупрозрачности виджета
    QTimer *timer;          // Таймер, по которому виджет будет скрыт

    QPoint _positionBottomRight;
    QPoint _positionTopLeft;

    QRect _actualCardSize;


};

#endif // HANDCARDPOINTER_H
