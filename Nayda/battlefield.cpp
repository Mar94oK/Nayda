#include "battlefield.h"
#include "ui_battlefield.h"
#include "munchkinglobaldefines.h"
#include <QDebug>
#include "Application/The_Game/The_Game.h"

battleField::battleField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battleField)
{
    ui->setupUi(this);

    QObject::connect(ui->btnStartTestCards, SIGNAL(clicked()), this, SLOT(startCardsRepresentation()));

    //disable the button for cards' testing.
    ui->btnStartTestCards->hide();

    SetUpPictureAddresses();
    SetUpInitialTimersPictures();
    SetWidgetsToStartUpPhase();
    SetUpSignalsSlotsConnections();

    SetUpTimersLabels();
    //InitializeStartUpProcedureVisualization();


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

    ui->dbgLayout->addWidget(_theBtnMainRepresenter);
    ui->dbgLayout->setAlignment(Qt::AlignHCenter);
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
        ui->dbgLayout->addWidget(representersVector[var]);

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

void battleField::SetBackgroundPicture()
{

//    qDebug() << "NAY-001: SetUp Cover Picture for BattleField.";
#ifndef USE_RESOURCES
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Pictures/playMenu";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Nayda/Pictures/battleField";
#endif
    QPixmap pxmpBattleField(uiBattleFieldFilesLocation + QString("BattleFieldCover.png"));
#else
    QPixmap pxmpBattleField(":/Pictures/battleField/BattleFieldCover.png");
#endif
    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

    QPixmap resultOpaque = pxmpBattleField;
    setAutoFillBackground(true);

    QPainter painter(this);
    painter.begin(&resultOpaque);
    painter.setOpacity(0.3);
    painter.drawPixmap(0,0, pxmpBattleField);
    painter.end();

    QPalette plte_battleField;
    qDebug () << "Size: " << size();
    plte_battleField.setBrush(QPalette::Background, QBrush(resultOpaque.scaled(HW_Screen_Size.width() * The_Game::koeff_GameField_size,
                                                                                  HW_Screen_Size.height() * The_Game::koeff_GameField_size,
                                                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation)));


    setPalette(plte_battleField);

}

void battleField::SetWidgetsToStartUpPhase()
{
    //make 'em all invisible first...
    ui->btnStartTestCards->hide();
    ui->btn_MoveTimer->hide();
    ui->btn_PhaseTimer->hide();
    ui->lbl_Monster->hide();
    ui->lbl_MonsterTotalPower->hide();
    ui->lbl_MoveTime->hide();
    ui->lbl_MoveTimer->hide();
    ui->lbl_PhaseTime->hide();
    ui->lbl_PhaseTimer->hide();
    ui->lbl_Player->hide();
    ui->lbl_PlayersPower->hide();    
    ui->lbl_PhaseName->hide();

}

void battleField::SetFontAndAlignment(QLabel *lbl)
{
    QFont        _startUpTimerTextLabelFont ("times", 35);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    lbl->setFont(_startUpTimerTextLabelFont);
    lbl->setAlignment(Qt::AlignHCenter);
}

void battleField::ShowInitialAnimationScene_1()
{
    QFont        _startUpTimerTextLabelFont ("times", 75);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    _startUpTimerTextLabel->setText(_startUpTimerText);
    _startUpTimerTextLabel->setFont(_startUpTimerTextLabelFont);

    uint32_t pixelWidth = _startUpTimerTextLabelFontInterval.width(_startUpTimerTextLabel->text());
    uint32_t pixelHeight = _startUpTimerTextLabelFontInterval.height();

    _startUpTimerTextLabel->setFixedWidth(pixelWidth);
    _startUpTimerTextLabel->setFixedHeight(pixelHeight);
    _startUpTimerTextLabel->setText("Вперёд, в пещеры!!!!");
    _startUpTimerTextLabel->setAlignment(Qt::AlignHCenter);

    _timeLeftBeforeStartUpLabel->setText("");
}

void battleField::HideInitialAnimationScene_1()
{
    _startUpTimerTextLabel->hide();
    _timeLeftBeforeStartUpLabel->hide();
}

void battleField::ShowInitialAnimationScene_2()
{
//    _orderNotificationName = new QLabel();
//    SetFontAndAlignment(_orderNotificationName);

//    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
//    {
//        QLabel* currLabel = new QLabel();
//        SetFontAndAlignment(currLabel);
//        _labelsPlayerNamesInOrder.push_back(currLabel);
//        currLabel->setText(QString::number(_labelsPlayerNamesInOrder.size())
//                           + " : "
//                           + _playersOrder[var]);

//    }

//    ui->dbgLayout->addWidget(_orderNotificationName);
//    for (uint32_t var = 0; var < _labelsPlayerNamesInOrder.size(); ++var)
//    {
//        ui->dbgLayout->addWidget(_labelsPlayerNamesInOrder[var]);
//    }

    _orderNotification = new PlayersOrderNotification();
    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
        _orderNotification->AddPlayer(_playersOrder[var]);

    _spacerForScene2_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->dbgLayout->addSpacerItem(_spacerForScene2_2);

    ui->dbgLayout->addWidget(_orderNotification);
    ui->dbgLayout->setAlignment(Qt::AlignHCenter);

    _spacerForScene2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->dbgLayout->addSpacerItem(_spacerForScene2);
}

void battleField::InitializeStartUpProcedureVisualization()
{
    QFont        _startUpTimerTextLabelFont ("times", 24);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    _startUpTimerTextLabel = new QLabel(this);
    _startUpTimerTextLabel->setText(_startUpTimerText);
    _startUpTimerTextLabel->setFont(_startUpTimerTextLabelFont);

    uint32_t pixelWidth = _startUpTimerTextLabelFontInterval.width(_startUpTimerTextLabel->text());
    uint32_t pixelHeight = _startUpTimerTextLabelFontInterval.height();

    //_startUpTimerTextLabel->setFixedWidth(pixelWidth);
    _startUpTimerTextLabel->setFixedHeight(pixelHeight);

    QFont        _timeLeftBeforeStartUpLabelFont ("times", 112);
    QFontMetrics _timeLeftBeforeStartUpLabelFontInterval (_timeLeftBeforeStartUpLabelFont);
    _timeLeftBeforeStartUpLabel = new QLabel(this);
    _timeLeftBeforeStartUpLabel->setText(QString::number(_startUpTimeSeconds));
    _timeLeftBeforeStartUpLabel->setFont(_timeLeftBeforeStartUpLabelFont);

    _startUpTimerTextLabel->setAlignment(Qt::AlignHCenter);
    _timeLeftBeforeStartUpLabel->setAlignment(Qt::AlignHCenter);

    pixelWidth = _timeLeftBeforeStartUpLabelFontInterval.width(_timeLeftBeforeStartUpLabel->text());
    pixelHeight = _timeLeftBeforeStartUpLabelFontInterval.height();

    _timeLeftBeforeStartUpLabel->setFixedWidth(pixelWidth);
    _timeLeftBeforeStartUpLabel->setFixedHeight(pixelHeight);

    QVBoxLayout* centeredLayout1 = new QVBoxLayout();
    QVBoxLayout* centeredLayout2 = new QVBoxLayout();

    ui->dbgLayout->addLayout(centeredLayout1);
    ui->dbgLayout->addLayout(centeredLayout2);

    _spacerBottom = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->dbgLayout->addSpacerItem(_spacerBottom);

    centeredLayout1->addWidget(_startUpTimerTextLabel);
    centeredLayout2->addWidget(_timeLeftBeforeStartUpLabel);

    ui->dbgLayout->setStretch(1,1);
    ui->dbgLayout->setAlignment(Qt::AlignHCenter);


    QFont        _PhaseNameLabelFont ("times", 24);
    QFontMetrics _PhaseNameLabelFontInterval (_PhaseNameLabelFont);
    ui->lbl_PhaseName->setText(_phaseNameInitialPhaseText + " "+ _playersOrder[0]);
    ui->lbl_PhaseName->setFont(_PhaseNameLabelFont);

    pixelWidth = _PhaseNameLabelFontInterval.width(ui->lbl_PhaseName->text());
    pixelHeight = _PhaseNameLabelFontInterval.height();

    //ui->lbl_PhaseName->setFixedWidth(pixelWidth);
    ui->lbl_PhaseName->setFixedHeight(pixelHeight);


    //Set-Up Players Order Notification:

    //Order notification should be Created here!
    _orderNotification = new PlayersOrderNotification();
    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
        _orderNotification->AddPlayer(_playersOrder[var]);


    //Initialize the Timer:
    _startUpTimer = new QTimer(this);
    _startUpTimer->setInterval(1000);
    _startUpTimer->setSingleShot(true);
    connect(_startUpTimer, &QTimer::timeout, this, &battleField::SlotStartUpTimerHandler);
    _startUpTimer->start();

}

void battleField::SlotStartUpAnimationCompleted()
{
    qDebug() << "SlotStartUpAnimationCompleted() ";

    ui->btn_MoveTimer->show();
    ui->btn_PhaseTimer->show();
    ui->lbl_Monster->show();
    ui->lbl_MonsterTotalPower->show();
    ui->lbl_MoveTime->show();
    ui->lbl_MoveTimer->show();
    ui->lbl_PhaseTime->show();
    ui->lbl_PhaseTimer->show();
    ui->lbl_Player->show();
    ui->lbl_PlayersPower->show();
    ui->lbl_PhaseName->show();

}

void battleField::SetUpSignalsSlotsConnections()
{
    connect(this, &battleField::SignalStartUpAnimationCompleted, this, &battleField::SlotStartUpAnimationCompleted);
}

void battleField::SlotStartUpTimerHandler()
{
    ++_startUpTimerTicksCounter;
    _timeLeftBeforeStartUpLabel->setText(QString::number(_startUpTimeSeconds - 1*_startUpTimerTicksCounter));
    if (_startUpTimerTicksCounter < _startUpTimeSeconds)
        _startUpTimer->start();
    else if (_startUpTimerTicksCounter == _startUpTimeSeconds)
    {
        ShowInitialAnimationScene_1();
        _startUpTimer->start();
    }
    else if (_startUpTimerTicksCounter == _startUpTimeSeconds + 1)
    {
        HideInitialAnimationScene_1();
        ShowInitialAnimationScene_2();
        _startUpTimer->start();
    }
    else if ( _startUpTimerTicksCounter <= _startUpTimeSeconds + 1 + _startUpShowOrderTime)
    {
        _startUpTimer->start();
    }
    else
    {
        HideInitialAnimationScene_2();
        emit SignalStartUpAnimationCompleted();
    }

}

void battleField::paintEvent(QPaintEvent *)
{
#ifndef USE_RESOURCES

    //    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Pictures/battleField/";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Nayda/Pictures/battleField/";
#endif

     QString path = homeDirectory + uiBattleFieldFilesLocation;

     qDebug() << "NAY-001: SetUp Cover Picture for BattleField.";
     QPixmap pxmpBattleField(path + QString("BattleFieldCover.png"));

#else
    QPixmap pxmpBattleField(":/Pictures/battleField/BattleFieldCover.png");
#endif

     //find the HW size of the window
     QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

     QPixmap resultOpaque = pxmpBattleField.scaled(HW_Screen_Size.width() * The_Game::koeff_GameField_size,
                                                    HW_Screen_Size.height() * The_Game::koeff_GameField_size,
                                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
     setAutoFillBackground(true);

     QPainter painter(this);
     if (!painter.isActive())
        painter.begin(&resultOpaque);
     painter.setOpacity(0.15);
     painter.drawPixmap(0,0, resultOpaque);
     painter.end();

}

void battleField::SetUpPictureAddresses()
{
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Pictures/gameSettingsWidget";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Nayda/Pictures/battleField";
#endif

     QString picturesLocationBasis = homeDirectory + uiPlayMenuFilesLocation + "/";
#ifndef USE_RESOURCES
     _diplomacyTimerPictureAddress = picturesLocationBasis + "DiplomacyTime.png";
     _timeToMoveTimerPictureAddress = picturesLocationBasis + "TimeToMove.png";
     _timeToThinkTimerPictureAddress = picturesLocationBasis + "TimeToThink.png";
     _timeForOpponentsToDecideTimerPictureAddress = picturesLocationBasis + "TimeForOpponentsDecision.png";
#else
    _diplomacyTimerPictureAddress = ":/Pictures/gameSettingsWidget/DiplomacyTime.png";
    _timeToMoveTimerPictureAddress = ":/Pictures/gameSettingsWidget/TimeToMove.png";
    _timeToThinkTimerPictureAddress = ":/Pictures/gameSettingsWidget/TimeToThink.png";
    _timeForOpponentsToDecideTimerPictureAddress = ":/Pictures/gameSettingsWidget/TimeForOpponentsDecision.png";

#endif

}

void battleField::SetUpInitialTimersPictures()
{
    SetUpButtonPicture(ui->btn_MoveTimer, _timeToMoveTimerPictureAddress, _buttonsWidthCoefficient, _buttonsHeightWidthRelatio);
    SetUpButtonPicture(ui->btn_PhaseTimer, _timeToThinkTimerPictureAddress, _buttonsWidthCoefficient, _buttonsHeightWidthRelatio);
}

void battleField::SetUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
{
    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());
    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*widthCoeff,
                                            geometry().width()*widthCoeff*heightWidthRelatio,
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    btn->setMinimumWidth(geometry().width()*widthCoeff);
    btn->setMinimumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setMaximumWidth(geometry().width()*widthCoeff);
    btn->setMaximumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}

std::vector<QString> battleField::playersOrder() const
{
    return _playersOrder;
}

void battleField::setPlayersOrder(const std::vector<QString> &playersOrder)
{
    _playersOrder = playersOrder;
}

void battleField::AddCardToForCards(SimpleCard card)
{

}

void battleField::AddCardToAgainstCards(SimpleCard card)
{

}

void battleField::InitializeBattle()
{

}

void battleField::SlotChangeMoveTimerTime(uint32_t time)
{
    ui->lbl_MoveTime->setText(QString::number(time));
}

void battleField::SlotChangePhaseTimerTime(uint32_t time)
{
    ui->lbl_PhaseTime->setText(QString::number(time));
}

void battleField::SlotGamePhaseHasBeenChanged(GamePhase phase)
{
    if (phase == GamePhase::Diplomacy)
        SetUpButtonPicture(ui->btn_PhaseTimer, _diplomacyTimerPictureAddress, _buttonsWidthCoefficient, _buttonsHeightWidthRelatio);
    else if (phase == GamePhase::WaitingForAnOpponentToMove)
        SetUpButtonPicture(ui->btn_PhaseTimer, _timeForOpponentsToDecideTimerPictureAddress, _buttonsWidthCoefficient, _buttonsHeightWidthRelatio);
    else if (phase == GamePhase::StartOfTheMove)
        SetUpButtonPicture(ui->btn_PhaseTimer, _timeToThinkTimerPictureAddress, _buttonsWidthCoefficient, _buttonsHeightWidthRelatio);
    else
        qDebug() << "NAY-001: This phase will not change the timers ICO! Place here changings for all the Other Features";


}

void battleField::SetTimeLeftMoveTimer(uint32_t secondsLeft)
{
    ui->lbl_MoveTime->setText(QString::number(secondsLeft));
}

void battleField::SetTimeLeftPhaseTimer(uint32_t secondsLeft)
{
    ui->lbl_PhaseTime->setText(QString::number(secondsLeft));
}

void battleField::SetUpTimersLabels()
{
    ui->lbl_PhaseTime->setText(_initialPhaseTimeText);
    ui->lbl_PhaseTimer->setText(_initialPhaseTimerText);
    ui->lbl_MoveTime->setText(_initialMoveTimeText);
    ui->lbl_MoveTimer->setText(_initialMoveTimerText);

    SetFontAndAlignment(ui->lbl_PhaseTimer, 14);
    SetFontAndAlignment(ui->lbl_PhaseTime, 32);
    SetFontAndAlignment(ui->lbl_MoveTimer, 14);
    SetFontAndAlignment(ui->lbl_MoveTime, 32);
}

void battleField::SetFontAndAlignment(QLabel *lbl, uint32_t size)
{
    qDebug() << "NAY-002: Set Font and Alignment";
    QFont        TextLabelFont ("times", static_cast<int32_t>(size));
    QFontMetrics TextLabelFontInterval (TextLabelFont);
    lbl->setText(lbl->text());
    lbl->setFont(TextLabelFont);

//    uint32_t pixelWidth = static_cast<uint32_t>(TextLabelFontInterval.width(_startUpTimerTextLabel->text()));
    uint32_t pixelHeight = static_cast<uint32_t>(TextLabelFontInterval.height());

    lbl->setFixedHeight(static_cast<int32_t>(pixelHeight));
}


void battleField::HideInitialAnimationScene_2()
{
    _orderNotification->hide();
    ui->dbgLayout->removeWidget(_orderNotification);
    delete _orderNotification;

    ui->dbgLayout->removeItem(_spacerBottom);
    delete _spacerBottom;
    ui->dbgLayout->removeItem(_spacerForScene2);
    delete _spacerForScene2;
    ui->dbgLayout->removeItem(_spacerForScene2_2);
    delete _spacerForScene2_2;
}
