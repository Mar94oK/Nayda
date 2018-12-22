#include "cardsingame.h"
#include "ui_cardsingame.h"

CardsInGame::CardsInGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardsInGame)
{
    ui->setupUi(this);
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

void CardsInGame::AddCardToCardsInGame(CardInGame card)
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

    if (_mode == CardsInGameWidgetMode::MainPlayer)
    {
        if (card.first)
        {
            if (_cardsInGameHolder.size() < _maximumActiveCardsInLine)
            {
                ui->lyt_Top->addWidget(cardToShow);
            }
            else if (_cardsInGameHolder.size() > 5 && _cardsInGameHolder.size() < 10)
            {
                ui->lyt_Middle->addWidget(cardToShow);
            }
            else
            {
                if (_cardsInGameHolder.size() % 2)
                    ui->lyt_Top->addWidget(cardToShow);
                else
                    ui->lyt_Middle->addWidget(cardToShow);
            }
        }
        else
        {
            ui->lyt_Bottom->addWidget(cardToShow);
        }
    }
    else
    {
        if (card.first)
            ui->lyt_Top->addWidget(cardToShow);
        else
            ui->lyt_TopSecondary->addWidget(cardToShow);
    }



    _cardsAsButtonsRepresenter.push_back(cardToShow);
    cardToShow->show();
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
            return (*_weaponsIterator).second.pictureAddress();

    }
    qDebug() << "NAY-002: Error while QString GetCardPictureAddress::GetCardPictureAddress(SimpleCard card)"
             << "Card Not found!";
    return QString("");
}

void CardsInGame::SetUpButtonPicture(QPushButton * const btn, const QString &picturePath, QSize size, bool active)
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
