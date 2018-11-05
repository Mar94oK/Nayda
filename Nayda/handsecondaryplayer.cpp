#include "handsecondaryplayer.h"
#include "ui_handsecondaryplayer.h"
#include "munchkinglobaldefines.h"

HandSecondaryPlayer::HandSecondaryPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandSecondaryPlayer)
{
    ui->setupUi(this);


    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //place picture
#ifndef USE_RESOURCES
    QPixmap pxmpHandSecondaryPlayer("Pictures/handCover/HandCover.png");
#else
    QPixmap pxmpHandSecondaryPlayer(":/Pictures/handCover/HandCover.png");
#endif


    QPalette plte_handSecondaryPlayer;
    qDebug () << "Size: " << size();
    plte_handSecondaryPlayer.setBrush(QPalette::Background, QBrush(pxmpHandSecondaryPlayer.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                                                  _race_class_btn_size_height*HW_Screen_Size_Height,
                                                                                  Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    setPalette(plte_handSecondaryPlayer);
    setAutoFillBackground(true);


    ui->btn_Doors->setStyleSheet("QPushButton{background:transparent;color:#0011FF;font:18pt;font:bold;}");
    ui->btn_Treasures->setStyleSheet("QPushButton{background:transparent;color:#0011FF;font:18pt;font:bold;}");

    ui->btn_Doors->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->btn_Treasures->setAttribute(Qt::WA_TranslucentBackground, true);

    ui->btn_Doors->setWindowOpacity(0.55);
    ui->btn_Treasures->setWindowOpacity(0.55);

    ui->btn_Doors->setAutoFillBackground(true);
    ui->btn_Treasures->setAutoFillBackground(true);

#ifdef DEBUG_HANDSECONDARY_PLAYER_WIDGET

    connect(ui->btn_Doors, &QPushButton::clicked, this, &HandSecondaryPlayer::_slotTestHandButtons);
    connect(ui->btn_Treasures, &QPushButton::clicked, this, &HandSecondaryPlayer::_slotTestHandButtons);

#endif

    //setting-up the Text Style of PushButtons;
    //ui->btn_Doors->setStyleSheet("QPushButton{color:#FAAB21;}");
    ui->btn_Doors->setText(QString::number(0));
//    ui->btn_Doors->setStyleSheet("font:28pt;");

//    //ui->btn_Treasures->setStyleSheet("QPushButton{color:#FAAB21;}");
    ui->btn_Treasures->setText(QString::number(0));
//    ui->btn_Treasures->setStyleSheet("font:28pt;");

}

HandSecondaryPlayer::~HandSecondaryPlayer()
{
    delete ui;
}

void HandSecondaryPlayer::_slotTestHandButtons()
{
    qDebug() << "The Button is pressed!" ;
}

void HandSecondaryPlayer::_slot_updateCardsOnHandsTreasures(unsigned int var)
{

    ui->btn_Treasures->setText(QString::number(var));

}

void HandSecondaryPlayer::_slot_updateCardsOnHandsDoors(unsigned int var)
{
    ui->btn_Doors->setText(QString::number(var));
}
