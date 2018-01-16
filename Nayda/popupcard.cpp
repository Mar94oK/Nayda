#include "popupcard.h"
#include "ui_popupcard.h"


#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

PopUpCard::PopUpCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopUpCard)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint |        // Отключаем оформление окна
                   Qt::Tool |                       // Отменяем показ в качестве отдельного окна
                   Qt::WindowStaysOnTopHint);       // Устанавливаем поверх всех окон
    setAttribute(Qt::WA_TranslucentBackground);     // Указываем, что фон будет прозрачным
    setAttribute(Qt::WA_ShowWithoutActivating);     // При показе, виджет не получается фокуса автоматически

    animation.setTargetObject(this);                // Устанавливаем целевой объект анимации
    animation.setPropertyName("popupOpacity");      // Устанавливаем анимируемое свойство
    connect(&animation, &QAbstractAnimation::finished, this, &PopUpCard::hide); /* Подключаем сигнал окончания
                                                                                * анимации к слоты скрытия
                                                                                * */

    // Настройка текста уведомления
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // Устанавливаем по центру
    // И настраиваем стили
    label.setStyleSheet("QLabel { color : white; "
                        "margin-top: 6px;"
                        "margin-bottom: 6px;"
                        "margin-left: 10px;"
                        "margin-right: 10px; }");

    // Производим установку текста в размещение, ...
    layout.addWidget(&label, 0, 0);
    setLayout(&layout); // которое помещаем в виджет

    // По сигналу таймера будет произведено скрытие уведомления, если оно видимо
    timer = new QTimer();

#ifdef HIDE_THE_CARD_ON_TIMEOUT
    connect(timer, &QTimer::timeout, this, &PopUpCard::hideAnimation);
#endif



}

void PopUpCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    /* А теперь настраиваем фон уведомления,
     * который является прямоугольником с чёрным фоном
     * */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание

    // Подготавливаем фон. rect() возвращает внутреннюю геометрию виджета уведомления, по содержимому
    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    // Кисть настраиваем на чёрный цвет в режиме полупрозрачности 180 из 255
    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen); // Край уведомления не будет выделен

    // Отрисовываем фон с закруглением краёв в 10px
    painter.drawRoundedRect(roundedRect, 10, 10);


//    QPolygon poly;

//    int yPos = 0;
//    int xPos = 0;


//        //Check the position!

//        if (_positionTopLeft.y() - height() - 30 < 0) { //higher, than allowed

//            yPos = _positionBottomRight.y() + 10;

//            poly << QPoint(_positionBottomRight.x(), _positionBottomRight.y()) << QPoint(_positionTopLeft.x(), _positionBottomRight.y());
//            qDebug() << QPoint(_positionBottomRight.x(), _positionBottomRight.y()) << QPoint(_positionTopLeft.x(), _positionBottomRight.y());

//        }
//        else {

//            yPos =  _positionTopLeft.y() - height() - 10;

//            poly << QPoint(_positionTopLeft.x(), _positionTopLeft.y()) << QPoint(_positionBottomRight.x(), _positionTopLeft.y());
//            qDebug() << QPoint(_positionTopLeft.x(), _positionTopLeft.y()) << QPoint(_positionBottomRight.x(), _positionTopLeft.y());


//        }

//        if (_positionBottomRight.x() + width() + 10 > QApplication::desktop()->availableGeometry().width()) { //righter, than allowed

//            xPos = QApplication::desktop()->availableGeometry().width() - width() - 10;

//             if (_positionTopLeft.y() - height() - 30 < 0) {

//                 poly << QPoint(xPos, yPos) << QPoint(xPos + width(), yPos);
//                 qDebug() << QPoint(xPos, yPos) << QPoint(xPos + width(), yPos);

//             }
//             else {

//                 poly << QPoint(xPos, yPos - height()) << QPoint(xPos + width(), yPos - height());
//                 qDebug() << QPoint(xPos, yPos - height()) << QPoint(xPos + width(), yPos - height());
//             }



//        }
//        else {

//            xPos = _positionTopLeft.x();

//            if (_positionTopLeft.y() - height() - 30 < 0) {

//                poly << QPoint(xPos, yPos) << QPoint(xPos + width(), yPos);
//                qDebug() << "Points: " << QPoint(xPos, yPos) << QPoint(xPos + width(), yPos);

//            }
//            else {

//                poly << QPoint(xPos, yPos - height()) << QPoint(xPos + width(), yPos - height());
//                qDebug() << QPoint(xPos, yPos - height()) << QPoint(xPos + width(), yPos - height());

//            }



//        }

//    poly << QPoint( 0, height()) << QPoint(width(),  height())
//         << QPoint(width(),  height() - 100) << QPoint(0, height()- 100);

//    qDebug() << QPoint( 0, height()) << QPoint(width(),  height())
//             << QPoint(width(),  height() + 100) << QPoint(0, height()+100);

//    QPen pen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
//    painter.setPen(pen);

//    QBrush brush;
//    brush.setColor(Qt::green);
//    brush.setStyle(Qt::SolidPattern);


//    // Fill polygon

//    QPainterPath path;
//    path.addPolygon(poly);


//    // Draw polygon
//    painter.drawPolygon(poly);
//    painter.fillPath(path, brush);







}

void PopUpCard::setPopupText(const QString &text)
{
    label.setText(text);    // Устанавливаем текст в Label
    adjustSize();           // С пересчётом размеров уведомления
}


void PopUpCard::show()
{
    setWindowOpacity(0.0);  // Устанавливаем прозрачность в ноль

    animation.setDuration(150);     // Настраиваем длительность анимации
    animation.setStartValue(0.0);   // Стартовое значение будет 0 (полностью прозрачный виджет)
    animation.setEndValue(1.0);     // Конечное - полностью непрозрачный виджет

    setGeometry(QApplication::desktop()->availableGeometry().width() / 2  -  width() / 2 + QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() / 2  - height() /2 + QApplication::desktop() -> availableGeometry().y(),
                width(),
                height());
//    qDebug() << "Available Geometry Width" << QApplication::desktop()->availableGeometry().width();
//    qDebug() << "Available Geometry X: " << QApplication::desktop() -> availableGeometry().x();
//    qDebug() << "Width: " << width();
//    qDebug() << "Available Geometry Height" << QApplication::desktop()->availableGeometry().height();
//    qDebug() << "Available Geometry Y: " << QApplication::desktop() -> availableGeometry().y();
//    qDebug() << "Width: " << width();


    QWidget::show();                // Отображаем виджет, который полностью прозрачен

    animation.start();              // И запускаем анимацию

#ifdef HIDE_THE_CARD_ON_TIMEOUT
    //timer->start(5000);             // А также стартуем таймер, который запустит скрытие уведомления через 3 секунды
#endif


}

void PopUpCard::show(QPoint positionTopLeft, QPoint positionBottomRight)
{
    setWindowOpacity(0.0);  // Устанавливаем прозрачность в ноль

    animation.setDuration(150);     // Настраиваем длительность анимации
    animation.setStartValue(0.0);   // Стартовое значение будет 0 (полностью прозрачный виджет)
    animation.setEndValue(1.0);     // Конечное - полностью непрозрачный виджет

    int yPos = 0;
    int xPos = 0;

    _positionBottomRight = positionBottomRight;
    _positionTopLeft = positionTopLeft;

    //Check the position!

    if (positionTopLeft.y() - height() - 30 < 0) { //higher, than allowed

        yPos = positionBottomRight.y() + 10;

    }
    else {

        yPos =  positionTopLeft.y() - height() - 10;

    }

    if (positionBottomRight.x() + width() + 10 > QApplication::desktop()->availableGeometry().width()) { //righter, than allowed

        xPos = QApplication::desktop()->availableGeometry().width() - width() - 10;

    }
    else {

        xPos = positionTopLeft.x();

    }


    setGeometry(xPos,
                yPos,
                width(),
                height());








    QWidget::show();                // Отображаем виджет, который полностью прозрачен

    animation.start();              // И запускаем анимацию

#ifdef HIDE_THE_CARD_ON_TIMEOUT
    //timer->start(5000);             // А также стартуем таймер, который запустит скрытие уведомления через 3 секунды
#endif


}

void PopUpCard::setUpPopUpCard(SimpleCard card)
{
    //ui->theCard
    std::map<int, gameCardDoorMonster> :: const_iterator  _monstersIterator;
    std::map<int, gameCardDoorAmplifier> :: const_iterator _amplifiersIterator;
    std::map<int, gameCardDoorCurse> :: const_iterator _cursesIterator;
    std::map<int, gameCardDoorProfession> :: const_iterator _professionsIterator;
    std::map<int, gameCardDoorRace> :: const_iterator _racesIterator;
    std::map<int, gameCardDoorSpecialMechanic> :: const_iterator _specialMechanicsIterator;

    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    QString currentPictureAddress;
    bool isFound = false;
    bool isNoClassNoRace = false;



    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.0975f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    //resize the Widget
    this->resize(handCardSizeWidht*HW_Screen_Size_Width + 20, handCardSizeHeight*HW_Screen_Size_Height + 20);


    if ((!card.first) && (!card.second)) { //the card is Card_No_Race

        QPixmap pxmp_icon_race_1("Pictures/No_Race_dbg.png");
        QPalette plte_icon_race_1;
        plte_icon_race_1.setBrush(ui->theCard->backgroundRole(),
        QBrush(pxmp_icon_race_1.scaled(handCardSizeWidht*HW_Screen_Size_Width,
                                                                 handCardSizeHeight*HW_Screen_Size_Height,
                                                                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

        ui->theCard->setFlat(true);
        ui->theCard->setAutoFillBackground(true);
        ui->theCard->setPalette(plte_icon_race_1);
        ui->theCard->setText("");

        isFound = true;
        isNoClassNoRace = true;
    }
    else if ((!card.first) && (card.second == 1777)) {
        QPixmap pxmp_icon_class_1("Pictures/No_Class_dbg.png");
        QPalette plte_icon_class_1;
        plte_icon_class_1.setBrush(ui->theCard->backgroundRole(),
                                   QBrush(pxmp_icon_class_1.scaled(handCardSizeWidht*HW_Screen_Size_Width,
                                                                   handCardSizeHeight*HW_Screen_Size_Height,
                                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


        ui->theCard->setFlat(true);
        ui->theCard->setAutoFillBackground(true);
        ui->theCard->setPalette(plte_icon_class_1);
        ui->theCard->setText("");

        isFound = true;
        isNoClassNoRace = true;

    }


    else if (!card.first) { //door

        _monstersIterator = _monstersDeck->find(static_cast <int> (card.second));
        if (_monstersIterator != _monstersDeck->end()) {
            currentPictureAddress = (*_monstersIterator).second.pictureAddress();
            isFound = true;
        }
        if (!isFound) {
            _amplifiersIterator = _amplifiersDeck->find(static_cast <int> (card.second));
            if (_amplifiersIterator != _amplifiersDeck->end()) {
                currentPictureAddress = (*_amplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _cursesIterator = _cursesDeck->find(static_cast <int> (card.second));
            if (_cursesIterator != _cursesDeck->end()) {
                currentPictureAddress = (*_cursesIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _professionsIterator = _professionsDeck->find(static_cast <int> (card.second));
            if (_professionsIterator != _professionsDeck->end()) {
                currentPictureAddress = (*_professionsIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _racesIterator = _racesDeck->find(static_cast <int> (card.second));
            if (_racesIterator != _racesDeck->end()) {
                currentPictureAddress = (*_racesIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _specialMechanicsIterator = _specialMechanicsDeck->find(static_cast <int> (card.second));
            if (_specialMechanicsIterator != _specialMechanicsDeck->end()) {
                currentPictureAddress = (*_specialMechanicsIterator).second.pictureAddress();
                isFound = true;
            }
        }




    }
    else { //treasure


        _armorIterator = _armorDeck->find(static_cast <int> (card.second));
        if (_armorIterator != _armorDeck->end()) {
            currentPictureAddress = (*_armorIterator).second.pictureAddress();
            isFound = true;
        }
        if (!isFound) {
            _armorAmplifiersIterator = _armorAmplifiersDeck->find(static_cast <int> (card.second));
            if (_armorAmplifiersIterator != _armorAmplifiersDeck->end()) {
                currentPictureAddress = (*_armorAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _battleAmplifiersIterator = _battleAmplifiersDeck->find(static_cast <int> (card.second));
            if (_battleAmplifiersIterator != _battleAmplifiersDeck->end()) {
                currentPictureAddress = (*_battleAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _levelUpIterator = _levelUpDeck->find(static_cast <int> (card.second));
            if (_levelUpIterator != _levelUpDeck->end()) {
                currentPictureAddress = (*_levelUpIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck->find(static_cast <int> (card.second));
            if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck->end()) {
                currentPictureAddress = (*_specialMechanicsTreasureIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _thingsAmplifiersIterator = _thingsAmplifiersDeck->find(static_cast <int> (card.second));
            if (_thingsAmplifiersIterator != _thingsAmplifiersDeck->end()) {
                currentPictureAddress = (*_thingsAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _weaponsIterator = _weaponsDeck->find(static_cast <int> (card.second));
            if (_weaponsIterator != _weaponsDeck->end()) {
                currentPictureAddress = (*_weaponsIterator).second.pictureAddress();
                isFound = true;
            }
        }



    }

    if (!isFound) qDebug() << "Error during passing Cards to the Hands Shower! Check the number passed! " << card.second;

    if ((isFound) && (!isNoClassNoRace)) {

        //setUpTheCard
        QPixmap pxmp_theCard(currentPictureAddress);
        QPalette plte_theCard;
        plte_theCard.setBrush(ui->theCard->backgroundRole(),
        QBrush(pxmp_theCard.scaled(handCardSizeWidht*HW_Screen_Size_Width,
                                                                 handCardSizeHeight*HW_Screen_Size_Height,
                                                                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

        ui->theCard->setFlat(true);
        ui->theCard->setAutoFillBackground(true);
        ui->theCard->setPalette(plte_theCard);
        ui->theCard->setText("");

    }




}

void PopUpCard::setUpPointsForPoly(QPoint topLeft, QPoint botRight)
{
    _positionBottomRight = botRight;
    _positionTopLeft = topLeft;

}



void PopUpCard::hideAnimation()
{
    timer->stop();                  // Останавливаем таймер
    animation.setDuration(fadingTime);    // Настраиваем длительность анимации
    animation.setStartValue(1.0);   // Стартовое значение будет 1 (полностью непрозрачный виджет)
    animation.setEndValue(0.0);     // Конечное - полностью прозрачный виджет
    animation.start();              // И запускаем анимацию
}

void PopUpCard::hide()
{
    // Если виджет прозрачный, то скрываем его
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void PopUpCard::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float PopUpCard::getPopupOpacity() const
{
    return popupOpacity;
}

PopUpCard::~PopUpCard()
{
    delete ui;
}


void PopUpCard::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void PopUpCard::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void PopUpCard::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void PopUpCard::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void PopUpCard::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void PopUpCard::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void PopUpCard::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void PopUpCard::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void PopUpCard::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void PopUpCard::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void PopUpCard::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void PopUpCard::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void PopUpCard::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}

