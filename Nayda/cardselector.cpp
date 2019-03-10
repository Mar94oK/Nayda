#include "cardselector.h"
#include "ui_cardselector.h"
#include <QDialogButtonBox>
#include <QPushButton>

CardSelector::CardSelector(const std::vector<ActiveIncativeCard> &cards,
                           QSize windowSize,
                           const AllDecksToBePassed &data,
                           CardSelectorSetup setup,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardSelector),
    _generalMode(setup.generalMode),
    _selectorMode(setup.mode),
    _selectionType(setup.selectionType),
    _typeOfChoice(setup.choiceType),
    _totalCardsHaveToBeSelected(setup.totalCardsToBeSelected),
    _givenCards(cards),
    _windowSize(windowSize)
{
    ui->setupUi(this);

    _selectableCards = ActiveIncativeToSimpleCardsVector(_givenCards);

    DECLARE_NAMED_LOGGER(CardSelector);

    SetDecks(data);

    SetUpSignalsSlotsConnections();

    //Initially Hide "Ok" button
    ui->btnBox_Controls->button(QDialogButtonBox::StandardButton::Ok)->hide();


    //Здесь установить настройки (графические) текстовых полей
    SetFontAndAlignment(ui->lbl_SelectorName);
    //SetFontAndAlignment(ui->lbl_SelecotrDefinition);

    switch (_generalMode)
    {
    case SelectableCardMode::AmplifierAddition:
    {
        ui->lbl_SelectorName->setText("Выбер вещи для усиления");
        ui->lbl_SelecotrDefinition->setText("Выберите одну из предложенных. Усилитель будет прикреплён к ней.");
    }
    break;

    default:
        logger.Error() << "NAY-002: Unsupported SelectableCardMode!";
    }

    for (std::vector<SimpleCard>::iterator it = _selectableCards.begin();
         it != _selectableCards.end(); ++it)
    {
        AddCard(*it);
    }

    setWindowModality(Qt::ApplicationModal);

}

CardSelector::~CardSelector()
{
    delete ui;
}

void CardSelector::AddCard(SimpleCard card)
{
    SelectableCardWidget* selectableCard = nullptr;
    switch (_generalMode)
    {
    case SelectableCardMode::AmplifierAddition:
    {
        selectableCard = new SelectableCardWidget
                (SelectableCardMode::AmplifierAddition,
                 std::make_shared<CardToBeAmplifiedData>
                 (GetCardToBeAmplifiedCredentials(card)));
    }
    break;

    default:
        logger.Error() << "NAY-002: Unsupported SelectableCardMode!";
        return; //не добавлять карт
    }

    _cardsToBeSelected.push_back(selectableCard);

    ui->lyt_SelectableCards->addWidget(selectableCard,
                              static_cast<int32_t>(GetCurrentCardPosition().posRow),
                              static_cast<int32_t>(GetCurrentCardPosition().posColumn));
    selectableCard->show();

    connect(selectableCard, &SelectableCardWidget::SignalReportSelected,
            [this, card, selectableCard](bool selected){SlotCardWasSelectedByUser(card, selected, selectableCard);});

}

CardToBeAmplifiedData CardSelector::GetCardToBeAmplifiedCredentials(SimpleCard card)
{
    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    if (!card.first)
    {
        logger.Error() << "NAY-002:: GetCardToBeAmplifiedCredentials():: Doors couldn't have been amplified!";
        throw "Doors can not be amplified";
    }

    QSize cardSize(static_cast<int32_t>(_windowSize.width()*handCardSizeWidht),
                   static_cast<int32_t>(_windowSize.height()*handCardSizeHeight));

    _armorIterator = _armorDeck.find(static_cast <int> (card.second));
    if (_armorIterator != _armorDeck.end())
        return CardToBeAmplifiedData(cardSize,
                                     (*_armorIterator).second.pictureAddress(),
                                     static_cast<uint32_t>((*_armorIterator).second.GetBonus()),
                                     static_cast<uint32_t>((*_armorIterator).second.price()),
                                     (*_armorIterator).second.bonusToFleeing(),
                                     (*_armorIterator).second.size());

    _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
    if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
        return CardToBeAmplifiedData(cardSize,
                                     (*_thingsAmplifiersIterator).second.pictureAddress(),
                                     static_cast<uint32_t>((*_thingsAmplifiersIterator).second.bonus()),
                                     static_cast<uint32_t>((*_thingsAmplifiersIterator).second.price()),
                                     0, //Бонуса на смывку они не дают
                                     (*_thingsAmplifiersIterator).second.size());

    _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
    if (_weaponsIterator != _weaponsDeck.end())
        return CardToBeAmplifiedData(cardSize,
                                     (*_weaponsIterator).second.GetPictureAddress(),
                                     static_cast<uint32_t>((*_weaponsIterator).second.GetBonus()),
                                     static_cast<uint32_t>((*_weaponsIterator).second.GetPrice()),
                                     (*_weaponsIterator).second.GetBonusToFlee(),
                                     (*_weaponsIterator).second.GetSize());

    logger.Error() << "NAY-002: Error During GetCardToBeAmplifiedCredentials() in CardSelector. Card Not Found!!!";
    throw "CardSelector::GetCardToBeAmplifiedCredentials(SimpleCard card):: Card Not found! ";
    return CardToBeAmplifiedData();
}

CardPosition CardSelector::GetCurrentCardPosition()
{
    uint32_t column = (_cardsToBeSelected.size() % 4);
    uint32_t row = 3 + _cardsToBeSelected.size() / 4;

    logger.Debug() << "NAY-002: Column: " << column;
    logger.Debug() << "NAY-002: Row: " << row;


    return CardPosition(column, row);
}

void CardSelector::SetDecks(const AllDecksToBePassed &data)
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

void CardSelector::SlotCardWasSelectedByUser(SimpleCard card, bool selected, SelectableCardWidget *wt)
{
    if (selected)
    {
        //Проверить тип выбора
        //Если группа, можно добавить в список
        //Далее проверить, хватает ли карт для выбора
        //Если да - отключить для остальных возможность выбора
        //следующим образом:
        //При попытке выставить галку в другую карту
        //Сохраняются выставленные галки для всех карт, кроме последней
        //Последняя удаляется из списка, и заменяется на ту, которую выбрал пользователь
        //В том случае, если она НЕ была выбрана
        //А если была, то просто удаляется из списка

        if (_selectionType == SelectionType::Group)
        {
           //Проверить, не выбрано ли максимально требуемое число карт
           if (_selectedCards.size() == _totalCardsHaveToBeSelected)
           {
                //Удалить последнюю добавленную
                //Добавить последнюю
                _selectedCards.erase(_selectedCards.end() - 1);

                if (_lastSelectedCardWt != nullptr)
                    _lastSelectedCardWt->DisableChecker();

                _lastSelectedCardWt = wt;

                _selectedCards.push_back(card);
                //А больше ничего не делать
                return;
           }

            _selectedCards.push_back(card);
            _lastSelectedCardWt = wt;

           if (_selectedCards.size() == _totalCardsHaveToBeSelected)
                ui->btnBox_Controls->button(QDialogButtonBox::StandardButton::Ok)->show();

           return;
        }
        else if (_selectionType == SelectionType::Single)
        {
            if (_selectedCards.size() == _totalCardsHaveToBeSelected)
            {
                //удалить селектор
                _selectedCards.erase(_selectedCards.begin());
                if (_lastSelectedCardWt != nullptr)
                    _lastSelectedCardWt->DisableChecker();
            }

            _lastSelectedCardWt = wt;
            _selectedCards.push_back(card);
        }


    }
    else
    {
        for (std::vector<SimpleCard>::iterator it = _selectedCards.begin();
             it != _selectedCards.end(); ++it)
        {
            if (*it == card)
            {
                _selectedCards.erase(it);
                ui->btnBox_Controls->button(QDialogButtonBox::StandardButton::Ok)->hide();
                return;
            }
        }
    }
}

void CardSelector::SetUpSignalsSlotsConnections()
{
    connect(ui->btnBox_Controls->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::pressed,
            [this]{emit SignalReportCardsWereSelected(_selectedCards);});
    connect(ui->btnBox_Controls->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::pressed,
            this, &CardSelector::close);

    connect(ui->btnBox_Controls->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::pressed,
            [this]{emit SignalUserClosedCardSelector();});
}

void CardSelector::closeEvent(QCloseEvent *event)
{
    emit SignalUserClosedCardSelector();
}

void CardSelector::SetFontAndAlignment(QLabel *lbl)
{
    QFont        _startUpTimerTextLabelFont ("times", 35);
    QFontMetrics _startUpTimerTextLabelFontInterval (_startUpTimerTextLabelFont);
    lbl->setFont(_startUpTimerTextLabelFont);
    lbl->setAlignment(Qt::AlignHCenter);
}
