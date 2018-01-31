#include "handcardpointer.h"
#include "ui_handcardpointer.h"

HandCardPointer::HandCardPointer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandCardPointer)
{
    ui->setupUi(this);


    setWindowFlags(Qt::FramelessWindowHint |        // Отключаем оформление окна
                   Qt::Tool |                       // Отменяем показ в качестве отдельного окна
                   Qt::WindowStaysOnTopHint);       // Устанавливаем поверх всех окон
    setAttribute(Qt::WA_TranslucentBackground);     // Указываем, что фон будет прозрачным
    setAttribute(Qt::WA_ShowWithoutActivating);     // При показе, виджет не получается фокуса автоматически

    animation.setTargetObject(this);                // Устанавливаем целевой объект анимации
    animation.setPropertyName("popupOpacity");      // Устанавливаем анимируемое свойство
    connect(&animation, &QAbstractAnimation::finished, this, &HandCardPointer::hide); /* Подключаем сигнал окончания
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

#ifdef HIDE_THE_CARD_REJECTED_MESSAGE_ON_TIMEOUT
    connect(timer, &QTimer::timeout, this, &HandCardPointer::hideAnimation);
#endif


}



void HandCardPointer::paintEvent(QPaintEvent *event)
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


    QRect normalRect;
    normalRect.setX(rect().x());
    normalRect.setY(rect().y());
    normalRect.setWidth(rect().width());
    normalRect.setHeight(rect().height()); //different from setted 10!

    normalRect.setHeight(15);

//    qDebug() <<"The height of Triangle Pointer: " << rect().height();
//    qDebug() <<"The width of Triangle Pointer: " << rect().width();
    // Кисть настраиваем на чёрный цвет в режиме полупрозрачности 180 из 255
    //RAL 1017
    //Шафраново-жёлтый	  0  30  70   0	  0  30  90   0	#F4B752	244 183  82

    painter.setBrush(QBrush(QColor(244,183,82,150)));
    painter.setPen(Qt::NoPen); // Край уведомления не будет выделен

    // Отрисовываем фон с закруглением краёв в 10px
    //painter.drawRoundedRect(roundedRect, 10, 10);



    QPainterPath path;



    if (_positionTopLeft.y() - _actualCardSize.height() - 30 < 0) { //higher, than allowed

        path.moveTo(normalRect.topLeft());
        //path.lineTo(_positionBottomRight.x(), normalRect.topLeft().y());
        path.lineTo(normalRect.bottomRight());
        path.lineTo(normalRect.bottomLeft());
        path.lineTo(normalRect.topLeft());

    }
    else {


        qDebug() << "Top Left Position" << normalRect.topLeft();
        qDebug() << "The difference: " << (_positionBottomRight.x() - _positionTopLeft.x()) / 2;

        path.moveTo(normalRect.topLeft());
        //path.lineTo(_positionBottomRight.x(), normalRect.topLeft().y());
        path.lineTo( normalRect.topLeft().x() +((_positionBottomRight.x() - _positionTopLeft.x()) / 2),
                     normalRect.bottomLeft().y());

        path.lineTo(normalRect.topLeft().x() + _positionBottomRight.x() - _positionTopLeft.x(),
                                               normalRect.topRight().y());

        path.lineTo(normalRect.topLeft());



//        path.moveTo((_positionBottomRight.x() - _positionTopLeft.x()) / 2, _positionTopLeft.y());

//        //path.lineTo(_positionBottomRight.x(), normalRect.topLeft().y());
//        path.lineTo(_positionTopLeft.x(), _positionTopLeft.y() - 20 );

//        path.lineTo(_positionBottomRight.x(),_positionTopLeft.y() - 20 );
//        path.lineTo((_positionBottomRight.x() - _positionTopLeft.x()) / 2, _positionTopLeft.y());

    }




    painter.fillPath(path, QBrush(QColor(244,183,82,150)));





}

void HandCardPointer::show()
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



void HandCardPointer::show(QPoint positionTopLeft, QPoint positionBottomRight)
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

    if (positionTopLeft.y() - _actualCardSize.height() - 30 < 0) { //higher, than allowed

        yPos = positionBottomRight.y();

    }
    else {

        yPos =  positionTopLeft.y() - 10; //20 == height of the Triangle

    }

    if (positionBottomRight.x() + _actualCardSize.width() + 10 > QApplication::desktop()->availableGeometry().width()) { //righter, than allowed

        xPos = positionTopLeft.x();

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

void HandCardPointer::setUpHandCardPointer(QPoint positionTopLeft, QPoint positionBottomRight)
{

    //find the HW size of the window
    //The Pointer Size should be the same as the Card

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.0975f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    //resize the Widget
    this->resize((handCardSizeWidht*HW_Screen_Size_Width + 20)*0.5, 10); //height is fixed and is related to card!
//    qDebug() <<"The Height of Triangle Pointer After Resize: " << this->size().height();
//    qDebug() <<"The Width of Triangle Pointer After Resize: " << this->size().width();

    _actualCardSize.setHeight(handCardSizeHeight*HW_Screen_Size_Height + 20);
    _actualCardSize.setWidth(handCardSizeWidht*HW_Screen_Size_Width + 20);



    //pass the Points value to the TriangleCardPointer
    _positionBottomRight = positionBottomRight;
    _positionTopLeft = positionTopLeft;

//    qDebug() << "Delta: " << _positionBottomRight.x() - positionTopLeft.x();


}


void HandCardPointer::hideAnimation()
{
    timer->stop();                  // Останавливаем таймер
    animation.setDuration(CARD_REJECTED_MESSAGE_FADING_TIME);    // Настраиваем длительность анимации
    animation.setStartValue(1.0);   // Стартовое значение будет 1 (полностью непрозрачный виджет)
    animation.setEndValue(0.0);     // Конечное - полностью прозрачный виджет
    animation.start();              // И запускаем анимацию
}


void HandCardPointer::hide()
{
    // Если виджет прозрачный, то скрываем его
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void HandCardPointer::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float HandCardPointer::getPopupOpacity() const
{
    return popupOpacity;
}












HandCardPointer::~HandCardPointer()
{
    delete ui;
}
