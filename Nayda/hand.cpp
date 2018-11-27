#include "hand.h"
#include "ui_hand.h"
#include "munchkinglobaldefines.h"

Hand::Hand(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hand)
{
    ui->setupUi(this);

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //setup the koefficients;
    const float handCard_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float handCard_btn_size_width = 0.0415f;
    const float handCard_btn_size_height = handCard_btn_size_geometric_width_to_height_ratio*handCard_btn_size_width;

    //set the maximum Height of the "Hand" Widget
    setMaximumHeight(HW_Screen_Size_Height*handCard_btn_size_height);

    //place picture
#ifndef USE_RESOURCES
    QPixmap pxmp_HandCover("Pictures/Hand/sunRiseMiddle.png");
#else
    QPixmap pxmp_HandCover(":/Pictures/Hand/sunRiseMiddle.png");
#endif

    QPalette plte_HandCover;
    plte_HandCover.setBrush(backgroundRole(),
    QBrush(pxmp_HandCover.scaled(handCard_btn_size_width*HW_Screen_Size_Width,
                                                             handCard_btn_size_height*HW_Screen_Size_Height,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    //do not fill the background to make it transparent
    setAutoFillBackground(false);
    //setPalette(plte_HandCover);

    _showCardsTimer = new QTimer(this);
    _showCardsTimer->setSingleShot(true);
    //connect timeout issue
    connect(_showCardsTimer, &QTimer::timeout, this, &Hand::SlotShowTheCardInCentreSlot);
//    connect(_showCardsTimer, &QTimer::timeout ,this, &Hand::_showTheCardNearItsPositionSlot);
    connect(this, &Hand::_cardIsPreparedToBePlayed, this, &Hand::_slotCardIsPreparedToBePlayedFromHand);
//    qDebug() << "The Size Of Cards On Hands, Height: " << size().height();

#ifdef __linux__
    _debounceTimer = new QTimer(this);
    _debounceTimer->setSingleShot(true);
    connect(_debounceTimer, &QTimer::timeout, this, &Hand::SlotDebounceTimerHandler);
#endif


}


void Hand::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void Hand::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void Hand::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void Hand::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void Hand::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void Hand::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void Hand::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void Hand::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void Hand::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void Hand::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void Hand::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void Hand::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void Hand::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}

Hand::~Hand()
{
    delete ui;
}

void Hand::addNewCardToHands(SimpleCard card)
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

    QPushButton* newCard = new QPushButton();

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.019f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;



    newCard->setMaximumWidth(handCardSizeWidht*HW_Screen_Size_Width*2);
    newCard->setMaximumHeight(handCardSizeHeight*HW_Screen_Size_Height*2);
    newCard->setMinimumWidth(handCardSizeWidht*HW_Screen_Size_Width*2);
    newCard->setMinimumHeight(handCardSizeHeight*HW_Screen_Size_Height*2);

    //qDebug() << "Current Picture Address: " << currentPictureAddress;
    QPixmap pxmpBtnMainRepresenter(currentPictureAddress);
    QPalette plteBtnMainRepresenter;
    plteBtnMainRepresenter.setBrush(newCard->backgroundRole(),
    QBrush(pxmpBtnMainRepresenter.scaled(handCardSizeWidht*HW_Screen_Size_Width*2,
                                                             handCardSizeHeight*HW_Screen_Size_Height*2,
                                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->layout()->addWidget(newCard);
    //ui->verticalLayout->addWidget(_theBtnMainRepresenter);
    //ui->verticalLayout->setAlignment(Qt::AlignHCenter);
    this->layout()->setAlignment(Qt::AlignHCenter);
    newCard->setFlat(true);
    newCard->setAutoFillBackground(true);
    newCard->setPalette(plteBtnMainRepresenter);

    //set The Filter:
    newCard->installEventFilter(this);


    _cardsVector.push_back(newCard);
    _cardsOnHandsHandsWidgetProperty.push_back(card);
}

void Hand::SlotShowTheCardInCentreSlot()
{
    emit SignalShowTheCard(_currentCardToShowNearItsPosition);
}


bool Hand::eventFilter(QObject *o, QEvent *e)
{

    for (unsigned int var = 0; var < _cardsVector.size(); ++var) {
        if (o == _cardsVector[var]) {

            if (e->type() == QEvent::Enter) {
                qDebug() << "Mouse Enters Area!";
#ifdef __linux__
                if (_debounceTimer->isActive())
                    _debounceTimer->stop();
#endif
                _currentCardToShowInCentre = _cardsOnHandsHandsWidgetProperty[var]; //no Class
//                qDebug() << "Size of the card, X: " << QWidget::mapToGlobal(_cardsVector[var]->pos()).x();
//                qDebug() << "Size of the card, Y: " <<  QWidget::mapToGlobal(_cardsVector[var]->pos()).y();
//                qDebug() << "Size of the card, H: " << _cardsVector[var]->height();
//                qDebug() << "Size of the card, W: " << _cardsVector[var]->width();
                _currentCardToShowNearItsPosition.SetSimpleCard(_cardsOnHandsHandsWidgetProperty[var]);
                qDebug() << "Hand.cpp : Position top Left X: " << _cardsVector[var]->pos().x();
                qDebug() << "Hand.cpp :Position top Left Y: " << _cardsVector[var]->pos().y();
                _currentCardToShowNearItsPosition.SetPositionTopLeft({ _cardsVector[var]->pos().x(),
                                                                       _cardsVector[var]->pos().y()});
                _currentCardToShowNearItsPosition.SetPositionBottomRight({_cardsVector[var]->pos().x() + _cardsVector[var]->width(),
                                                                          _cardsVector[var]->pos().y() + _cardsVector[var]->height()});
                qDebug() << "Hand.cpp :Position bottom Right X: " <<_cardsVector[var]->pos().x() + _cardsVector[var]->width();
                qDebug() << "Hand.cpp :Position bottom Right Y: " << _cardsVector[var]->pos().y() + _cardsVector[var]->height();

                _showCardsTimer->start(static_cast<uint32_t>(_timeToShowTheCard));
                return true;
            }
            else if (e->type() == QEvent::Leave) {
                qDebug() << "Mouse Leaves Area!";

#ifdef __linux__
                _debounceTimer->start(_debounceTime);
                //if (_showCardsTimer->isActive()) _showCardsTimer->stop();
                return true;
#else

                if (_showCardsTimer->isActive()) _showCardsTimer->stop();
                emit SignalHideTheCard(true);
                return true;
#endif
            }
            else if (e->type() == QEvent::MouseButtonPress) {

                qDebug() << "Button Pressed " << var;
                emit _cardIsPreparedToBePlayed(var);
                emit SignalHideTheCard(true);

            }
            else {
                return QWidget::eventFilter(o, e);
            }
        }
    }
    return QWidget::eventFilter(o, e);
}

void Hand::_slotCardIsPreparedToBePlayedFromHand(unsigned int cardId)
{
    //this is not work.
    //size().setHeight(size().height() + movingUpCardDelta *2);
    //qDebug() << "The Size Of Cards On Hands, Height: " << size().height();

    if (_cardIsReadyToBePlayed.thereIsCardToBePulledDown == true) {

        if (_cardIsReadyToBePlayed.cardID == cardId) // Gamer pressed the same card for the second time! Play it, if possible!
        {
            qDebug() << "Trying to play the card! Send the card to The_Game check. ";

            //send the card to the Game check;

            PositionedCard cardToBeSendForTheCheck;
            cardToBeSendForTheCheck.SetSimpleCard(_cardIsReadyToBePlayed.card);

            cardToBeSendForTheCheck.SetPositionTopLeft({ _cardsVector[cardId]->pos().x(),
                                                         _cardsVector[cardId]->pos().y()});
            cardToBeSendForTheCheck.SetPositionBottomRight({ _cardsVector[cardId]->pos().x() + _cardsVector[cardId]->width(),
                                                             _cardsVector[cardId]->pos().y() + _cardsVector[cardId]->height()});

            //Debug only...
            //returning the card to previous position!
            QPoint currPos = _cardsVector[cardId]->pos();
            _cardsVector[cardId]->move(currPos.x(), currPos.y() + movingUpCardDelta);
            _cardIsReadyToBePlayed.thereIsCardToBePulledDown = false;
            emit _cardIsSendedToTheGameCheck(cardToBeSendForTheCheck);
        }
        else {
            //returning the previous card to previous position!
            QPoint currPos = _cardsVector[_cardIsReadyToBePlayed.cardID]->pos();
            _cardsVector[_cardIsReadyToBePlayed.cardID]->move(currPos.x(), currPos.y() + movingUpCardDelta); //returning the card to previous position!

            //changing the new card's position! (debug). In real - to send the card to The_Game check;
            currPos = _cardsVector[cardId]->pos();
            _cardsVector[cardId]->move(currPos.x(), currPos.y() - movingUpCardDelta);

            //rewrite the card to the special property
            _cardIsReadyToBePlayed.card = _cardsOnHandsHandsWidgetProperty[cardId];
            _cardIsReadyToBePlayed.cardID = cardId;
            _cardIsReadyToBePlayed.thereIsCardToBePulledDown = true;
        }
    }
    else {

        QPoint currPos = _cardsVector[cardId]->pos();
        _cardsVector[cardId]->move(currPos.x(), currPos.y() - movingUpCardDelta);
        //setting the cardToBeChecked;
        _cardIsReadyToBePlayed.card = _cardsOnHandsHandsWidgetProperty[cardId];
        _cardIsReadyToBePlayed.cardID = cardId;
        _cardIsReadyToBePlayed.thereIsCardToBePulledDown = true;
    }
}

void Hand::_slotCardIsRejectedToBePlayed(bool rejected)
{
    qDebug() << "Is card rejected to be Played? " <<
                (rejected ? "Yes, it was! " : "Not, it wasn't");

    //if we are here, we can be sure that there's card in the
    // "_cardIsReadyToBePlayed"
    //up to be debugged!
    if (!rejected) {
        _removeCardFromHand(_cardIsReadyToBePlayed.card);
        _cardIsReadyToBePlayed.thereIsCardToBePulledDown = false;
    }
}

void Hand::_removeCardFromHand(SimpleCard card)
{
    unsigned int position = 0;
    for (unsigned int var = 0; var < _cardsOnHandsHandsWidgetProperty.size(); ++var) {

        if (((_cardsOnHandsHandsWidgetProperty[var]).first == card.first)
                && ((_cardsOnHandsHandsWidgetProperty[var]).second == card.second)) {

            qDebug() << "The Card with ID: " << _cardsOnHandsHandsWidgetProperty[var].first << ";"
                     << _cardsOnHandsHandsWidgetProperty[var].second
                     << "is deleted from Hand!";
            position = var;
            _cardsOnHandsHandsWidgetProperty.erase(_cardsOnHandsHandsWidgetProperty.begin() + var);
            _cardsOnHandsHandsWidgetProperty.shrink_to_fit();
        }
    }

    _cardsVector[position]->deleteLater();
    _cardsVector.erase(_cardsVector.begin() + position);
    _cardsVector.shrink_to_fit();
    qDebug() << "The card is removed from Hands!" ;
}
