#include "selectablecardwidget.h"
#include "ui_selectablecardwidget.h"
#include <QDebug>
#include <QPixmap>
#include <QPalette>

SelectableCardWidget::SelectableCardWidget(SelectableCardMode mode,
                                           std::shared_ptr<CommonCardViewData> data,
                                           QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectableCardWidget)
{
    ui->setupUi(this);

    DECLARE_NAMED_LOGGER(SelectableCardWidget);

    logger.Algorithm() << "NAY-002: Created Selectable Card Widget with Mode: " << mode;


    switch (mode)
    {

        case SelectableCardMode::SellMenu:
        {
            std::shared_ptr<CardToBeShownInSellMenu> infoData
                    = std::static_pointer_cast<CardToBeShownInSellMenu>(data);
            _cardData = new CardToBeShownInSellMenu(infoData->explicitSize,
                                                infoData->pictureAddress,
                                                infoData->price);

            ui->lbl_Price->setText("Стоимость карты: " + QString::number(infoData->price));

        }
        break;
        case SelectableCardMode::AmplifierAddition:
        {
            std::shared_ptr<CardToBeAmplifiedData> infoData
                    = std::static_pointer_cast<CardToBeAmplifiedData>(data);

            ui->lbl_Price->setText("Стоимость карты: " + QString::number(infoData->price));

            QLabel* bonusLabel = new QLabel("Бонус: " + QString::number(infoData->bonus));
            QLabel* bonusFleeLabel = new QLabel("Бонус на смывку: " +
                                           QString::number(infoData->flightBonus));
            QLabel* cardSizeLabel = new QLabel("Размер: " + QString(infoData->size == Size::Big ? "Большая" : " Мелкая"));

            ui->lyt_OtherLabels->AddWidget(bonusLabel);
            ui->lyt_OtherLabels->AddWidget(bonusFleeLabel);
            ui->lyt_OtherLabels->AddWidget(cardSizeLabel);


        }
        break;




    default:
        logger.Error() << "NAY-002: Not handled Selectable Mode! To be Done" << mode;

        break;
    }


//    _dataSellCards = new CardToBeShownInSellMenu(data.explicitSize,
//                                                 data.pictureAddress,
//                                                 data.price);

    SetUpSignalsSlotsConnection();

    //setCard_related Appearance:

    //setUpTheCard
    //У базового инфо тоже есть все параметрпы, достаточные, чтобы настроить карту.
    QPixmap pxmp_theCard(data->pictureAddress);
    QPalette plte_theCard;
    plte_theCard.setBrush(ui->btn_theCard->backgroundRole(),
    QBrush(pxmp_theCard.scaled(data->explicitSize.width(),
                               data->explicitSize.height(),
                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_theCard->setFlat(true);
    ui->btn_theCard->setAutoFillBackground(true);
    ui->btn_theCard->setPalette(plte_theCard);
    ui->btn_theCard->setText("");
    ui->btn_theCard->setMinimumSize(data->explicitSize);
    ui->chckBox_Selected->setCheckState(Qt::CheckState::Unchecked);

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

void SelectableCardWidget::DisableChecker()
{
    ui->chckBox_Selected->setCheckState(Qt::CheckState::Unchecked);
}
