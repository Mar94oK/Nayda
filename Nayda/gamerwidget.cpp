#include "gamerwidget.h"
#include "ui_gamerwidget.h"
#define USE_RESOURCES


GamerWidget::GamerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamerWidget)
{
    ui->setupUi(this);

    //https://wiki.qt.io/Qt_Coding_Style/ru

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //Hide odds
    ui->btn_race_2->hide();
    ui->lbl_halfblood->hide();
    ui->btn_class_2->hide();
    ui->lbl_supermunchkin->hide();


    //setup the "card"-race and "card"-class size
    ui->btn_race_1->setMaximumWidth(_race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_race_1->setMaximumHeight(_race_class_btn_size_height*HW_Screen_Size_Height);
    ui->btn_race_1->setMinimumWidth(_race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_race_1->setMinimumHeight(_race_class_btn_size_height*HW_Screen_Size_Height);

    ui->btn_class_1->setMaximumWidth(_race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_class_1->setMaximumHeight(_race_class_btn_size_height*HW_Screen_Size_Height);
    ui->btn_class_1->setMinimumWidth(_race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_class_1->setMinimumHeight(_race_class_btn_size_height*HW_Screen_Size_Height);

    //http://www.prog.org.ru/topic_7215_0.html


#ifndef USE_RESOURCES
    QPixmap pxmp_icon_race_1("Pictures/No_Race_dbg.png");
#else
    QPixmap pxmp_icon_race_1(":/Pictures/No_Race_dbg.png");
#endif

    QPalette plte_icon_race_1;
    plte_icon_race_1.setBrush(ui->btn_race_1->backgroundRole(),
    QBrush(pxmp_icon_race_1.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                             _race_class_btn_size_height*HW_Screen_Size_Height,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

#ifndef USE_RESOURCES
    QPixmap pxmp_icon_class_1("Pictures/No_Class_dbg.png");
#else
    QPixmap pxmp_icon_class_1(":/Pictures/No_Class_dbg.png");
#endif

    QPalette plte_icon_class_1;
    plte_icon_class_1.setBrush(ui->btn_class_1->backgroundRole(),
    QBrush(pxmp_icon_class_1.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                             _race_class_btn_size_height*HW_Screen_Size_Height,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_race_1->setFlat(true);
    ui->btn_race_1->setAutoFillBackground(true);
    ui->btn_race_1->setPalette(plte_icon_race_1);
    ui->btn_race_1->setText("");
    ui->btn_race_1->installEventFilter(this);

    ui->btn_class_1->setFlat(true);
    ui->btn_class_1->setAutoFillBackground(true);
    ui->btn_class_1->setPalette(plte_icon_class_1);
    ui->btn_class_1->setText("");
    ui->btn_class_1->installEventFilter(this);

    ui->btn_diplomacy->installEventFilter(this);

    //fill the classes-races vector with 0,0 card - this means "NoClass (0,1777)" and "NoRace (0, 0)" card.
    _cardsRacesClassesGamerWidgetProperty.push_back({0,0}); //put there NoRace
    _cardsRacesClassesGamerWidgetProperty.push_back({0,1777}); //put there NoClass




    qDebug() <<"Size of the pixmap.scaled, Width: " << pxmp_icon_race_1.scaled(118,180,
                                                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation).size().width();
    qDebug() << "Size of the pixmap.scaled, Height: " << pxmp_icon_race_1.scaled(118,180,
                                                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation).size().height();

    qDebug() << "Size of the button, Width: " << _race_class_btn_size_width*HW_Screen_Size_Width;
    qDebug() << "Size of the button, Height: " << _race_class_btn_size_height*HW_Screen_Size_Height;



    //Initialize the timer for cards show
    _showCardsTimer = new QTimer(this);
    _showCardsTimer->setSingleShot(true);
    //connect timeout issue
    connect(_showCardsTimer, &QTimer::timeout, this, &GamerWidget::_representTheCardInCenterSlot);
    connect(ui->widget, &Hand::_showTheCard, this, &GamerWidget::_representTheCardFromHandsInCentre);
    connect(ui->widget, &Hand::_hideTheCard, this, &GamerWidget::_hideTheCardInCentreSlot);


#ifdef DEBUG_GAMER_WIDGET

    _testTimer = new QTimer();
    _testTimer->setInterval(1000);
    _testTimer->setSingleShot(false);

    connect(ui->btn_Test, &QPushButton::clicked, this, &GamerWidget::_slotStartTestCards);
    connect(_testTimer, &QTimer::timeout, this, &GamerWidget::_slotTestGamerLevels);
    connect(_testTimer, &QTimer::timeout, this, &GamerWidget::_slotTestGamerBattlePower);

#endif
    //forming the vector of pictures;
    //set the initial levelel's pictures.

    QPixmap levelImage(_levelsPictures[_gamerLevel-1]);
    ui->lbl_Level->setPixmap(levelImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                               _race_class_btn_size_height*HW_Screen_Size_Height,
                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    //set The BattlePower Picture and Digit Lables;
    QPixmap battlePowerImage(_battlePowerPictures[0]);
    ui->lbl_BattlePowerPicture->setPixmap(battlePowerImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                            _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    ui->lbl_BattlePowerDigit->setStyleSheet("QLabel {color: #FAAB21; }");
    ui->lbl_BattlePowerDigit->setText(QString::number(_battlePower));
    ui->lbl_BattlePowerDigit->setStyleSheet("font: 28pt;");

    //this is not work
//    qDebug() << "Current Size of The Hand, H:" << ui->widget->size().height();
//    ui->widget->size().setHeight( ui->widget->size().height() + 10);
//    qDebug() << "New Size of The Hand, H:" << ui->widget->size().height();


    qDebug() << "The Size of The Gamer Widget " << size();

    connect(ui->widget, &Hand::adjustSize, this, &GamerWidget::_adjustSizeSlot);

    //trying to resize manually - failed.

    //ui->widget->setMinimumHeight(0.45*size().height());
    //ui->widget->setMaximumHeight(0.45*size().height());
    //ui->btn_class_1->setMinimumHeight(0.45*size().height());
    //ui->btn_class_1->setMaximumHeight(0.45*size().height());

    //connect the Hand with the Game... (checking the possibility for the Card to be played)
    connect(ui->widget, &Hand::_cardIsSendedToTheGameCheck, this, &GamerWidget::_slotSendTheCardToTheGameCheck);

    //connect the Hand with the answer from The_Game Crad check slot;
    connect(this, &GamerWidget::_signalCardIsRejectedToBePlayed, ui->widget, &Hand::_slotCardIsRejectedToBePlayed);

}

GamerWidget::~GamerWidget()
{
    delete ui;
}

bool GamerWidget::is_MainPlayer() const
{
    return _is_MainPlayer;
}

void GamerWidget::setIs_MainPlayer(bool is_MainPlayer)
{
    _is_MainPlayer = is_MainPlayer;
}

void GamerWidget::redraw_as_a_secondary_player()
{

    ui->btn_auto_advice->hide();
    ui->btn_diplomacy->hide();
    ui->btn_fast_action->hide();
    ui->btn_Test->hide();

    //hide if secondary!
    ui->widget->hide();

}



void GamerWidget::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void GamerWidget::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void GamerWidget::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void GamerWidget::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void GamerWidget::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void GamerWidget::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void GamerWidget::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void GamerWidget::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void GamerWidget::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void GamerWidget::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void GamerWidget::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void GamerWidget::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void GamerWidget::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}





void GamerWidget::passCardsDecksToHandsWidget()
{

    ui->widget->setMonsersDeck(_monstersDeck);
    ui->widget->setAmplifiersDeck(_amplifiersDeck);
    ui->widget->setArmorAmplifiersDeck(_armorAmplifiersDeck);
    ui->widget->setArmorDeck(_armorDeck);
    ui->widget->setBattleAmplifiersDeck(_battleAmplifiersDeck);
    ui->widget->setCursesDeck(_cursesDeck);
    ui->widget->setLevelUpDeck(_levelUpDeck);
    ui->widget->setProfessionsDeck(_professionsDeck);
    ui->widget->setRacesDeck(_racesDeck);
    ui->widget->setSpecialMechanicsDeck(_specialMechanicsDeck);
    ui->widget->setSpecialMechanicsTreasureDeck(_specialMechanicsTreasureDeck);
    ui->widget->setThingsAmplifiersDeck(_thingsAmplifiersDeck);
    ui->widget->setWeaponsDeck(_weaponsDeck);
}

void GamerWidget::addTheCardToHandsWidget(SimpleCard card)
{
    ui->widget->addNewCardToHands(card);
    _cardsOnHandsGamerWidgetProperty.push_back(card);

    //changing the values for Secondary players:

    if (!card.first) ui->wt_CardsOnHandsSecondary->_slot_updateCardsOnHandsDoors(++_totalDoorsOnHands);
    else ui->wt_CardsOnHandsSecondary->_slot_updateCardsOnHandsTreasures(++_totalTreasuresOnHands);




}

bool GamerWidget::eventFilter(QObject *o, QEvent *e)
{

    if (o == ui->btn_class_1)  {
        if (e->type() == QEvent::Enter) {
            qDebug() << "Mouse Enters Area!";
            _currentCardToShowInCentre = {0,1777}; //no Class
            _showCardsTimer->start(static_cast<int>(_timeToShowTheCard));
            _currentCardToShowNearItsPosition.card = {0,1777};
            _currentCardToShowNearItsPosition.positionTopLeft = { QWidget::mapToGlobal(ui->btn_class_1->pos()).x(),
                                                                  QWidget::mapToGlobal(ui->btn_class_1->pos()).y()};
            _currentCardToShowNearItsPosition.positionBottomRight = { QWidget::mapToGlobal(ui->btn_class_1->pos()).x() + ui->btn_class_1->width(),
                                                                  QWidget::mapToGlobal(ui->btn_class_1->pos()).y() + ui->btn_class_1->height()};

            return true;
        }
        else if (e->type() == QEvent::Leave) {
            qDebug() << "Mouse Leaves Area!";
            if (_showCardsTimer->isActive()) _showCardsTimer->stop();
            emit _hideTheCardInCentre(true); //close the card!
            return true;
        }
        else {
            return QWidget::eventFilter(o, e);
        }

    }
    if (o == ui->btn_race_1)  {
        if (e->type() == QEvent::Enter) {
            qDebug() << "Mouse Enters Area!";
            _currentCardToShowInCentre = {0,0}; //no Race
            _showCardsTimer->start(static_cast<int>(_timeToShowTheCard));
            _currentCardToShowNearItsPosition.card = {0,0};
            _currentCardToShowNearItsPosition.positionTopLeft = { QWidget::mapToGlobal(ui->btn_race_1->pos()).x(),
                                                                  QWidget::mapToGlobal(ui->btn_race_1->pos()).y()};
            _currentCardToShowNearItsPosition.positionBottomRight = { QWidget::mapToGlobal(ui->btn_race_1->pos()).x() + ui->btn_class_1->width(),
                                                                  QWidget::mapToGlobal(ui->btn_race_1->pos()).y() + ui->btn_class_1->height()};

            return true;
        }
        else if (e->type() == QEvent::Leave) {
            qDebug() << "Mouse Leaves Area!";
            if (_showCardsTimer->isActive()) _showCardsTimer->stop();
            emit _hideTheCardInCentre(true); //close the card!
            return true;
        }
        else {
            return QWidget::eventFilter(o, e);
        }

    }


    else {
        return QWidget::eventFilter(o, e);
    }

}

void GamerWidget::_representTheCardInCenterSlot()
{
    emit _representTheCardInCentre(_currentCardToShowNearItsPosition);
}

void GamerWidget::_representTheCardFromHandsInCentre(PositionedCard card)
{
    emit _representTheCardInCentre(card);

}

void GamerWidget::_hideTheCardInCentreSlot(bool)
{
    emit _hideTheCardInCentre(true);
}


//Attention!!!
//Bad Code!!! To change these coeffisients to be built-int in the class;
void GamerWidget::_changeTheGamerLevel(int levelDelta)
{
    _gamerLevel = _gamerLevel + levelDelta;

    if (_gamerLevel < 1) {
        _gamerLevel = 1;
    }
    else if (_gamerLevel > 10) {
        _gamerLevel = 10; //Win!

#ifdef DEBUG_GAMER_WIDGET
        _gamerLevel = 1;
#endif

    }






    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();



    QPixmap levelImage(_levelsPictures[_gamerLevel-1]);
    ui->lbl_Level->setPixmap(levelImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                               _race_class_btn_size_height*HW_Screen_Size_Height,
                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void GamerWidget::_slotTestGamerLevels()
{
    _changeTheGamerLevel(1);


}

void GamerWidget::_slotStartTestCards()
{
    _testBtnIsPressed = !_testBtnIsPressed;
    if (_testBtnIsPressed) _testTimer->start();
    else {
        if (_testTimer->isActive()) _testTimer->stop();
    }

}

void GamerWidget::_changeTheGamerBattlePower(int battlePowerDelta)
{

    _battlePower += battlePowerDelta;

    ui->lbl_BattlePowerDigit->setText(QString::number(_battlePower));

    unsigned int pictureToShow = 0;

    if (_battlePower < 4) {

        pictureToShow = 0;

    }
    else if ((_battlePower > 3) && (_battlePower < 7)) {

        pictureToShow = 1;

    }
    else if ((_battlePower > 6) && (_battlePower < 10)) {

        pictureToShow = 2;

    }
    else if ((_battlePower > 9) && (_battlePower < 13)) {

        pictureToShow = 3;

    }
    else if ((_battlePower > 12) && (_battlePower < 16)) {

        pictureToShow = 4;

    }
    else if ((_battlePower) > 15 && (_battlePower < 19)) {

             pictureToShow = 5;

    }
    else if (_battlePower > 18) {

             pictureToShow = 6;

    }

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    QPixmap battlePowerImage(_battlePowerPictures[pictureToShow]);
    ui->lbl_BattlePowerPicture->setPixmap(battlePowerImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                                            _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation));


}


//This slot doesn't imply current Level of the Gamer!

void GamerWidget::_slotTestGamerBattlePower()
{
    ++_currentDeltaToBattlePower;
    if (_currentDeltaToBattlePower > 50) {
        _battlePower = 1;
        _currentDeltaToBattlePower = 0;
    }
    _changeTheGamerBattlePower(1);

}

void GamerWidget::_hideHandSecondaryPlayerWidget()
{
    ui->wt_CardsOnHandsSecondary->hide();
}

void GamerWidget::_adjustSizeSlot()
{
    QWidget::adjustSize();
    //ui->widget->adjustSize(true);
    emit _signalAdjustSize(true);
}

void GamerWidget::_slotSendTheCardToTheGameCheck(PositionedCard card)
{
    emit _signalSendTheCardToTheGameCheck(card);
}

void GamerWidget::_slotCardIsRejectedToBePlayed(bool rejected)
{
    emit _signalCardIsRejectedToBePlayed(rejected);
}


