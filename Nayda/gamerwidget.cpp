#include "gamerwidget.h"
#include "ui_gamerwidget.h"

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

    //setup the koefficients;
    const float race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float race_class_btn_size_width = 0.035f;
    const float race_class_btn_size_height = race_class_btn_size_geometric_width_to_height_ratio*race_class_btn_size_width;

    //setup the "card"-race and "card"-class size
    ui->btn_race_1->setMaximumWidth(race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_race_1->setMaximumHeight(race_class_btn_size_height*HW_Screen_Size_Height);
    ui->btn_race_1->setMinimumWidth(race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_race_1->setMinimumHeight(race_class_btn_size_height*HW_Screen_Size_Height);

    ui->btn_class_1->setMaximumWidth(race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_class_1->setMaximumHeight(race_class_btn_size_height*HW_Screen_Size_Height);
    ui->btn_class_1->setMinimumWidth(race_class_btn_size_width*HW_Screen_Size_Width);
    ui->btn_class_1->setMinimumHeight(race_class_btn_size_height*HW_Screen_Size_Height);

    //http://www.prog.org.ru/topic_7215_0.html




    QPixmap pxmp_icon_race_1("Pictures/No_Race_dbg.png");
    QPalette plte_icon_race_1;
    plte_icon_race_1.setBrush(ui->btn_race_1->backgroundRole(),
    QBrush(pxmp_icon_race_1.scaled(race_class_btn_size_width*HW_Screen_Size_Width,
                                                             race_class_btn_size_height*HW_Screen_Size_Height,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    QPixmap pxmp_icon_class_1("Pictures/No_Class_dbg.png");
    QPalette plte_icon_class_1;
    plte_icon_class_1.setBrush(ui->btn_class_1->backgroundRole(),
    QBrush(pxmp_icon_class_1.scaled(race_class_btn_size_width*HW_Screen_Size_Width,
                                                             race_class_btn_size_height*HW_Screen_Size_Height,
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

    qDebug() << "Size of the button, Width: " << race_class_btn_size_width*HW_Screen_Size_Width;
    qDebug() << "Size of the button, Height: " << race_class_btn_size_height*HW_Screen_Size_Height;



    //Initialize the timer for cards show
    _showCardsTimer = new QTimer(this);
    _showCardsTimer->setSingleShot(true);
    //connect timeout issue
    connect(_showCardsTimer, &QTimer::timeout, this, &GamerWidget::_representTheCardInCenterSlot);
    connect(ui->widget, &Hand::_showTheCard, this, &GamerWidget::_representTheCardFromHandsInCentre);



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
}

bool GamerWidget::eventFilter(QObject *o, QEvent *e)
{

    if (o == ui->btn_class_1)  {
        if (e->type() == QEvent::Enter) {
            qDebug() << "Mouse Enters Area!";
            _currentCardToShowInCentre = {0,1777}; //no Class
            _showCardsTimer->start(static_cast<int>(_timeToShowTheCard));

            return true;
        }
        else if (e->type() == QEvent::Leave) {
            qDebug() << "Mouse Leaves Area!";
            if (_showCardsTimer->isActive()) _showCardsTimer->stop();
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

            return true;
        }
        else if (e->type() == QEvent::Leave) {
            qDebug() << "Mouse Leaves Area!";
            if (_showCardsTimer->isActive()) _showCardsTimer->stop();
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
    emit _representTheCardInCentre(_currentCardToShowInCentre);
}

void GamerWidget::_representTheCardFromHandsInCentre(SimpleCard card)
{
    emit _representTheCardInCentre(card);

}


