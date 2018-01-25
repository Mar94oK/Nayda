#include "handsecondaryplayer.h"
#include "ui_handsecondaryplayer.h"

HandSecondaryPlayer::HandSecondaryPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandSecondaryPlayer)
{
    ui->setupUi(this);


    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    QPixmap pxmpHandSecondaryPlayer("Pictures/handCover/HandCover.png");
    QPalette plte_handSecondaryPlayer;
    qDebug () << "Size: " << size();
    plte_handSecondaryPlayer.setBrush(QPalette::Background, QBrush(pxmpHandSecondaryPlayer.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                                                  _race_class_btn_size_height*HW_Screen_Size_Height,
                                                                                  Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    setPalette(plte_handSecondaryPlayer);
    setAutoFillBackground(true);


    ui->btn_Doors->setStyleSheet("QPushButton{background:transparent;}");
    ui->btn_Treasures->setStyleSheet("QPushButton{background:transparent;}");

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


}

HandSecondaryPlayer::~HandSecondaryPlayer()
{
    delete ui;
}

void HandSecondaryPlayer::_slotTestHandButtons()
{
    qDebug() << "The Button is pressed!" ;
}
