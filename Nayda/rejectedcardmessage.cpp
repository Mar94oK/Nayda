#include "rejectedcardmessage.h"
#include "ui_rejectedcardmessage.h"




#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>


RejectedCardMessage::RejectedCardMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RejectedCardMessage)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint |        // Отключаем оформление окна
                   Qt::Tool |                       // Отменяем показ в качестве отдельного окна
                   Qt::WindowStaysOnTopHint);       // Устанавливаем поверх всех окон
    setAttribute(Qt::WA_TranslucentBackground);     // Указываем, что фон будет прозрачным
    setAttribute(Qt::WA_ShowWithoutActivating);     // При показе, виджет не получается фокуса автоматически

    animation.setTargetObject(this);                // Устанавливаем целевой объект анимации
    animation.setPropertyName("popupOpacity");      // Устанавливаем анимируемое свойство
    connect(&animation, &QAbstractAnimation::finished, this, &RejectedCardMessage::hide); /* Подключаем сигнал окончания
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

    connect(timer, &QTimer::timeout, this, &RejectedCardMessage::hideAnimation);


}


void RejectedCardMessage::paintEvent(QPaintEvent *event)
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
//    roundedRect.setX(rect().x());
//    roundedRect.setY(rect().y());

//    roundedRect.setWidth(rect().width());
//    roundedRect.setHeight(rect().height());
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    QRect normalRect;

    normalRect.setX(rect().x());
    normalRect.setY(rect().y());
    normalRect.setWidth(rect().width());
    normalRect.setHeight(rect().height());




    // Кисть настраиваем на чёрный цвет в режиме полупрозрачности 180 из 255
    //painter.setBrush(QBrush(QColor(0,0,0,180)));
    //Шафраново-жёлтый	  0  30  70   0	  0  30  90   0	#F4B752	244 183  82
    painter.setBrush(QBrush(QColor(244,183,82,150)));

    painter.setPen(Qt::NoPen); // Край уведомления не будет выделен

    // Отрисовываем фон с закруглением краёв в 10px
    //painter.drawRoundedRect(roundedRect, 10, 10);
    //painter.drawRoundedRect(roundedRect, 5, 5);

    //painter.drawRect(normalRect);
    painter.drawRoundedRect(roundedRect, 10, 10);





}

void RejectedCardMessage::setPopupText(const QString &text)
{
    label.setText(text);    // Устанавливаем текст в Label
    adjustSize();           // С пересчётом размеров уведомления
}

void RejectedCardMessage::show()
{
    setWindowOpacity(0.0);  // Устанавливаем прозрачность в ноль

    animation.setDuration(150);     // Настраиваем длительность анимации
    animation.setStartValue(0.0);   // Стартовое значение будет 0 (полностью прозрачный виджет)
    animation.setEndValue(1.0);     // Конечное - полностью непрозрачный виджет

    setGeometry(QApplication::desktop()->availableGeometry().width() / 2  -  width() / 2 + QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() / 2  - height() /2 + QApplication::desktop() -> availableGeometry().y(),
                width(),
                height());



    QWidget::show();                // Отображаем виджет, который полностью прозрачен

    animation.start();              // И запускаем анимацию

#ifdef HIDE_THE_CARD_REJECTED_MESSAGE_ON_TIMEOUT
    timer->start(1500);             // А также стартуем таймер, который запустит скрытие уведомления через 3 секунды
#endif


}


void RejectedCardMessage::show(QPoint positionTopLeft, QPoint positionBottomRight)
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

#ifdef HIDE_THE_CARD_REJECTED_MESSAGE_ON_TIMEOUT
    timer->start(1500);             // А также стартуем таймер, который запустит скрытие уведомления через 3 секунды
#endif


}


void RejectedCardMessage::hideAnimation()
{
    timer->stop();                  // Останавливаем таймер
    animation.setDuration(CARD_REJECTED_MESSAGE_FADING_TIME);    // Настраиваем длительность анимации
    animation.setStartValue(1.0);   // Стартовое значение будет 1 (полностью непрозрачный виджет)
    animation.setEndValue(0.0);     // Конечное - полностью прозрачный виджет
    animation.start();              // И запускаем анимацию
}


void RejectedCardMessage::hide()
{
    // Если виджет прозрачный, то скрываем его
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void RejectedCardMessage::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float RejectedCardMessage::getPopupOpacity() const
{
    return popupOpacity;
}


RejectedCardMessage::~RejectedCardMessage()
{
    delete ui;
}
