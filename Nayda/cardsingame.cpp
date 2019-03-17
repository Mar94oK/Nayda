#include "cardsingame.h"
#include "ui_cardsingame.h"
#include <QTimer>

CardsInGame::CardsInGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardsInGame)
{
    ui->setupUi(this);

    _showCardsTimer = new QTimer(this);
    _showCardsTimer->setSingleShot(true);
    connect(_showCardsTimer, &QTimer::timeout, [this]{ emit SignalShowTheCard(_currentCardToShowNearItsPosition);});

}

CardsInGame::~CardsInGame()
{
    delete ui;
}

void CardsInGame::SetDecks(const AllDecksToBePassed &data)
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

void CardsInGame::AddCardToCardsInGame(CardInGame card, bool isMainPlayer)
{    
    //17.03.2019
    //Виджетами карт в игре также нужно управлять.
    //Между виджетами и картой должно присутствовать взаимнооднозначное соответствие.
    //Придётся переделать хранилище карт в отдельный класс, который хранит "Карты в игре"
    //И удаление карты из которого ведёт к удалению конкретного виджета
    //Впрочем, это, кажется, уже сделано. =))) Класс "Карты в иге" этим и занимается.



    QSize cardSize;

    if (isMainPlayer)
    {
        cardSize.setWidth((CardsInGameWidgetPerfomanceValues::threeLayoutForCardsAreEnabled ?
                                  static_cast<int32_t>(_widnowSizeWidth *GeometricLimitations::handCardSizeWidht
                                                       * GeometricLimitations::cardInGametoCardOnHandSizeRatio)
                                :
                                  static_cast<int32_t>(_widnowSizeWidth *GeometricLimitations::handCardSizeWidht * 2)));

        cardSize.setHeight((CardsInGameWidgetPerfomanceValues::threeLayoutForCardsAreEnabled ?
                                  static_cast<int32_t>(_windowSizeHeight *GeometricLimitations::handCardSizeHeight
                                                       * GeometricLimitations::cardInGametoCardOnHandSizeRatio)
                                :
                                  static_cast<int32_t>(_windowSizeHeight *GeometricLimitations::handCardSizeHeight * 2)));
    }
    else
    {
        cardSize.setWidth(static_cast<int32_t>(GeometricLimitations::handCardSizeWidht*_widnowSizeWidth));
        cardSize.setHeight(static_cast<int32_t>(GeometricLimitations::handCardSizeHeight*_windowSizeHeight));
    }

    qDebug() << "CardSize CardsInGame: _widnowSizeWidth: " << _widnowSizeWidth;
    qDebug() << "CardSize CardsInGame: _windowSizeHeight: " << _windowSizeHeight;


    qDebug() << "CardSize CardsInGame: width: " << cardSize.width();
    qDebug() << "CardSize CardsInGame: height: " << cardSize.height();

    _cardsInGameHolder.push_back(card);
    qDebug() << "NAY-002: CardsInGame::AddCardToCardsInGame(CardInGame card): "
             << " cards is " << (card.first ? "Enabled!" : "Disabled!");

    if (card.first)
        _activeCards.push_back(card.second);
    else
        _disabledCards.push_back(card.second);

    QPushButton* cardToShow = new QPushButton();
    QVBoxLayout* cardLayout = new QVBoxLayout();

    qDebug() << "CardsInGame::AddCardToCardsInGame(CardInGame card): " << GetCardPictureAddress(card.second);

    cardToShow->setMinimumSize(cardSize);
    cardToShow->setMaximumSize(cardSize);
    cardToShow->setFlat(true);
    cardToShow->setAutoFillBackground(true);
    cardToShow->setStyleSheet("QPushButton {background-color:transparent;}");
    //btn->setPalette(plteBtnMainRepresenter);

    cardLayout->addWidget(cardToShow);


    bool active = card.first;
    if (_mode == CardsInGameWidgetMode::MainPlayer)
    {
        if (active)
        {
            if (CardsInGameWidgetPerfomanceValues::threeLayoutForCardsAreEnabled)
            {
                if (_cardsInGameHolder.size()
                        < CardsInGameWidgetPerfomanceValues::maximumCardsInARowInTheCardsInActiveGameLayout)
                {
                    //cardLayout->addWidget(cardToShow);
                    ui->lyt_Top->addLayout(cardLayout);
                }
                else if (_cardsInGameHolder.size()
                         > CardsInGameWidgetPerfomanceValues::maximumCardsInARowInTheCardsInActiveGameLayout
                         && _cardsInGameHolder.size()
                         < 2 * CardsInGameWidgetPerfomanceValues::maximumCardsInARowInTheCardsInActiveGameLayout)
                {
                    //ui->lyt_Middle->addWidget(cardToShow);
                    ui->lyt_Middle->addLayout(cardLayout);
                }

                else
                {
                    if (_cardsInGameHolder.size() % 2)
                        //ui->lyt_Top->addWidget(cardToShow);
                        ui->lyt_Top->addLayout(cardLayout);
                    else
                        //ui->lyt_Middle->addWidget(cardToShow);
                        ui->lyt_Middle->addLayout(cardLayout);
                }
            }
            else
            {
                //ui->lyt_Top->addWidget(cardToShow);
                ui->lyt_Top->addLayout(cardLayout);
            }
        }
        else
        {
            //ui->lyt_Bottom->addWidget(cardToShow);
            ui->lyt_Bottom->addLayout(cardLayout);
        }
    }
    else
    {
        if (active)
            //ui->lyt_Top->addWidget(cardToShow);
            ui->lyt_Top->addLayout(cardLayout);

        else
            //ui->lyt_TopSecondary->addWidget(cardToShow);
            ui->lyt_TopSecondary->addLayout(cardLayout);

    }

    _cardsAsButtonsRepresenter.push_back(cardToShow);
    cardToShow->show();
//    cardToShow->hide();
    //Продолжить здесь 18.03.2019. Начать с контроля за Layout ами, которые содержат карты.
    cardToShow->installEventFilter(this);
}

void CardsInGame::RemoveCard(SimpleCard card)
{
    //Как обычно - т.к. вектор кнопок, отображающих карты, и вектор карт - связанные сущности,
    //Удалить из обоих мест

    if (_cardsInGameHolder.size() != _cardsAsButtonsRepresenter.size())
    {
        qDebug() << "NAY-002: ERROR void CardsInGame::RemoveCard(SimpleCard card). Sizes of containers incompatible!";
    }

    for (uint32_t var = 0; var < _cardsInGameHolder.size(); ++var)
    {
        if (_cardsInGameHolder[var].second == card)
        {
            _cardsInGameHolder.erase(_cardsInGameHolder.begin() + static_cast<int32_t>(var));
            _cardsInGameHolder.shrink_to_fit();

            _cardsAsButtonsRepresenter[var]->deleteLater();
            _cardsAsButtonsRepresenter.erase(_cardsAsButtonsRepresenter.begin() + static_cast<int32_t>(var));
            _cardsAsButtonsRepresenter.shrink_to_fit();
            qDebug() << "The card is removed from CardsInGame!";
            return;
        }
    }
    for (uint32_t var = 0; var < _activeCards.size(); ++var)
    {
        if (_activeCards[var] == card)
        {
            _activeCards.erase(_activeCards.begin() + static_cast<int32_t>(var));
            _activeCards.shrink_to_fit();
            return;
        }
    }
    for (uint32_t var = 0; var < _disabledCards.size(); ++var)
    {
        if (_disabledCards[var] == card)
        {
            _disabledCards.erase(_activeCards.begin() + static_cast<int32_t>(var));
            _disabledCards.shrink_to_fit();
            return;
        }
    }
}

PositionedCard CardsInGame::GetCardPosition(SimpleCard card)
{
    //Define whether there's such card in the hand.
    if (_cardsAsButtonsRepresenter.size() != _cardsInGameHolder.size())
    {
        qDebug() << "NAY-002: ERROR WHILE PositionedCard CardsInGame::GetCardPosition(SimpleCard card)"
                 << "Sizes not equal!";
    }

    for (uint32_t var = 0; var < _cardsInGameHolder.size(); ++var)
    {
        if (_cardsInGameHolder[var].second == card)
        {
            PositionedCard posCard;
            posCard.SetSimpleCard(card);
            //Они добавляются в вектор карт точно в таком же порядке, их ID должны свопадать
            //Им может служить в общем случае индекс массива

            posCard.SetPositionTopLeft({ _cardsAsButtonsRepresenter[var]->pos().x(),
                                                         _cardsAsButtonsRepresenter[var]->pos().y()});
            posCard.SetPositionBottomRight({ _cardsAsButtonsRepresenter[var]->pos().x() + _cardsAsButtonsRepresenter[var]->width(),
                                                             _cardsAsButtonsRepresenter[var]->pos().y() + _cardsAsButtonsRepresenter[var]->height()});
            return posCard;

        }
    }
    qDebug() << "NAY-002: ERROR WHILE PositionedCard CardsInGame::GetCardPosition(SimpleCard card)"
             << "No card found!";

    return PositionedCard();
}

std::vector<PositionedCard> CardsInGame::GetPositionedCards(const std::vector<SimpleCard> &cards)
{
    std::vector<PositionedCard> posCards;

    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        posCards.push_back(GetCardPosition(cards[var]));
    }

    return posCards;
}

QString CardsInGame::GetCardPictureAddress(SimpleCard card)
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
            return (*_weaponsIterator).second.GetPictureAddress();

    }
    qDebug() << "NAY-002: Error while QString GetCardPictureAddress::GetCardPictureAddress(SimpleCard card)"
             << "Card Not found!";
    return QString("");
}

void CardsInGame::SetUpButtonPicture(QPushButton * const btn, const QString &picturePath, QSize size, bool active)
{

    QImage image(picturePath);
    QPixmap pxmpBtnMainRepresenter;
    QPalette plteBtnMainRepresenter(btn->palette());

    //NAY-002: EXPECTED_IMPROVEMENT
    //Передавать в этот виджет настройку, отвечающую за отображение или неотображение
    //Карт серым цветом в том случае, если они неактивны.
    if (!active)
    {
        pxmpBtnMainRepresenter = QPixmap::fromImage(image.convertToFormat(QImage::Format_Grayscale8));
    }
    else
        pxmpBtnMainRepresenter = QPixmap::fromImage(image);

    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(size.width(),
                                            size.height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    btn->setMinimumSize(size);
    btn->setMaximumSize(size);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);

    qDebug() << "NAY-002: CardsInGameSetCardPicture Function Checker()";
}

void CardsInGame::ShowLastCardAdded(bool isMainPlayer)
{
    QSize cardSize;

    if (isMainPlayer)
    {
        cardSize.setWidth((CardsInGameWidgetPerfomanceValues::threeLayoutForCardsAreEnabled ?
                                  static_cast<int32_t>(_widnowSizeWidth *GeometricLimitations::handCardSizeWidht
                                                       * GeometricLimitations::cardInGametoCardOnHandSizeRatio)
                                :
                                  static_cast<int32_t>(_widnowSizeWidth *GeometricLimitations::handCardSizeWidht * 2)));

        cardSize.setHeight((CardsInGameWidgetPerfomanceValues::threeLayoutForCardsAreEnabled ?
                                  static_cast<int32_t>(_windowSizeHeight *GeometricLimitations::handCardSizeHeight
                                                       * GeometricLimitations::cardInGametoCardOnHandSizeRatio)
                                :
                                  static_cast<int32_t>(_windowSizeHeight *GeometricLimitations::handCardSizeHeight * 2)));
    }
    else
    {
        cardSize.setWidth(static_cast<int32_t>(GeometricLimitations::handCardSizeWidht*_widnowSizeWidth));
        cardSize.setHeight(static_cast<int32_t>(GeometricLimitations::handCardSizeHeight*_windowSizeHeight));
    }


    SetUpButtonPicture(_cardsAsButtonsRepresenter.back(),
                       GetCardPictureAddress(_cardsInGameHolder.back().second),
                       cardSize, _cardsInGameHolder.back().first);

    _cardsAsButtonsRepresenter.back()->show();
}

bool CardsInGame::eventFilter(QObject *o, QEvent *e)
{
    for (unsigned int var = 0; var < _cardsAsButtonsRepresenter.size(); ++var) {
        if (o == _cardsAsButtonsRepresenter[var]) {

            if (e->type() == QEvent::Enter) {
//                qDebug() << "Mouse Enters Area!";
//#ifdef __linux__
//                if (_debounceTimer->isActive())
//                    _debounceTimer->stop();
//#endif
                _currentCardToShow = _cardsInGameHolder[var].second; //no Class

                _currentCardToShowNearItsPosition.SetSimpleCard(_cardsInGameHolder[var].second);
                _currentCardToShowNearItsPosition.SetPositionTopLeft({ _cardsAsButtonsRepresenter[var]->pos().x(),
                                                                       _cardsAsButtonsRepresenter[var]->pos().y()});
                _currentCardToShowNearItsPosition.SetPositionBottomRight({_cardsAsButtonsRepresenter[var]->pos().x() + _cardsAsButtonsRepresenter[var]->width(),
                                                                          _cardsAsButtonsRepresenter[var]->pos().y() + _cardsAsButtonsRepresenter[var]->height()});

                _showCardsTimer->start(static_cast<int32_t>(_timeToShowTheCard));
                return true;
            }
            else if (e->type() == QEvent::Leave)
            {
                if (_showCardsTimer->isActive()) _showCardsTimer->stop();
                emit SignalHideTheCard(true);
                return true;
            }
            else if (e->type() == QEvent::MouseButtonPress)
            {
                emit SignalHideTheCard(true);
            }
            else
            {
                return QWidget::eventFilter(o, e);
            }
        }
    }
    return QWidget::eventFilter(o, e);
}

QPoint CardsInGame::ProvidePositionOfTheLastAddedCard()
{
    //Здесь, скорее всего, упадёт - т.к. вектор пустой!!!
    return _cardsAsButtonsRepresenter.back()->pos();
}


