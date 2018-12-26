#include "gamerwidget.h"
#include "ui_gamerwidget.h"
#include "munchkinglobaldefines.h"

GamerWidget::GamerWidget(QWidget *parent, Player *player) :
    QWidget(parent), ui(new Ui::GamerWidget),
    _player(player)
{
    ui->setupUi(this);

    //https://wiki.qt.io/Qt_Coding_Style/ru

    SetUpWidgetsPerfomance();
    ui->btn_Trade->hide();


    SetUpTestTimer();
    SetUpShowTimer();
    SetUpSignalsSlotsConnections();

    ui->wt_CardsInGameMainPlayer->show();
    ui->btn_HideCardsInGame->hide();
}

GamerWidget::~GamerWidget()
{
    delete ui;
}

bool GamerWidget::is_MainPlayer() const
{
    return _isMainPlayer;
}

void GamerWidget::setIs_MainPlayer(bool is_MainPlayer)
{
    _isMainPlayer = is_MainPlayer;
}

void GamerWidget::RedrawAsASecondaryPlayer(uint32_t opponentOrder)
{
    ui->btn_auto_advice->hide();
    ui->btn_diplomacy->hide();
    ui->btn_fast_action->hide();
    ui->btn_Test->hide();

    //hide if secondary!
    //ui->wt_Hand->hide();
    ui->wt_CardsInGameMainPlayer->hide();
    ui->btn_HideCardsInGame->hide();
    ui->wt_CardsInGameSecondaryPlayer->show();

    //mirror Hand and Cards in Game
    if (opponentOrder <= GamerWidgetPerfomanceValues::totalOpponentsAtTopLayout)
    {
        ui->lyt_Hand->removeWidget(ui->wt_Hand);
        ui->lyt_CardsOnHandsSecondary_Mirror->addWidget(ui->wt_Hand);
        ui->lyt_CardsInGameSecondaryPlayer->removeWidget(ui->wt_CardsInGameSecondaryPlayer);
        ui->lyt_CardsInGameSecondary_Mirror->addWidget(ui->wt_CardsInGameSecondaryPlayer);
    }

}



void GamerWidget::SetDecks(const AllDecksToBePassed& data)
{
    _monstersDeck = data._monstersDeck;
    _amplifiersDeck = data._amplifiersDeck;
    _cursesDeck = data._cursesDeck;
    _professionsDeck = data._professionsDeck;
    _racesDeck = data._racesDeck;
    _specialMechanicsDeck = data._specialMechanicsDeck;

    _armorDeck = data._armorDeck;
    _armorAmplifiersDeck = data._armorAmplifiersDeck;
    _battleAmplifiersDeck = data._battleAmplifiersDeck;
    _levelUpDeck = data._levelUpDeck;
    _specialMechanicsTreasureDeck = data._specialMechanicsTreasureDeck;
    _thingsAmplifiersDeck = data._thingsAmplifiersDeck;
    _weaponsDeck = data._weaponsDeck;

    ui->wt_CardsInGameMainPlayer->SetDecks(data);
    ui->wt_CardsInGameSecondaryPlayer->SetDecks(data);
}

Player *GamerWidget::GetPointerToPlayer() const
{
    return _player;
}

void GamerWidget::SetPointerToPlayer(Player *player)
{
    _player = player;
}

void GamerWidget::SetIsRoomMaster()
{
    _isRoomMaster = true;
    ui->btn_Master->show();
}

void GamerWidget::PassCardsDecksToHandsAndCardsInGameWidgets(const AllDecksToBePassed& data)
{

    ui->wt_Hand->SetDecks(data);
    _cardsInGameObserver->SetDecks(data);
}

void GamerWidget::AddTheCardToHandsWidget(SimpleCard card)
{

    qDebug() << "NAY-002: IsMainPlayer: " << is_MainPlayer();
    qDebug() << "";

    if (_isMainPlayer)
    {
        ui->wt_Hand->AddNewCardToHands(card);
        _cardsOnHandsGamerWidgetProperty.push_back(card);
    }
    else
    {
        //Пока сохранить эти значения
        //changing the values for Secondary players:
        if (!card.first) ui->wt_CardsOnHandsSecondary->SlotUpdateCardsOnHandsDoors(++_totalDoorsOnHands);
        else ui->wt_CardsOnHandsSecondary->SlotUpdateCardsOnHandsTreasures(++_totalTreasuresOnHands);

        //добавить карты в руку и для них
        ui->wt_Hand->AddNewCardToHands(card, false);
        _cardsOnHandsGamerWidgetProperty.push_back(card);
    }
}

bool GamerWidget::eventFilter(QObject *o, QEvent *e)
{

    if (o == ui->btn_class_1)  {
        if (e->type() == QEvent::Enter) {
            //qDebug() << "Mouse Enters Area!";
            _currentCardToShowInCentre = {0,1777}; //no Class
            _showCardsTimer->start(static_cast<int>(_timeToShowTheCard));
            _currentCardToShowNearItsPosition.SetSimpleCard({0,1777});
            _currentCardToShowNearItsPosition.SetPositionTopLeft({ ui->btn_class_1->pos().x(),
                                                                   ui->btn_class_1->pos().y()});
            _currentCardToShowNearItsPosition.SetPositionBottomRight({ ui->btn_class_1->pos().x() + ui->btn_class_1->width(),
                                                                       ui->btn_class_1->pos().y() + ui->btn_class_1->height()});

            return true;
        }
        else if (e->type() == QEvent::Leave) {
            //qDebug() << "Mouse Leaves Area!";
            if (_showCardsTimer->isActive()) _showCardsTimer->stop();
            emit SignalHideTheCardInCentre(true); //close the card!
            return true;
        }
        else {
            return QWidget::eventFilter(o, e);
        }

    }
    if (o == ui->btn_race_1)  {
        if (e->type() == QEvent::Enter) {
            //qDebug() << "Mouse Enters Area!";
            _currentCardToShowInCentre = {0,0}; //no Race
            _showCardsTimer->start(static_cast<int>(_timeToShowTheCard));
            _currentCardToShowNearItsPosition.SetSimpleCard({0,0});
            _currentCardToShowNearItsPosition.SetPositionTopLeft({ ui->btn_race_1->pos().x(),
                                                                   ui->btn_race_1->pos().y()});
            _currentCardToShowNearItsPosition.SetPositionBottomRight({ ui->btn_race_1->pos().x() + ui->btn_class_1->width(),
                                                                       ui->btn_race_1->pos().y() + ui->btn_class_1->height()});
            return true;
        }
        else if (e->type() == QEvent::Leave) {
            //qDebug() << "Mouse Leaves Area!";
            if (_showCardsTimer->isActive()) _showCardsTimer->stop();
            emit SignalHideTheCardInCentre(true); //close the card!
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

void GamerWidget::SlotRepresentTheCardInCentre()
{
    qDebug() << "SlotRepresentTheCardInCentre(): ";
    qDebug() << "POS X: " << ui->wt_Hand->pos().x();
    qDebug() << "POS Y: " << ui->wt_Hand->pos().y();

    _currentCardToShowNearItsPosition.AddBase(pos());
    emit SignalRepresentTheCardInCentre(_currentCardToShowNearItsPosition);
}

void GamerWidget::SlotRepresentTheCardFromHandsScope(PositionedCard card, bool fromHand)
{
    if (fromHand)
    {
        card.AddBase(ui->wt_Hand->pos());
    }
    else // from CardsInGame
    {
        if (_isMainPlayer)
            card.AddBase(ui->wt_CardsInGameMainPlayer->pos());
        else
            card.AddBase(ui->wt_CardsInGameSecondaryPlayer->pos());
    }

    card.AddBase(pos());
    emit SignalRepresentTheCardInCentre(card);
}

void GamerWidget::SlotHideTheCardInCentre(bool)
{
    emit SignalHideTheCardInCentre(true);
}

//Attention!!!
//Bad Code!!! To change these coeffisients to be built-int in the class;
void GamerWidget::SlotChangeTheGamerLevel(int levelDelta)
{
    qDebug() << "NAY-002: SlotChangeTheGamerLevel: levelDelta:" << levelDelta;
    this->SlotChangeTheGamerBattlePower(levelDelta);
    if (levelDelta < 0)
        _gamerLevel -= levelDelta;
    else
        _gamerLevel += levelDelta;

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
    ui->lbl_Level->setPixmap(levelImage.scaled(_raceClassBtnSizeWidth*HW_Screen_Size_Width,
                                               _raceClassBtnSizeHeight*HW_Screen_Size_Height,
                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}


void GamerWidget::DEBUGSlotTestGamerLevels()
{
    SlotChangeTheGamerLevel(1);
}

void GamerWidget::DEBUGSlotStartTestCards()
{
    _testBtnIsPressed = !_testBtnIsPressed;
    if (_testBtnIsPressed) _testTimer->start();
    else {
        if (_testTimer->isActive()) _testTimer->stop();
    }
}

void GamerWidget::SlotChangeTheGamerBattlePower(int battlePowerDelta)
{
    qDebug() << "NAY-002: BattlePower delta: " << battlePowerDelta;

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
    ui->lbl_BattlePowerPicture->setPixmap(battlePowerImage.scaled(_raceClassBtnSizeWidth*HW_Screen_Size_Width,
                                                            _raceClassBtnSizeHeight*HW_Screen_Size_Height / 2,
                                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

//This slot doesn't imply current Level of the Gamer!

void GamerWidget::DEBUGSlotTestGamerBattlePower()
{
    ++_currentDeltaToBattlePower;
    if (_currentDeltaToBattlePower > 50) {
        _battlePower = 1;
        _currentDeltaToBattlePower = 0;
    }
    SlotChangeTheGamerBattlePower(1);

}

void GamerWidget::HideHandSecondaryPlayerWidget()
{
    ui->wt_CardsOnHandsSecondary->hide();
}

void GamerWidget::_adjustSizeSlot()
{
    QWidget::adjustSize();
    //ui->widget->adjustSize(true);
    emit SignalAdjustSize(true);
}

void GamerWidget::SlotSendTheCardToTheGameCheck(PositionedCard card, bool fromHand)
{
    emit SignalSendTheCardToTheGameCheck(card, fromHand);
}

void GamerWidget::SlotCardIsRejectedToBePlayed(bool rejected)
{
    emit SignalCardIsRejectedToBePlayed(rejected);
}

void GamerWidget::SlotHideTradeButton()
{
    ui->btn_Trade->hide();
}

void GamerWidget::SlotShowTradeButton()
{
    qDebug() << "NAY-002: Show Trade Button!!!";
    ui->btn_Trade->show();
}

std::vector<PositionedCard> GamerWidget::GetPositionedCardsFromCardsOnHand(const std::vector<SimpleCard> cards)
{
    return ui->wt_Hand->GetPositionedCards(cards);
}

PositionedCard GamerWidget::GetPositionedCardFromCardsOnHand(SimpleCard card)
{
    return ui->wt_Hand->GetCardPosition(card);
}

std::vector<PositionedCard> GamerWidget::GetPositionedCardsFromCardsInGame(const std::vector<SimpleCard> cards)
{
    if (_isMainPlayer)
        return  ui->wt_CardsInGameMainPlayer->GetPositionedCards(cards);
    else
        return ui->wt_CardsInGameSecondaryPlayer->GetPositionedCards(cards);
}

void GamerWidget::RemoveCardFromHand(SimpleCard card)
{
    ui->wt_Hand->SlotRemoveCardFromHand(card);
    if (!card.first) ui->wt_CardsOnHandsSecondary->SlotUpdateCardsOnHandsDoors(--_totalDoorsOnHands);
    else ui->wt_CardsOnHandsSecondary->SlotUpdateCardsOnHandsTreasures(--_totalTreasuresOnHands);

}

void GamerWidget::RemoveCardsFromCardsInGame(std::vector<SimpleCard> cards)
{    
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        if (_cardsInGameObserver != nullptr)
            _cardsInGameObserver->RemoveCard(cards[var]);

        if (_isMainPlayer)
        {
            ui->wt_CardsInGameMainPlayer->RemoveCard(cards[var]);
        }
        else
        {
            ui->wt_CardsInGameSecondaryPlayer->RemoveCard(cards[var]);
        }
    }

}

QPoint GamerWidget::ProvideSelfPosition()
{
    return pos();
}

QPoint GamerWidget::ProvideHandPosition()
{
    return ui->wt_Hand->pos(); //Relative to Gamer Widget.
}

void GamerWidget::SetGamerName(const QString &gamerName)
{
    ui->lbl_Avatar->setText(gamerName);
    _playerName = gamerName;
    _cardsInGameObserver->SetPlayerName(gamerName);
}

QPoint GamerWidget::ProvideCardsInGamePosition() const
{
    if (_isMainPlayer)
        return ui->wt_CardsInGameMainPlayer->pos();
    else
        return ui->wt_CardsInGameSecondaryPlayer->pos();

}

QSize GamerWidget::ProvideExpectedCardsInGameSize() const
{
    if (_isRoomMaster)
    {
        if (_isMainPlayer)
        {
            return QSize(ui->btn_Master->size().width(),ui->btn_Avatar->pos().y() - ui->btn_Master->pos().y() );
        }
        else
        {
            return QSize(ui->btn_Master->size().width(),ui->lbl_Avatar->pos().y() - ui->btn_Master->pos().y() );
        }
    }
    else
    {
        if (_isMainPlayer)
        {
            return QSize(ui->btn_Avatar->size().width(),ui->btn_Avatar->pos().y() - ui->lbl_Avatar->pos().y() );
        }
        else
        {
            return QSize(ui->btn_Avatar->size().width(),ui->btn_Avatar->pos().y() - ui->lbl_Avatar->pos().y() );
        }
    }


}

QSize GamerWidget::ProvideAvatarSize() const
{
    return ui->btn_Avatar->size();
}

QSize GamerWidget::ProvideCardOnHandSize() const
{
    return ui->wt_Hand->ProvideCardSize();
}

void GamerWidget::SlotShowCardsInGame()
{
    _cardsInGameObserver->show();
}

void GamerWidget::SlotHideCardsInGame()
{
    _cardsInGameObserver->hide();
}

void GamerWidget::SlotAddCardToCardsInGame(CardInGame card)
{
    _cardsInGameObserver->AddCard(card);
    ui->wt_CardsInGameMainPlayer->AddCardToCardsInGame(card);
}

void GamerWidget::SlotDeleteCardFromCardsInGame(SimpleCard card)
{
    _cardsInGameObserver->RemoveCard(card);
}

void GamerWidget::SetUpSignalsSlotsConnections()
{

    connect(ui->wt_Hand, &Hand::adjustSize, this, &GamerWidget::_adjustSizeSlot);

    //connect the Hand with the Game... (checking the possibility for the Card to be played)
    connect(ui->wt_Hand, &Hand::SignalCardIsSendedToTheGameCheck,
            [this](PositionedCard card) {SlotSendTheCardToTheGameCheck(card, true);});

    //connect the Hand with the answer from The_Game Card check slot;
    connect(this, &GamerWidget::SignalCardIsRejectedToBePlayed,
            ui->wt_Hand, &Hand::SlotCardIsRejectedToBePlayed);

    connect(ui->btn_Trade, &QPushButton::pressed, [this]{emit SignalTradeButtonWasPressed();});
    connect(ui->wt_Hand, &Hand::SignalReportCardPosition,
            [this](PositionedCard card){emit SignalReportPostionedCard(card);});
    connect(this, &GamerWidget::SignalGetPositionedCard, ui->wt_Hand, &Hand::SlotGetCardPostion);

    connect(ui->btn_Avatar, &QPushButton::pressed, this, &GamerWidget::SlotShowCardsInGame);

}

void GamerWidget::SetUpTestTimer()
{
#ifdef DEBUG_GAMER_WIDGET

    _testTimer = new QTimer();
    _testTimer->setInterval(1000);
    _testTimer->setSingleShot(false);

    connect(ui->btn_Test, &QPushButton::clicked, this, &GamerWidget::DEBUGSlotStartTestCards);
    connect(_testTimer, &QTimer::timeout, this, &GamerWidget::DEBUGSlotTestGamerLevels);
    connect(_testTimer, &QTimer::timeout, this, &GamerWidget::DEBUGSlotTestGamerBattlePower);

#endif
}

void GamerWidget::SetUpShowTimer()
{
    //Initialize the timer for cards show
    _showCardsTimer = new QTimer(this);
    _showCardsTimer->setSingleShot(true);
    //connect timeout issue
    connect(_showCardsTimer, &QTimer::timeout, this, &GamerWidget::SlotRepresentTheCardInCentre);
    connect(ui->wt_Hand, &Hand::SignalShowTheCard,
            [this](PositionedCard card){ SlotRepresentTheCardFromHandsScope(card, true);});
    connect(ui->wt_Hand, &Hand::SignalHideTheCard, this, &GamerWidget::SlotHideTheCardInCentre);
    connect(ui->wt_CardsInGameMainPlayer, &CardsInGame::SignalShowTheCard,
            [this](PositionedCard card){ SlotRepresentTheCardFromHandsScope(card, false);});
    connect(ui->wt_CardsInGameMainPlayer, &CardsInGame::SignalHideTheCard,
            this, &GamerWidget::SlotHideTheCardInCentre);
    connect(ui->wt_CardsInGameSecondaryPlayer, &CardsInGame::SignalShowTheCard,
            [this](PositionedCard card){ SlotRepresentTheCardFromHandsScope(card, false);});
    connect(ui->wt_CardsInGameSecondaryPlayer, &CardsInGame::SignalHideTheCard,
            this, &GamerWidget::SlotHideTheCardInCentre);

}

void GamerWidget::SetUpWidgetsPerfomance()
{
    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    qDebug() << "NAY-002: void GamerWidget::SetUpWidgetsPerfomance()";
    ui->wt_CardsInGameMainPlayer->SetUpMainWindowSize(QSize(HW_Screen_Size_Width,HW_Screen_Size_Height));
    ui->wt_CardsInGameSecondaryPlayer->SetUpMainWindowSize(QSize(HW_Screen_Size_Width,HW_Screen_Size_Height));

    //Hide odds
    ui->btn_race_2->hide();
    ui->lbl_halfblood->hide();
    ui->btn_class_2->hide();
    ui->lbl_supermunchkin->hide();
    ui->btn_Master->hide();
    ui->wt_CardsInGameSecondaryPlayer->hide();

    //setup the "card"-race and "card"-class size
    ui->btn_race_1->setMaximumWidth(_raceClassBtnSizeWidth*HW_Screen_Size_Width);
    ui->btn_race_1->setMaximumHeight(_raceClassBtnSizeHeight*HW_Screen_Size_Height);
    ui->btn_race_1->setMinimumWidth(_raceClassBtnSizeWidth*HW_Screen_Size_Width);
    ui->btn_race_1->setMinimumHeight(_raceClassBtnSizeHeight*HW_Screen_Size_Height);

    ui->btn_class_1->setMaximumWidth(_raceClassBtnSizeWidth*HW_Screen_Size_Width);
    ui->btn_class_1->setMaximumHeight(_raceClassBtnSizeHeight*HW_Screen_Size_Height);
    ui->btn_class_1->setMinimumWidth(_raceClassBtnSizeWidth*HW_Screen_Size_Width);
    ui->btn_class_1->setMinimumHeight(_raceClassBtnSizeHeight*HW_Screen_Size_Height);

    //http://www.prog.org.ru/topic_7215_0.html

#ifndef USE_RESOURCES
    QPixmap pxmp_icon_race_1("Pictures/No_Race_dbg.png");
#else
    QPixmap pxmp_icon_race_1(":/Pictures/No_Race_dbg.png");
#endif

    QPalette plte_icon_race_1;
    plte_icon_race_1.setBrush(ui->btn_race_1->backgroundRole(),
    QBrush(pxmp_icon_race_1.scaled(_raceClassBtnSizeWidth*HW_Screen_Size_Width,
                                                             _raceClassBtnSizeHeight*HW_Screen_Size_Height,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
#ifndef USE_RESOURCES
    QPixmap pxmp_icon_class_1("Pictures/No_Class_dbg.png");
#else
    QPixmap pxmp_icon_class_1(":/Pictures/No_Class_dbg.png");
#endif

    QPalette plte_icon_class_1;
    plte_icon_class_1.setBrush(ui->btn_class_1->backgroundRole(),
    QBrush(pxmp_icon_class_1.scaled(_raceClassBtnSizeWidth*HW_Screen_Size_Width,
                                                             _raceClassBtnSizeHeight*HW_Screen_Size_Height,
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

    //forming the vector of pictures;
    //set the initial levelel's pictures.

    QPixmap levelImage(_levelsPictures[_gamerLevel-1]);
    ui->lbl_Level->setPixmap(levelImage.scaled(_raceClassBtnSizeWidth*HW_Screen_Size_Width,
                                               _raceClassBtnSizeHeight*HW_Screen_Size_Height,
                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    //set The BattlePower Picture and Digit Lables;
    QPixmap battlePowerImage(_battlePowerPictures[0]);
    ui->lbl_BattlePowerPicture->setPixmap(battlePowerImage.scaled(_raceClassBtnSizeWidth*HW_Screen_Size_Width,
                                                            _raceClassBtnSizeHeight*HW_Screen_Size_Height / 2,
                                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    ui->lbl_BattlePowerDigit->setStyleSheet("QLabel {color: #FAAB21; }");
    ui->lbl_BattlePowerDigit->setText(QString::number(_battlePower));
    ui->lbl_BattlePowerDigit->setStyleSheet("font: 28pt;");


    _cardsInGameObserver = new CardsInGameObserver(QSize(HW_Screen_Size.width(),
                                                         HW_Screen_Size.height()), QString("Player1"));


}

QSize GamerWidget::GetCardOnHandSize()
{
    return ui->wt_Hand->ProvideCardSize();
}

void GamerWidget::SlotShowLastCardInGameAdded()
{
    if (_isMainPlayer)
        ui->wt_CardsInGameMainPlayer->ShowLastCardAdded(_isMainPlayer);
    else
        ui->wt_CardsInGameSecondaryPlayer->ShowLastCardAdded(false);
}

QPoint GamerWidget::ProvidePositionOfTheLastCardAddedToCardsInGame() const
{
    if (_isMainPlayer)
        return ui->wt_CardsInGameMainPlayer->ProvidePositionOfTheLastAddedCard();
    else
        return ui->wt_CardsInGameSecondaryPlayer->ProvidePositionOfTheLastAddedCard();
}



