#include "sellmenu.h"
#include "ui_sellmenu.h"
#include <QDebug>
#include <QRect>
#include <QSize>
#include <QPushButton>

SellMenu::SellMenu(AllDecksToBePassed decksData, QSize mainWindowSize,
                   bool AllowedToOverSellAtLevelNine, uint32_t playerLevel, bool AllowLevelOverSell, const std::vector<SimpleCard> &data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellMenu)
{
    ui->setupUi(this);

    _AllowedToOverSellAtLevelNine = AllowedToOverSellAtLevelNine;
    _playerLevel = playerLevel;
    _AllowLevelOverSell = AllowLevelOverSell;
    //find the HW size of the window
    QSize HW_Screen_Size = mainWindowSize;
    _widnowSizeWidth = static_cast<uint32_t>(HW_Screen_Size.width());
    _windowSizeHeight = static_cast<uint32_t>(HW_Screen_Size.height());

    //Initially Hide "Ok" button
    ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();

    SetUpSignalsSlotsConnections();

    SetDecks(decksData);

    for (uint32_t var = 0; var < data.size(); ++var)
    {
        AddCard(data[var]);
    }

    SetFontAndAlignment(ui->lbl_Name);
    SetFontAndAlignment(ui->lbl_Sum);
    SetFontAndAlignment(ui->lbl_CardsToSell);

    setWindowModality(Qt::WindowModal);

}

SellMenu::~SellMenu()
{
    delete ui;
}

void SellMenu::AddCard(SimpleCard card)
{
    if (!card.first)
    {
        qDebug() << "NAY-002: ERROR WHILE AddCard() to SellMenu! Card is not treasure!";
        return;
    }

    CardToBeSoldCredentials cardData = GetCardToBeSoldCredentials(card);

    QSize cardSize(static_cast<int32_t>(_widnowSizeWidth*handCardSizeWidht),
                   static_cast<int32_t>(_windowSizeHeight*handCardSizeHeight));


    SelectableCardWidget* selectableCard = new SelectableCardWidget(SelectableCardMode::SellMenu,
                                                                    CardToBeShownInSellMenu(cardSize,
                                                                                            cardData._picturePath,
                                                                                            cardData._price));
    _cardsToBeSoldOut.push_back(selectableCard);

    ui->lyt_Cards->addWidget(selectableCard,
                              static_cast<int32_t>(GetCurrentCardPosition().posRow),
                              static_cast<int32_t>(GetCurrentCardPosition().posColumn));
    selectableCard->show();

    connect(selectableCard, &SelectableCardWidget::SignalReportSelected,
            [this, card, selectableCard](bool selected){SlotCardWasSelectedToBeSoldByUser(card, selected, selectableCard);});

}

CardToBeSoldCredentials SellMenu::GetCardToBeSoldCredentials(SimpleCard card)
{
    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    //_armorAmplifiersIterator
    //_battleAmplifiersIterator
    //_levelUpIterator
    //Should not be presented here!
    //Since they couldn't be sold!

    if (!card.first)
        throw "NAY-002: Error During GetCardToBeSoldCredentials(). Doors have no prices!";

    qDebug() << "NAY-002: card.second " << card.second;
    qDebug() << "NAY-002: card.first " << card.first;


    _armorIterator = _armorDeck.find(static_cast <int> (card.second));
    if (_armorIterator != _armorDeck.end())
        return CardToBeSoldCredentials((*_armorIterator).second.pictureAddress(),
                                        static_cast<uint32_t>((*_armorIterator).second.price()));

    _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
    if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end())
        return CardToBeSoldCredentials((*_specialMechanicsTreasureIterator).second.pictureAddress(),
                                        static_cast<uint32_t>((*_specialMechanicsTreasureIterator).second.price()));


    _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
    if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
        return CardToBeSoldCredentials((*_thingsAmplifiersIterator).second.pictureAddress(),
                                        static_cast<uint32_t>((*_thingsAmplifiersIterator).second.price()));


    _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
    if (_weaponsIterator != _weaponsDeck.end())
        return CardToBeSoldCredentials((*_weaponsIterator).second.pictureAddress(),
                                        static_cast<uint32_t>((*_weaponsIterator).second.price()));

    qDebug() << "NAY-002: Error During GetCardToBeSoldCredentials() in SellMenu. Card Not Found!!!";
    return CardToBeSoldCredentials();
}

uint32_t SellMenu::GetCardPrice(SimpleCard card)
{
    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    if (!card.first)
        throw "NAY-002: Error During CheckCardPrice(). Doors have no prices!";

    _armorIterator = _armorDeck.find(static_cast <int> (card.second));
    if (_armorIterator != _armorDeck.end())
        return static_cast<uint32_t>((*_armorIterator).second.price());

    _armorAmplifiersIterator = _armorAmplifiersDeck.find(static_cast <int> (card.second));
    if (_armorAmplifiersIterator != _armorAmplifiersDeck.end())
        return 0;

    _battleAmplifiersIterator = _battleAmplifiersDeck.find(static_cast <int> (card.second));
    if (_battleAmplifiersIterator != _battleAmplifiersDeck.end())
        return 0;


     _levelUpIterator = _levelUpDeck.find(static_cast <int> (card.second));
    if (_levelUpIterator != _levelUpDeck.end())
        return 0;

    _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
    if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end())
        return static_cast<uint32_t>((*_specialMechanicsTreasureIterator).second.price());


    _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
    if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
        return static_cast<uint32_t>((*_thingsAmplifiersIterator).second.price());


    _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
    if (_weaponsIterator != _weaponsDeck.end())
        return static_cast<uint32_t>((*_weaponsIterator).second.price());

    qDebug() << "NAY-002: Error During CheckCardPrice(). Card Not Found!!!";
    return 0;
}

void SellMenu::SetDecks(const AllDecksToBePassed &data)
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

    qDebug() << "NAY-002: Decks Sizes: "
             << _monstersDeck.size()
             << _amplifiersDeck.size()
             << _cursesDeck.size()
             << _professionsDeck.size()
             << _racesDeck.size()
             << _specialMechanicsDeck.size()
             << _armorDeck.size()
             << _armorAmplifiersDeck.size()
             << _battleAmplifiersDeck.size()
             << _levelUpDeck.size()
             << _specialMechanicsTreasureDeck.size()
             << _thingsAmplifiersDeck.size()
             << _weaponsDeck.size();
}

CardPosition SellMenu::GetCurrentCardPosition()
{
    uint32_t column = (_cardsToBeSoldOut.size() % 4);
    uint32_t row = 3 + _cardsToBeSoldOut.size() / 4;

    return CardPosition(column, row);
}

void SellMenu::SlotCardWasSelectedToBeSoldByUser(SimpleCard card, bool selected, SelectableCardWidget *wt)
{
    if (selected)
    {
        if (!_AllowedToOverSellAtLevelNine)
        {
            if (!CheckIfRestricetdToOverSellAtLevelNine(_totalSumOfSelectedCards + GetCardPrice(card)))
            {
                wt->DisableChecker();
                return;
            }
        }

        ++_totalCardsToBeSold;
        ui->lbl_CardsToSell->setText(_cardsToSellBaseText + QString::number(_totalCardsToBeSold));

        uint32_t cardPrice = GetCardPrice(card);
        qDebug() << "NAY-002: Card Price " << cardPrice;
        uint32_t amountOfMoneyWas = _totalSumOfSelectedCards;
        _totalSumOfSelectedCards += cardPrice;

        ui->lbl_Sum->setText(_sumBaseText + QString::number(_totalSumOfSelectedCards));

        _cardsToBeSold.push_back(card);

        if (!_AllowLevelOverSell)
        {
            CheckIfRestrictedToOverSell(amountOfMoneyWas, _totalSumOfSelectedCards);
        }
        else
        {
            if (_totalSumOfSelectedCards >= 1000)
                ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->show();
        }

    }
    else
    {
        uint32_t cardPrice = GetCardPrice(card);
        _totalSumOfSelectedCards -= cardPrice;
        ui->lbl_Sum->setText(_sumBaseText + QString::number(_totalSumOfSelectedCards));

        --_totalCardsToBeSold;
        ui->lbl_CardsToSell->setText(_cardsToSellBaseText + QString::number(_totalCardsToBeSold));

        for (uint32_t var = 0; var < _cardsToBeSold.size(); ++var)
        {
            if (_cardsToBeSold[var] == card)
            {
                _cardsToBeSold.erase(_cardsToBeSold.begin() + static_cast<int32_t>(var));
                _cardsToBeSold.shrink_to_fit();
                break;
            }
        }

        if (_totalSumOfSelectedCards < 1000)
        {
            ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();
            return;
        }

        if (!_AllowLevelOverSell)
        {
            CheckIfRestrictedToOverSell(_totalSumOfSelectedCards + cardPrice, _totalSumOfSelectedCards);
        }
        else
        {
            if (_totalSumOfSelectedCards >= 1000)
                ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->show();
        }

        qDebug() << "NAY-002: ERROR SlotCardWasSelectedToBeSoldByUser() Card Not Found!";
    }
}

void SellMenu::SetUpSignalsSlotsConnections()
{
    connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::pressed,
            [this]{emit SignalReportCardsToBeSold(_cardsToBeSold);});
    connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::pressed,
            this, &SellMenu::close);

    connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::pressed,
            [this]{emit SignalUserClosedTradeMenu();});

}

void SellMenu::closeEvent(QCloseEvent *event)
{
    emit SignalUserClosedTradeMenu();
}

void SellMenu::SetFontAndAlignment(QLabel *lbl)
{
    QFont        _startUpTimerTextLabelFont ("times", 35);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    lbl->setFont(_startUpTimerTextLabelFont);
    lbl->setAlignment(Qt::AlignHCenter);
}

void SellMenu::CheckIfRestrictedToOverSell(uint32_t priceWas, uint32_t priceBecame)
{
    qDebug() << "NAY-002: Processing overSell: ";
    uint32_t thresholdWas = priceWas / 1000;
    uint32_t thresholdBecame = priceBecame / 1000;

    if ((thresholdBecame == thresholdWas) && (priceBecame > priceWas))
    {
        qDebug() << "NAY-002: New level wasn't reached with this card! Price: " << priceBecame - priceWas;
        ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();
        return;
    }

//    if ((thresholdBecame == thresholdWas) && (priceBecame < priceWas))
//    {
//        //Check whether without each(!!!) card this result might nor be achieved;
//        for (uint32_t var = 0; var < _cardsToBeSold.size(); ++var)
//        {
//            uint32_t priceWithoutGivenCard = 0;
//            for (uint32_t y = 0; y < _cardsToBeSold.size(); ++y)
//            {
//                if (y != var)
//                    priceWithoutGivenCard += GetCardPrice(_cardsToBeSold[y]);
//            }
//            uint32_t thresholdReachedWithoutGivenCard = priceWithoutGivenCard / 1000;
//            if (thresholdReachedWithoutGivenCard == thresholdBecame)
//            {
//                qDebug() << "NAY-002: New level could be reached without this card! Card: "
//                         << _cardsToBeSold[var].second
//                         << " Price: " << GetCardPrice(_cardsToBeSold[var]);
//                ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();
//                return;
//            }
//        }
//        //check completed. Check if there's a level to be purchased:
//        if (priceBecame >= 1000)
//            ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->show();
//        else
//            ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();
//        return;
//    }

    if ((thresholdBecame > thresholdWas)
            || (thresholdBecame < thresholdWas)
            || ((thresholdBecame == thresholdWas) && (priceBecame < priceWas)))
    {
        //Check whether without each(!!!) card this result might nor be achieved;

        for (uint32_t var = 0; var < _cardsToBeSold.size(); ++var)
        {
            uint32_t priceWithoutGivenCard = 0;
            for (uint32_t y = 0; y < _cardsToBeSold.size(); ++y)
            {
                if (y != var)
                    priceWithoutGivenCard += GetCardPrice(_cardsToBeSold[y]);
            }
            uint32_t thresholdReachedWithoutGivenCard = priceWithoutGivenCard / 1000;
            if (thresholdReachedWithoutGivenCard == thresholdBecame)
            {
                qDebug() << "NAY-002: New level could be reached without this card! Card: "
                         << _cardsToBeSold[var].second
                         << " Price: " << GetCardPrice(_cardsToBeSold[var]);
                ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();
                return;
            }
        }
        //No such card without witch new threshold might be achieved
        if (priceBecame >= 1000)
            ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->show();
        else
            ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok)->hide();
        return;
    }
}

bool SellMenu::CheckIfRestricetdToOverSellAtLevelNine(uint32_t priceBecame)
{
    uint32_t levelAddition = priceBecame / 1000;
    uint32_t newLevelWillBe = _playerLevel + levelAddition;
    if (newLevelWillBe > 9)
        return false;
    return true;
}
