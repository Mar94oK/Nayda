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

    SetWidgetsToStartUpPhase();
    SetUpSignalsSlotsConnections();
    InitializeStartUpProcedureVisualization();

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

//#ifndef USE_RESOURCES
//    QPixmap pxmpBattleField("Pictures/JorneyCover.png");
//#else
//    QPixmap pxmpBattleField(":/Pictures/JorneyCover.png");
//#endif


    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Pictures/playMenu";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Nayda/Pictures/battleField";
#endif

    qDebug() << "NAY-001: SetUp Cover Picture for BattleField.";
    QPixmap pxmpBattleField(uiBattleFieldFilesLocation + QString("BattleFieldCover.png"));

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

    QPixmap resultOpaque = pxmpBattleField;
//    setPalette(plte_battleField);
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

}

void battleField::InitializeStartUpProcedureVisualization()
{
//    QLabel* _startUpTimerTextLabel;
//    QLabel* _timeLeftBeforeStartUpLabel;
//    QString _startUpTimerText = "До начала игры осталось: ";
//    QTimer* _startUpTimer;
//    const uint32_t _startUpTimeSeconds = 5;

    QFont        _startUpTimerTextLabelFont ("times", 24);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    _startUpTimerTextLabel = new QLabel(this);
    _startUpTimerTextLabel->setText(_startUpTimerText);
    _startUpTimerTextLabel->setFont(_startUpTimerTextLabelFont);

    uint32_t pixelWidth = _startUpTimerTextLabelFontInterval.width(_startUpTimerTextLabel->text());
    uint32_t pixelHeight = _startUpTimerTextLabelFontInterval.height();

    _startUpTimerTextLabel->setFixedWidth(pixelWidth);
    _startUpTimerTextLabel->setFixedHeight(pixelHeight);

    QFont        _timeLeftBeforeStartUpLabelFont ("times", 112);
    QFontMetrics _timeLeftBeforeStartUpLabelFontInterval (_timeLeftBeforeStartUpLabelFont);
    _timeLeftBeforeStartUpLabel = new QLabel(this);
    _timeLeftBeforeStartUpLabel->setText(QString::number(_startUpTimeSeconds));
    _timeLeftBeforeStartUpLabel->setFont(_timeLeftBeforeStartUpLabelFont);

    pixelWidth = _timeLeftBeforeStartUpLabelFontInterval.width(_timeLeftBeforeStartUpLabel->text());
    pixelHeight = _timeLeftBeforeStartUpLabelFontInterval.height();

    _timeLeftBeforeStartUpLabel->setFixedWidth(pixelWidth);
    _timeLeftBeforeStartUpLabel->setFixedHeight(pixelHeight);

//    ui->lyt_Against->addWidget(_startUpTimerTextLabel);
//    ui->lyt_Against->addWidget(_timeLeftBeforeStartUpLabel);

    QVBoxLayout* centeredLayout1 = new QVBoxLayout();
    QVBoxLayout* centeredLayout2 = new QVBoxLayout();


    ui->dbgLayout->addLayout(centeredLayout1);
    ui->dbgLayout->addLayout(centeredLayout2);

    centeredLayout1->addWidget(_startUpTimerTextLabel);
    centeredLayout2->addWidget(_timeLeftBeforeStartUpLabel);

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

    _startUpTimerTextLabel->hide();
    _timeLeftBeforeStartUpLabel->hide();

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
}

void battleField::SetUpSignalsSlotsConnections()
{
    connect(this, &battleField::SignalStartUpAnimationCompleted, this, &battleField::SlotStartUpAnimationCompleted);
}

void battleField::SlotStartUpTimerHandler()
{
    ++_startUpTimerTicksCounter;
    _timeLeftBeforeStartUpLabel->setText(QString::number(_startUpTimeSeconds - 1*_startUpTimerTicksCounter));
    if (_startUpTimerTicksCounter < 5)
        _startUpTimer->start();
    else
        emit SignalStartUpAnimationCompleted();

}

void battleField::paintEvent(QPaintEvent *)
{
//    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Pictures/playMenu";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiBattleFieldFilesLocation = "Munchkin/Nayda/Nayda/Pictures/battleField/";
#endif

     QString path = homeDirectory + uiBattleFieldFilesLocation;

     qDebug() << "NAY-001: SetUp Cover Picture for BattleField.";
     QPixmap pxmpBattleField(path + QString("BattleFieldCover.png"));

     //find the HW size of the window
     QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

     QPixmap resultOpaque = pxmpBattleField.scaled(HW_Screen_Size.width() * The_Game::koeff_GameField_size,
                                                    HW_Screen_Size.height() * The_Game::koeff_GameField_size,
                                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
     setAutoFillBackground(true);

     QPainter painter(this);
     painter.begin(&resultOpaque);
     painter.setOpacity(0.15);
     painter.drawPixmap(0,0, resultOpaque);
     painter.end();

}

