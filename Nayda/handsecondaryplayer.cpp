#include "handsecondaryplayer.h"
#include "ui_handsecondaryplayer.h"

HandSecondaryPlayer::HandSecondaryPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandSecondaryPlayer)
{
    ui->setupUi(this);
}

HandSecondaryPlayer::~HandSecondaryPlayer()
{
    delete ui;
}
