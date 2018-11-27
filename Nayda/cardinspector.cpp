#include "cardinspector.h"
#include "ui_cardinspector.h"

CardInspector::CardInspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardInspector)
{
    ui->setupUi(this);
}

CardInspector::~CardInspector()
{
    delete ui;
}

void CardInspector::SetUpPopUpCard(DecksPointersData data)
{
    ui->wdgtPopUpCard->setMonsersDeck(data.monstersDeck());
    ui->wdgtPopUpCard->setAmplifiersDeck(data.amplifiersDeck());
    ui->wdgtPopUpCard->setArmorAmplifiersDeck(data.armorAmplifiersDeck());
    ui->wdgtPopUpCard->setArmorDeck(data.armorDeck());
    ui->wdgtPopUpCard->setBattleAmplifiersDeck(data.battleAmplifiersDeck());
    ui->wdgtPopUpCard->setCursesDeck(data.cursesDeck());
    ui->wdgtPopUpCard->setLevelUpDeck(data.levelUpDeck());
    ui->wdgtPopUpCard->setProfessionsDeck(data.professionsDeck());
    ui->wdgtPopUpCard->setRacesDeck(data.racesDeck());
    ui->wdgtPopUpCard->setSpecialMechanicsDeck(data.specialMechanicsDeck());
    ui->wdgtPopUpCard->setSpecialMechanicsTreasureDeck(data.specialMechanicsTreasureDeck());
    ui->wdgtPopUpCard->setThingsAmplifiersDeck(data.thingsAmplifiersDeck());
    ui->wdgtPopUpCard->setWeaponsDeck(data.weaponsDeck());
}

void CardInspector::SlotSetUpSimpleCardToShow(PositionedCard card)
{
    ui->wdgtPopUpCard->setUpPopUpCard(card.GetCard());
    ui->wdgtPopUpCard->show();

    ui->txtBrowser_CardText->setText("Отличная карта!");
}
