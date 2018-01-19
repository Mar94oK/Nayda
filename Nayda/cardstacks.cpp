#include "cardstacks.h"
#include "ui_cardstacks.h"

CardStacks::CardStacks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardStacks)
{
    ui->setupUi(this);

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //set-up the initial Stacks

    QPixmap doorsStackImage(_doorsStackLevelsPictures[0]);
    QPalette plte_doorStack;
    plte_doorStack.setBrush(ui->btn_DoorsStack->backgroundRole(),
    QBrush(doorsStackImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                    _race_class_btn_size_height*HW_Screen_Size_Height,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


    ui->btn_DoorsStack->setFlat(true);
    ui->btn_DoorsStack->setAutoFillBackground(true);
    ui->btn_DoorsStack->setPalette(plte_doorStack);
    ui->btn_DoorsStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    if (_showTheNumberOfCardsLeft) {
        ui->lbl_DoorsStack->setText(QString::number(_doorsLeft));
    }

    QPixmap treasuresStackImage(_treasuresStackLevelPictures[0]);
    QPalette plte_treasureStack;
    plte_doorStack.setBrush(ui->btn_TreasuresStack->backgroundRole(),
    QBrush(treasuresStackImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                    _race_class_btn_size_height*HW_Screen_Size_Height,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


    ui->btn_TreasuresStack->setFlat(true);
    ui->btn_TreasuresStack->setAutoFillBackground(true);
    ui->btn_TreasuresStack->setPalette(plte_treasureStack);
    ui->btn_TreasuresStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    if (_showTheNumberOfCardsLeft) {
        ui->lbl_TreasuresStack->setText(QString::number(_treasuresLeft));
    }


}

CardStacks::~CardStacks()
{
    delete ui;
}

void CardStacks::changeTheDoorsStackView(unsigned int cardsLeft)
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    unsigned int stage = 0;
    if (cardsLeft > 100) {
        stage = 0;
    }
    else if ((cardsLeft < 101) && (cardsLeft > 70) ) {
        stage = 1;
    }
    else if ((cardsLeft < 71) && (cardsLeft > 30) ) {
        stage = 2;
    }
    else if ((cardsLeft < 31) && (cardsLeft > 1) ) {
        stage = 3;
    }
    else if (cardsLeft == 1) {
        stage = 4;
    }
    else {
        stage = 5; //clear the stack!
    }


    QPixmap doorsStackImage(_doorsStackLevelsPictures[stage]);
    QPalette plte_doorStack;
    plte_doorStack.setBrush(ui->btn_DoorsStack->backgroundRole(),
    QBrush(doorsStackImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                    _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


    ui->btn_DoorsStack->setFlat(true);
    ui->btn_DoorsStack->setAutoFillBackground(true);
    ui->btn_DoorsStack->setPalette(plte_doorStack);
    ui->btn_DoorsStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    if (_showTheNumberOfCardsLeft) {
        ui->lbl_DoorsStack->setText(QString::number(cardsLeft));
    }




}

void CardStacks::changeTheTreasureStackView(unsigned int cardsLeft)
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    unsigned int stage = 0;
    if (cardsLeft > 100) {
        stage = 0;
    }
    else if ((cardsLeft < 101) && (cardsLeft > 70) ) {
        stage = 1;
    }
    else if ((cardsLeft < 71) && (cardsLeft > 30) ) {
        stage = 2;
    }
    else if ((cardsLeft < 31) && (cardsLeft > 1) ) {
        stage = 3;
    }
    else if (cardsLeft == 1) {
        stage = 4;
    }
    else {
        stage = 5; //clear the stack!
    }


    QPixmap treasuresStackImage(_treasuresStackLevelPictures[stage]);
    QPalette plte_treasuresStack;
    plte_treasuresStack.setBrush(ui->btn_TreasuresStack->backgroundRole(),
    QBrush(treasuresStackImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                    _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


    ui->btn_TreasuresStack->setFlat(true);
    ui->btn_TreasuresStack->setAutoFillBackground(true);
    ui->btn_TreasuresStack->setPalette(plte_treasuresStack);
    ui->btn_TreasuresStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    //Show the Number of Cards Left
    if (_showTheNumberOfCardsLeft) {
        ui->lbl_TreasuresStack->setText(QString::number(cardsLeft));
    }


}

void CardStacks::passTheCardToFoldStack(SimpleCard card)
{
    if (card.first) {
        _treasuresFold.push_back(card);
    }
    else {
        _doorsFold.push_back(card);
    }


    //and redraw the Picture!

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();


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
    if (!card.first) { //door

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


    if (!card.first) {

        QPixmap docksFoldImage(currentPictureAddress);
        QPalette plte_doorsFoldStack;
        plte_doorsFoldStack.setBrush(ui->btn_TreasuresStack->backgroundRole(),
                                         QBrush(docksFoldImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                                          _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                                                          Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


        ui->btn_TreasuresFold->setFlat(true);
        ui->btn_TreasuresFold->setAutoFillBackground(true);
        ui->btn_TreasuresFold->setPalette(plte_doorsFoldStack);
        ui->btn_TreasuresFold->setText("");
        //ui->btn_DoorsStack->installEventFilter(this);

        //set the Value
        ui->lbl_DoorsFold->setText(QString::number(_doorsFold.size()));



    }
    else {


        QPixmap treasuresFoldImage(currentPictureAddress);
        QPalette plte_treasuresFoldStack;
        plte_treasuresFoldStack.setBrush(ui->btn_TreasuresStack->backgroundRole(),
                                         QBrush(treasuresFoldImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                                          _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                                                          Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));


        ui->btn_TreasuresFold->setFlat(true);
        ui->btn_TreasuresFold->setAutoFillBackground(true);
        ui->btn_TreasuresFold->setPalette(plte_treasuresFoldStack);
        ui->btn_TreasuresFold->setText("");
        //ui->btn_DoorsStack->installEventFilter(this);


        //set the Value
        ui->lbl_TreasuresFold->setText(QString::number(_treasuresFold.size()));
    }






}

unsigned int CardStacks::treasuresLeft() const
{
    return _treasuresLeft;
}

void CardStacks::setTreasuresLeft(unsigned int treasuresLeft)
{
    _treasuresLeft = treasuresLeft;
}

unsigned int CardStacks::doorsLeft() const
{
    return _doorsLeft;
}

void CardStacks::setDoorsLeft(unsigned int doorsLeft)
{
    _doorsLeft = doorsLeft;
}

unsigned int CardStacks::totalDoors() const
{
    return _totalDoors;
}

void CardStacks::setTotalDoors(unsigned int totalDoors)
{
    _totalDoors = totalDoors;
}

unsigned int CardStacks::totalTreasures() const
{
    return _totalTreasures;
}

void CardStacks::setTotalTreasures(unsigned int totalTreasures)
{
    _totalTreasures = totalTreasures;
}

void CardStacks::updateTreasuresLeft(unsigned int treasuresLeft)
{
    _treasuresLeft = treasuresLeft;
    ui->lbl_TreasuresStack->setText(QString::number(treasuresLeft));

}

void CardStacks::updateDoorsLeft(unsigned int doorsLeft)
{
    _doorsLeft = doorsLeft;
    ui->lbl_DoorsStack->setText(QString::number(doorsLeft));
}


void CardStacks::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void CardStacks::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void CardStacks::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void CardStacks::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void CardStacks::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void CardStacks::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void CardStacks::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void CardStacks::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void CardStacks::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void CardStacks::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void CardStacks::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void CardStacks::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void CardStacks::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}
