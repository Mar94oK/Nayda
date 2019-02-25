#include "cardsingameobserver.h"
#include "ui_cardsingameobserver.h"

CardsInGameObserver::CardsInGameObserver(QSize mainWindowSize, const QString &playerName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardsInGameObserver)
{
    ui->setupUi(this);

    _mainWindowSize = mainWindowSize;
    _widnowSizeWidth = static_cast<uint32_t>(_mainWindowSize.width());
    _windowSizeHeight = static_cast<uint32_t>(_mainWindowSize.height());

    _playerName = playerName;

    SetFontAndAlignment(ui->lbl_Name);
    ui->lbl_Name->setText(_widgetName + " игрока " + _playerName);

    connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::pressed,
            this, &CardsInGameObserver::close);
    connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::pressed,
            [this]{emit SignalUserIsClosingCardsInGameObserver();});

    setWindowModality(Qt::ApplicationModal);

    if (CheckCardsInGameStackIsEmpty())
        emit SignalNoCardsLeft();

}

CardsInGameObserver::~CardsInGameObserver()
{
    delete ui;
}

void CardsInGameObserver::RemoveCardFromDisabledCards(SimpleCard card)
{
    for (uint32_t var = 0; var < _disabledCards.size(); ++var)
    {
        if (_disabledCards[var] == card)
        {
            _disabledCards.erase(_disabledCards.begin() + static_cast<int32_t>(var));
            return;
        }
    }
    qDebug() << "NAY-002: ERROR WHILE RemoveCardFromDisabledCards(): Card not found!";
}

void CardsInGameObserver::RemoveCardFromActiveCards(SimpleCard card)
{
    for (uint32_t var = 0; var < _activeCards.size(); ++var)
    {
        if (_activeCards[var] == card)
        {
            _activeCards.erase(_activeCards.begin() + static_cast<int32_t>(var));
            return;
        }
    }
    qDebug() << "NAY-002: ERROR WHILE RemoveCardFromActiveCards(): Card not found!";
}

void CardsInGameObserver::AddCard(CardInGame card)
{
    QSize cardSize(static_cast<int32_t>(_widnowSizeWidth*handCardSizeWidht),
                   static_cast<int32_t>(_windowSizeHeight*handCardSizeHeight));

    _cardsInGameHolder.push_back(card);
    qDebug() << "NAY-002: AddCard in Cards In Game Observer: "
             << " cards is " << (card.first ? "Enabled!" : "Disabled!");

    if (card.first)
        _activeCards.push_back(card.second);
    else
        _disabledCards.push_back(card.second);


    QPushButton* cardToShow = new QPushButton();


    qDebug() << "CardsInGameObserver::AddCard(SimpleCard card): " << GetCardPictureAddress(card.second);
    SetUpButtonPicture(cardToShow,
                       GetCardPictureAddress(card.second),
                       cardSize);

    if (card.first)
        ui->lyt_ActiveCards->addWidget(cardToShow,
                                            static_cast<int32_t>(GetCurrentCardPosition(card.first).posRow),
                                            static_cast<int32_t>(GetCurrentCardPosition(card.first).posColumn));
    else
        ui->lyt_DisabledCards->addWidget(cardToShow,
                                            static_cast<int32_t>(GetCurrentCardPosition(card.first).posRow),
                                            static_cast<int32_t>(GetCurrentCardPosition(card.first).posColumn));

    _cardsAsButtonsRepresenter.push_back(cardToShow);
    cardToShow->show();

}

void CardsInGameObserver::RemoveCard(SimpleCard card)
{
    qDebug() << "NAY-002: CardsInGameObserver: Cards remove process: ";
    for (uint32_t var = 0; var < _cardsInGameHolder.size(); ++var)
    {
        if (_cardsInGameHolder[var].second == card)
        {
            //удалить её из соответствующего вектора
            if (_cardsInGameHolder[var].first)
                RemoveCardFromActiveCards(card);
            else
                RemoveCardFromDisabledCards(card);

            _cardsInGameHolder.erase(_cardsInGameHolder.begin() + static_cast<int32_t>(var));
            _cardsAsButtonsRepresenter[var]->deleteLater();
            _cardsAsButtonsRepresenter.erase(_cardsAsButtonsRepresenter.begin() + static_cast<int32_t>(var));
            return;
        }
    }
    qDebug() << "NAY-002: ERROR while void CardsInGameObserver::RemoveCard(SimpleCard card). Card not found!";
}

void CardsInGameObserver::SetDecks(const AllDecksToBePassed &data)
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

QString CardsInGameObserver::GetCardPictureAddress(SimpleCard card)
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

void CardsInGameObserver::SetFontAndAlignment(QLabel *lbl)
{
    QFont        _startUpTimerTextLabelFont ("times", 35);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    lbl->setFont(_startUpTimerTextLabelFont);
    lbl->setAlignment(Qt::AlignHCenter);
}

CardPosition CardsInGameObserver::GetCurrentCardPosition(bool disabledActive)
{

    uint32_t column = 0;
    uint32_t row = 0;
    if (disabledActive)
    {
        column = (_activeCards.size() % 4);
        row = _activeCards.size() / 4;
    }
    else
    {
        column = (_disabledCards.size() % 4);
        row = _disabledCards.size() / 4;
    }


    return CardPosition(column, row);
}

void CardsInGameObserver::SetUpButtonPicture(QPushButton * const btn, const QString &picturePath, QSize size)
{
    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());

    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(size.width(),
                                            size.height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    btn->setMinimumSize(size);
    btn->setMaximumSize(size);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}
