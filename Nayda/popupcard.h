#ifndef POPUPCARD_H
#define POPUPCARD_H

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

#define fadingTime 150
//Not not to hide the card on timeout event.
//#define HIDE_THE_CARD_ON_TIMEOUT

namespace Ui {
class PopUpCard;
}

class PopUpCard : public QWidget
{
    Q_OBJECT

    // Свойство полупрозрачности
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

public:
    explicit PopUpCard(QWidget *parent = 0);
    ~PopUpCard();


protected:

    void paintEvent(QPaintEvent *event);    // Фон будет отрисовываться через метод перерисовки

public slots:

    void setPopupText(const QString& text); // Установка текста в уведомление
    void show();                            /* Собственный метод показа виджета
                                               * Необходимо для преварительной настройки анимации
                                              * */
    void show(QPoint positionTopLeft, QPoint positionBottomRight);

    void setUpPopUpCard (SimpleCard card);
    //void setUpPopUpCard (PositionedCard card);
    void setUpPointsForPoly(QPoint topLeft, QPoint botRight);

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

private:
    Ui::PopUpCard *ui;

    const std::map<int, gameCardDoorMonster> *_monstersDeck;
    const std::map<int, gameCardDoorAmplifier> *_amplifiersDeck;
    const std::map<int, gameCardDoorCurse> *_cursesDeck;
    const std::map<int, gameCardDoorProfession> *_professionsDeck;
    const std::map<int, gameCardDoorRace> *_racesDeck;
    const std::map<int, gameCardDoorSpecialMechanic> *_specialMechanicsDeck;

    const std::map<int, gameCardTreasureArmor> *_armorDeck;
    const std::map<int, gameCardTreasureArmorAmplifier> *_armorAmplifiersDeck;
    const std::map<int, gameCardTreasureBattleAmplifier> *_battleAmplifiersDeck;
    const std::map<int, gameCardTreasureLevelUp> *_levelUpDeck;
    const std::map<int, gameCardTreasureSpecialMechanic> *_specialMechanicsTreasureDeck;
    const std::map<int, gameCardTreasureThingsAmplifiers> *_thingsAmplifiersDeck;
    const std::map<int, gameCardTreasureWeapon> *_weaponsDeck;

public:

    void setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck);
    void setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck);
    void setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck);
    void setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck);
    void setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck);
    void setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck);
    void setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck);
    void setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck);
    void setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck);
    void setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck);
    void setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck);
    void setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck);
    void setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck);

};

#endif // POPUPCARD_H
