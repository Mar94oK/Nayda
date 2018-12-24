#include "hand.h"
#include "ui_hand.h"
#include "munchkinglobaldefines.h"

Hand::Hand(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hand)
{
    ui->setupUi(this);

    _showCardsTimer = new QTimer(this);
    _showCardsTimer->setSingleShot(true);
    connect(_showCardsTimer, &QTimer::timeout, this, &Hand::SlotShowTheCardInCentreSlot);
    connect(this, &Hand::SignalCardIsPreparedToBePlayed, this, &Hand::SlotCardIsPreparedToBePlayedFromHand);

#ifdef __linux__
    _debounceTimer = new QTimer(this);
    _debounceTimer->setSingleShot(true);
    connect(_debounceTimer, &QTimer::timeout, this, &Hand::SlotDebounceTimerHandler);
#endif

}



void Hand::SetDecks(const AllDecksToBePassed &data)
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
}

Hand::~Hand()
{
    delete ui;
}

void Hand::AddNewCardToHands(SimpleCard card, bool isMainPlayer)
{

    QPushButton* newCard = new QPushButton();

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    QString currentPictureAddress = "";
    if (isMainPlayer)
    {
        _cardSize.setWidth(static_cast<int32_t>(GeometricLimitations::handCardSizeWidht
                                                *GeometricLimitations::handCardMainGamerSizeRatio
                                                *HW_Screen_Size_Width
                                                ));
        _cardSize.setHeight(static_cast<int32_t>(GeometricLimitations::handCardSizeHeight
                                                 *GeometricLimitations::handCardMainGamerSizeRatio
                                                 *HW_Screen_Size_Height
                                                 ));

       newCard->setMaximumSize(_cardSize);
       newCard->setMinimumSize(_cardSize);

        currentPictureAddress = GetCardPictureAddress(card);

        //Фильтр должен быть установлен только для карт главного игрока в случае с рукой -
        //Нельзя давать просматривать чужие карты.
        //Но, в принципе, можно будет потом сделать подобную карту. =)))
        //set The Filter:
        newCard->installEventFilter(this);
    }
    else
    {
        _cardSize.setWidth(static_cast<int32_t>(GeometricLimitations::handCardSizeWidht*HW_Screen_Size_Width));
        _cardSize.setHeight(static_cast<int32_t>(GeometricLimitations::handCardSizeHeight*HW_Screen_Size_Height));

        newCard->setMaximumSize(_cardSize);
        newCard->setMinimumSize(_cardSize);

        if (card.first)
            currentPictureAddress = ":/Pictures/stacksLevels/TreasureStack5_SingleCard.png";
        else
            currentPictureAddress = ":/Pictures/stacksLevels/DoorsStack5_SingleCard.png";

        //newCard->installEventFilter(this);
    }

    QPixmap pxmpBtnMainRepresenter(currentPictureAddress);
    QPalette plteBtnMainRepresenter;
    plteBtnMainRepresenter.setBrush(newCard->backgroundRole(),
    QBrush(pxmpBtnMainRepresenter.scaled(_cardSize.width(),
                                         _cardSize.height(),
                                         Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->layout()->addWidget(newCard);
    //ui->verticalLayout->addWidget(_theBtnMainRepresenter);
    //ui->verticalLayout->setAlignment(Qt::AlignHCenter);
    this->layout()->setAlignment(Qt::AlignHCenter);
    newCard->setFlat(true);
    newCard->setAutoFillBackground(true);
    newCard->setPalette(plteBtnMainRepresenter);

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
//                qDebug() << "Mouse Enters Area!";
#ifdef __linux__
                if (_debounceTimer->isActive())
                    _debounceTimer->stop();
#endif
                _currentCardToShowInCentre = _cardsOnHandsHandsWidgetProperty[var]; //no Class

                _currentCardToShowNearItsPosition.SetSimpleCard(_cardsOnHandsHandsWidgetProperty[var]);
                _currentCardToShowNearItsPosition.SetPositionTopLeft({ _cardsVector[var]->pos().x(),
                                                                       _cardsVector[var]->pos().y()});
                _currentCardToShowNearItsPosition.SetPositionBottomRight({_cardsVector[var]->pos().x() + _cardsVector[var]->width(),
                                                                          _cardsVector[var]->pos().y() + _cardsVector[var]->height()});

                _showCardsTimer->start(static_cast<int32_t>(_timeToShowTheCard));
                return true;
            }
            else if (e->type() == QEvent::Leave) {
//                qDebug() << "Mouse Leaves Area!";

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
                emit SignalCardIsPreparedToBePlayed(var);
                emit SignalHideTheCard(true);

            }
            else {
                return QWidget::eventFilter(o, e);
            }
        }
    }
    return QWidget::eventFilter(o, e);
}

void Hand::SlotCardIsPreparedToBePlayedFromHand(unsigned int cardId)
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
            emit SignalCardIsSendedToTheGameCheck(cardToBeSendForTheCheck);
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

void Hand::SlotCardIsRejectedToBePlayed(bool rejected)
{
    qDebug() << "Is card rejected to be Played? " <<
                (rejected ? "Yes, it was! " : "Not, it wasn't");

    //if we are here, we can be sure that there's card in the
    // "_cardIsReadyToBePlayed"
    //up to be debugged!
    if (!rejected)
    {
        SlotRemoveCardFromHand(_cardIsReadyToBePlayed.card);
        _cardIsReadyToBePlayed.thereIsCardToBePulledDown = false;
    }
}

void Hand::SlotRemoveCardFromHand(SimpleCard card)
{
    unsigned int position = 0;
    for (unsigned int var = 0; var < _cardsOnHandsHandsWidgetProperty.size(); ++var) {

        if (((_cardsOnHandsHandsWidgetProperty[var]).first == card.first)
                && ((_cardsOnHandsHandsWidgetProperty[var]).second == card.second))
        {

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

PositionedCard Hand::GetCardPosition(SimpleCard card)
{
    //Define whether there's such card in the hand.
    for (uint32_t var = 0; var < _cardsOnHandsHandsWidgetProperty.size(); ++var)
    {
        if (_cardsOnHandsHandsWidgetProperty[var] == card)
        {
            PositionedCard posCard;
            posCard.SetSimpleCard(card);
            //Они добавляются в вектор карт точно в таком же порядке, их ID должны свопадать
            //Им может служить в общем случае индекс массива

            posCard.SetPositionTopLeft({ _cardsVector[var]->pos().x(),
                                                         _cardsVector[var]->pos().y()});
            posCard.SetPositionBottomRight({ _cardsVector[var]->pos().x() + _cardsVector[var]->width(),
                                                             _cardsVector[var]->pos().y() + _cardsVector[var]->height()});
            return posCard;

        }
    }
    qDebug() << "NAY-002: ERROR WHILE PositionedCard Hand::GetCardPosition(SimpleCard card)"
             << "No card found!";

    return PositionedCard();

}

std::vector<PositionedCard> Hand::GetPositionedCards(const std::vector<SimpleCard> &cards)
{
    std::vector<PositionedCard> posCards;

    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        posCards.push_back(GetCardPosition(cards[var]));
    }

    return posCards;
}

QSize Hand::ProvideCardSize()
{
    return _cardSize;
}

QString Hand::GetCardPictureAddress(SimpleCard card)
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


    if (!card.first)
    { //door
        _monstersIterator = _monstersDeck.find(static_cast <int> (card.second));
        if (_monstersIterator != _monstersDeck.end())
            return (*_monstersIterator).second.pictureAddress();

        _amplifiersIterator = _amplifiersDeck.find(static_cast <int> (card.second));
        if (_amplifiersIterator != _amplifiersDeck.end())
            return (*_amplifiersIterator).second.pictureAddress();

        _cursesIterator = _cursesDeck.find(static_cast <int> (card.second));
        if (_cursesIterator != _cursesDeck.end())
            return (*_cursesIterator).second.pictureAddress();

        _professionsIterator = _professionsDeck.find(static_cast <int> (card.second));
        if (_professionsIterator != _professionsDeck.end())
            return (*_professionsIterator).second.pictureAddress();

        _racesIterator = _racesDeck.find(static_cast <int> (card.second));
        if (_racesIterator != _racesDeck.end())
            return (*_racesIterator).second.pictureAddress();

        _specialMechanicsIterator = _specialMechanicsDeck.find(static_cast <int> (card.second));
        if (_specialMechanicsIterator != _specialMechanicsDeck.end())
            return (*_specialMechanicsIterator).second.pictureAddress();
    }
    else
    { //treasure
        _armorIterator = _armorDeck.find(static_cast <int> (card.second));
        if (_armorIterator != _armorDeck.end())
            return (*_armorIterator).second.pictureAddress();

        _armorAmplifiersIterator = _armorAmplifiersDeck.find(static_cast <int> (card.second));
        if (_armorAmplifiersIterator != _armorAmplifiersDeck.end())
            return (*_armorAmplifiersIterator).second.pictureAddress();

        _battleAmplifiersIterator = _battleAmplifiersDeck.find(static_cast <int> (card.second));
        if (_battleAmplifiersIterator != _battleAmplifiersDeck.end())
            return (*_battleAmplifiersIterator).second.pictureAddress();

        _levelUpIterator = _levelUpDeck.find(static_cast <int> (card.second));
        if (_levelUpIterator != _levelUpDeck.end())
            return (*_levelUpIterator).second.pictureAddress();

        _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
        if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end())
            return (*_specialMechanicsTreasureIterator).second.pictureAddress();

        _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
        if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
            return (*_thingsAmplifiersIterator).second.pictureAddress();

        _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
        if (_weaponsIterator != _weaponsDeck.end())
            return (*_weaponsIterator).second.pictureAddress();

    }
    qDebug() << "NAY-002: Error while QString GetCardPictureAddress::GetCardPictureAddress(SimpleCard card)"
             << "Card Not found!";
    return QString("");
}
