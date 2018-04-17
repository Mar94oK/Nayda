#include "battlefield.h"
#include "ui_battlefield.h"
#include "munchkinglobaldefines.h"

battleField::battleField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battleField)
{
    ui->setupUi(this);


    QObject::connect(ui->btnStartTestCards, SIGNAL(clicked()), this, SLOT(startCardsRepresentation()));

    //disable the button for cards' testing.
    ui->btnStartTestCards->hide();


    //set the Cover-Picture

    //treeCover.jpg
#ifndef USE_RESOURCES
    QPixmap pxmpBattleField("Pictures/treeCover.jpg");
#else
    QPixmap pxmpBattleField(":/Pictures/treeCover.jpg");
#endif

    QPalette plte_battleField;
    plte_battleField.setBrush(QPalette::Background, QBrush(pxmpBattleField.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    //setPalette(plte_battleField);
    //setAutoFillBackground(true);

    //setStyleSheet("background-image: url(Pictures/TreasuresCard.png)");


}

battleField::~battleField()
{
    delete ui;
}

void battleField::cardsRepresenter()
{
    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //setup the koefficients;
    const float race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float race_class_btn_size_width = 0.0415f;
    const float race_class_btn_size_height = race_class_btn_size_geometric_width_to_height_ratio*race_class_btn_size_width;

    //setting the Main representer
    _theBtnMainRepresenter = new QPushButton (this);
    _theBtnMainRepresenter->setMaximumWidth(race_class_btn_size_width*HW_Screen_Size_Width*2);
    _theBtnMainRepresenter->setMaximumHeight(race_class_btn_size_height*HW_Screen_Size_Height*2);
    _theBtnMainRepresenter->setMinimumWidth(race_class_btn_size_width*HW_Screen_Size_Width*2);
    _theBtnMainRepresenter->setMinimumHeight(race_class_btn_size_height*HW_Screen_Size_Height*2);

    QPixmap pxmpBtnMainRepresenter(_monstersDeck->begin()->second.pictureAddress());
    QPalette plteBtnMainRepresenter;
    plteBtnMainRepresenter.setBrush(_theBtnMainRepresenter->backgroundRole(),
    QBrush(pxmpBtnMainRepresenter.scaled(race_class_btn_size_width*HW_Screen_Size_Width*2,
                                                             race_class_btn_size_height*HW_Screen_Size_Height*2,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->verticalLayout->addWidget(_theBtnMainRepresenter);
    ui->verticalLayout->setAlignment(Qt::AlignHCenter);
    _theBtnMainRepresenter->setFlat(true);
    _theBtnMainRepresenter->setAutoFillBackground(true);
    _theBtnMainRepresenter->setPalette(plteBtnMainRepresenter);




    //setting the other(bottom) representers
    _theBtnRepresenter1 = new QPushButton (this);
    _theBtnRepresenter2 = new QPushButton (this);
    _theBtnRepresenter3 = new QPushButton (this);
    _theBtnRepresenter4 = new QPushButton (this);
    _theBtnRepresenter5 = new QPushButton (this);



    std::vector<QPushButton*> representersVector = {_theBtnRepresenter1, _theBtnRepresenter2,
                                                   _theBtnRepresenter3,_theBtnRepresenter4,
                                                   _theBtnRepresenter5};

    auto iter = _monstersDeck->begin();
    for (int var = 0; var < representersVector.size(); ++var) {
        representersVector[var]->setMaximumWidth(race_class_btn_size_width*HW_Screen_Size_Width);
        representersVector[var]->setMaximumHeight(race_class_btn_size_height*HW_Screen_Size_Height);
        representersVector[var]->setMinimumWidth(race_class_btn_size_width*HW_Screen_Size_Width);
        representersVector[var]->setMinimumHeight(race_class_btn_size_height*HW_Screen_Size_Height);
        representersVector[var]->setText("Hello!");
        ui->horizontalLayout_2->addWidget(representersVector[var]);

        QPixmap pxmp_btn(iter->second.pictureAddress());
        if (iter != _monstersDeck->end()) iter++;
        QPalette plte_btn;
        plte_btn.setBrush(representersVector[var]->backgroundRole(),
        QBrush(pxmp_btn.scaled(race_class_btn_size_width*HW_Screen_Size_Width,
                                                                 race_class_btn_size_height*HW_Screen_Size_Height,
                                                                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

        representersVector[var]->setFlat(true);
        representersVector[var]->setAutoFillBackground(true);
        representersVector[var]->setPalette(plte_btn);
        representersVector[var]->setText("");

    }

    _showCardsTimer = new QTimer(this);
    connect(_showCardsTimer, SIGNAL(timeout()), this, SLOT(continueCardRepresentation()));
    _continueToRepresentCards = false;
    _showCardsTimer->setSingleShot(true);


//    std::map<int, gameCardDoorMonster> :: const_iterator  _monstersIterator;
//    std::map<int, gameCardDoorAmplifier> :: const_iterator _amplifiersIterator;
//    std::map<int, gameCardDoorCurse> :: const_iterator _cursesIterator;
//    std::map<int, gameCardDoorProfession> :: const_iterator _professionsIterator;
//    std::map<int, gameCardDoorRace> :: const_iterator _racesIterator;
//    std::map<int, gameCardDoorSpecialMechanic> _specialMechanicsIterator;

//    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
//    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
//    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
//    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
//    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
//    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
//    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    //setting the iterators to default;
    _monstersIterator = _monstersDeck->begin();
    _amplifiersIterator = _amplifiersDeck->begin();
    _cursesIterator = _cursesDeck->begin();
    _professionsIterator = _professionsDeck->begin();
    _racesIterator = _racesDeck->begin();
    _specialMechanicsIterator = _specialMechanicsDeck->begin();

    _armorIterator = _armorDeck->begin();
    _armorAmplifiersIterator = _armorAmplifiersDeck->begin();
    _battleAmplifiersIterator = _battleAmplifiersDeck->begin();
    _levelUpIterator = _levelUpDeck->begin();
    _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck->begin();
    _thingsAmplifiersIterator = _thingsAmplifiersDeck->begin();
    _weaponsIterator = _weaponsDeck->begin();



}

void battleField::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void battleField::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void battleField::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void battleField::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void battleField::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void battleField::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void battleField::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void battleField::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void battleField::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void battleField::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void battleField::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void battleField::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void battleField::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}

void battleField::continueCardRepresentation()
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();
    QPixmap pxmpMainBtn;

    if (_currCardsArrayRepresentationStep < _monstersDeck->size()) {
        pxmpMainBtn.load(_monstersIterator->second.pictureAddress());
        _monstersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size())){
        pxmpMainBtn.load(_amplifiersIterator->second.pictureAddress());
        _amplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size())){
        pxmpMainBtn.load(_cursesIterator->second.pictureAddress());
        _cursesIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size() + _professionsDeck->size())){
        pxmpMainBtn.load(_professionsIterator->second.pictureAddress());
        _professionsIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size() + _professionsDeck->size() +
                                                  _racesDeck->size())){
        pxmpMainBtn.load(_racesIterator->second.pictureAddress());
        _racesIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size() + _professionsDeck->size() +
                                                  _racesDeck->size() + _specialMechanicsDeck->size())){
        pxmpMainBtn.load(_specialMechanicsIterator->second.pictureAddress());
        _specialMechanicsIterator++;
        _currCardsArrayRepresentationStep++;
    }

    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size())){
        pxmpMainBtn.load(_armorIterator->second.pictureAddress());
        _armorIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size())){
        pxmpMainBtn.load(_armorAmplifiersIterator->second.pictureAddress());
        _armorAmplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size())){
        pxmpMainBtn.load(_battleAmplifiersIterator->second.pictureAddress());
        _battleAmplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size())){
        pxmpMainBtn.load(_levelUpIterator->second.pictureAddress());
        _levelUpIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size()
                                                   + _specialMechanicsTreasureDeck->size())){
        pxmpMainBtn.load(_specialMechanicsTreasureIterator->second.pictureAddress());
        _specialMechanicsTreasureIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size()
                                                   + _specialMechanicsTreasureDeck->size() + _thingsAmplifiersDeck->size())){
        pxmpMainBtn.load(_thingsAmplifiersIterator->second.pictureAddress());
        _thingsAmplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size()
                                                   + _specialMechanicsTreasureDeck->size() + _thingsAmplifiersDeck->size()
                                                   + _weaponsDeck->size())){
        pxmpMainBtn.load(_weaponsIterator->second.pictureAddress());
        _weaponsIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else {
        _monstersIterator = _monstersDeck->begin();
        _amplifiersIterator = _amplifiersDeck->begin();
        _cursesIterator = _cursesDeck->begin();
        _professionsIterator = _professionsDeck->begin();
        _racesIterator = _racesDeck->begin();
        _specialMechanicsIterator = _specialMechanicsDeck->begin();

        _armorIterator = _armorDeck->begin();
        _armorAmplifiersIterator = _armorAmplifiersDeck->begin();
        _battleAmplifiersIterator = _battleAmplifiersDeck->begin();
        _levelUpIterator = _levelUpDeck->begin();
        _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck->begin();
        _thingsAmplifiersIterator = _thingsAmplifiersDeck->begin();
        _weaponsIterator = _weaponsDeck->begin();



        pxmpMainBtn.load(_monstersIterator->second.pictureAddress());
        _currCardsArrayRepresentationStep = 0;
    }





    QPalette plte_btn;
    plte_btn.setBrush(_theBtnMainRepresenter->backgroundRole(),
    QBrush(pxmpMainBtn.scaled(_race_class_btn_size_width*HW_Screen_Size_Width*2,
                              _race_class_btn_size_height*HW_Screen_Size_Height*2,
                              Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    _theBtnMainRepresenter->setPalette(plte_btn);

    _showCardsTimer->start(_timerCount);


}

void battleField::startCardsRepresentation()
{
    _showCardsTimer->start(_timerCount);
    _timerCount = _timerCount*2;
    if (_timerCount > 2000) _timerCount = 100;
}

