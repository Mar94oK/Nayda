#include "playersordernotification.h"
#include "ui_playersordernotification.h"
#include <QFont>
#include <QStyle>

PlayersOrderNotification::PlayersOrderNotification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersOrderNotification)
{
    ui->setupUi(this);
}

PlayersOrderNotification::~PlayersOrderNotification()
{
    delete ui;
}

void PlayersOrderNotification::AddPlayer(const QString &playerName)
{
    _playersOrder.push_back(playerName);
    QLabel* currLabel = new QLabel();
    currLabel->setText(QString::number(_playersOrder.size()) + playerName);
    SetUpFonts(currLabel);
    _orderLabels.push_back(currLabel);
    ui->lyt_Players->addWidget(currLabel);
}

void PlayersOrderNotification::SetUpFonts(QLabel *lbl)
{
    QFont        _startUpTimerTextLabelFont ("times", 35);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    lbl->setFont(_startUpTimerTextLabelFont);
    lbl->setAlignment(Qt::AlignHCenter);
}
