#include "selectablecardwidget.h"
#include "ui_selectablecardwidget.h"
#include <QDebug>
#include <QPixmap>
#include <QPalette>

SelectableCardWidget::SelectableCardWidget(SelectableCardMode mode, CardToBeShownInSellMenu data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectableCardWidget)
{
    ui->setupUi(this);

    qDebug() << "NAY-002: Created Selectable Card Widget with Mode: " << mode;

    _dataSellCards = new CardToBeShownInSellMenu(data.explicitSize,
                                                 data.pictureAddress,
                                                 data.price);

    SetUpSignalsSlotsConnection();

    //setCard_related Appearance:

    //setUpTheCard
    QPixmap pxmp_theCard(data.pictureAddress);
    QPalette plte_theCard;
    plte_theCard.setBrush(ui->btn_theCard->backgroundRole(),
    QBrush(pxmp_theCard.scaled(data.explicitSize.width(),
                               data.explicitSize.height(),
                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_theCard->setFlat(true);
    ui->btn_theCard->setAutoFillBackground(true);
    ui->btn_theCard->setPalette(plte_theCard);
    ui->btn_theCard->setText("");

    ui->btn_theCard->setMinimumSize(data.explicitSize);

    ui->chckBox_Selected->setCheckState(Qt::CheckState::Unchecked);
    ui->lbl_Price->setText("Стоимость карты: " + QString::number(data.price));

}

SelectableCardWidget::~SelectableCardWidget()
{
    delete ui;
}

void SelectableCardWidget::SlotReportSelected(bool selected)
{
    emit SignalReportSelected(selected);
}

void SelectableCardWidget::SetUpSignalsSlotsConnection()
{
    connect(ui->chckBox_Selected, &QCheckBox::stateChanged,
            [this]{SlotReportSelected(ui->chckBox_Selected->isChecked());});
}
