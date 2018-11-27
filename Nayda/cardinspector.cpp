#include "cardinspector.h"
#include "ui_cardinspector.h"
#include <QRect>


CardInspector::CardInspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardInspector)
{
    ui->setupUi(this);


    //setting-up sizes:
    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.12f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    //resize the Widget
    resize(static_cast<uint32_t>(handCardSizeWidht*HW_Screen_Size_Width) + 20,
           static_cast<uint32_t>(handCardSizeHeight*HW_Screen_Size_Height) + 20);



    ui->btn_Card->setMinimumHeight(handCardSizeHeight*HW_Screen_Size_Height);
    ui->btn_Card->setMinimumWidth(handCardSizeWidht*HW_Screen_Size_Width );
    ui->btn_Card->setMaximumHeight(handCardSizeHeight*HW_Screen_Size_Height);
    ui->btn_Card->setMaximumWidth(handCardSizeWidht*HW_Screen_Size_Width);


}

CardInspector::~CardInspector()
{
    delete ui;
}


void CardInspector::SetUpCardToShow(SimpleCard card)
{
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
    const float handCardSizeWidht = 0.12f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    //resize the Widget
//    this->resize(handCardSizeWidht*HW_Screen_Size_Width + 20, handCardSizeHeight*HW_Screen_Size_Height + 20);

    if ((!card.first) && (!card.second))
    { //the card is Card_No_Race

#ifndef USE_RESOURCES
    QPixmap pxmp_icon_race_1("Pictures/No_Race_dbg.png");
#else
        QPixmap pxmp_icon_race_1(":/Pictures/No_Race_dbg.png");
#endif
        QPalette plte_icon_race_1;
        plte_icon_race_1.setBrush(ui->btn_Card->backgroundRole(),
        QBrush(pxmp_icon_race_1.scaled(handCardSizeWidht*HW_Screen_Size_Width,
                                                                 handCardSizeHeight*HW_Screen_Size_Height,
                                                                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        ui->btn_Card->setFlat(true);
        ui->btn_Card->setAutoFillBackground(true);
        ui->btn_Card->setPalette(plte_icon_race_1);
        ui->btn_Card->setText("");

        isFound = true;
        isNoClassNoRace = true;
    }
    else if ((!card.first) && (card.second == 1777)) {

#ifndef USE_RESOURCES
    QPixmap pxmp_icon_class_1("Pictures/No_Class_dbg.png");
#else
   QPixmap pxmp_icon_class_1(":/Pictures/No_Class_dbg.png");
#endif

        QPalette plte_icon_class_1;
        plte_icon_class_1.setBrush(ui->btn_Card->backgroundRole(),
                                   QBrush(pxmp_icon_class_1.scaled(handCardSizeWidht*HW_Screen_Size_Width,
                                                                   handCardSizeHeight*HW_Screen_Size_Height,
                                                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        ui->btn_Card->setFlat(true);
        ui->btn_Card->setAutoFillBackground(true);
        ui->btn_Card->setPalette(plte_icon_class_1);
        ui->btn_Card->setText("");
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

    if ((isFound) && (!isNoClassNoRace))
    {
        //setUpTheCard
        QPixmap pxmp_theCard(currentPictureAddress);
        QPalette plte_theCard;
        plte_theCard.setBrush(ui->btn_Card->backgroundRole(),
        QBrush(pxmp_theCard.scaled(handCardSizeWidht*HW_Screen_Size_Width,
                                                                 handCardSizeHeight*HW_Screen_Size_Height,
                                                                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

        ui->btn_Card->setFlat(true);
        ui->btn_Card->setAutoFillBackground(true);
        ui->btn_Card->setPalette(plte_theCard);
        ui->btn_Card->setText("");
    }
}


void CardInspector::SlotSetUpSimpleCardToShow(PositionedCard card)
{
    SetUpCardToShow(card.GetCard());

    ui->lbl_CardInfo->setText("Отличная карта!");
}


void CardInspector::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void CardInspector::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void CardInspector::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void CardInspector::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void CardInspector::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void CardInspector::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void CardInspector::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void CardInspector::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void CardInspector::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void CardInspector::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void CardInspector::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void CardInspector::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void CardInspector::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}
