#ifndef CARDSELECTOR_H
#define CARDSELECTOR_H

#include <QDialog>

#include <Application/card.h>
#include <selectablecardwidget.h>
#include <QLabel>


enum class CardSelectorMode
{
   Normal,
   Extended //пока сам не знаю, что будет под ним подразумеваться
};


enum class SelectionType
{
    Single,
    Group
};

enum class NecessityOfChoice
{
    UserCan,
    UserShould
};


struct CardSelectorSetup
{
    SelectableCardMode generalMode;
    CardSelectorMode mode;
    SelectionType selectionType;
    NecessityOfChoice choiceType;
    uint32_t totalCardsToBeSelected;

    explicit CardSelectorSetup(SelectableCardMode gnrlMode,
                               CardSelectorMode md = CardSelectorMode::Normal,
                               SelectionType selType = SelectionType::Single,
                               NecessityOfChoice chseType = NecessityOfChoice::UserCan,
                               uint32_t numberOfCardsHaveToBeSelected = 1) :
        generalMode(gnrlMode),
        mode(md),
        selectionType(selType),
        choiceType(chseType),
        totalCardsToBeSelected(numberOfCardsHaveToBeSelected)
    {
        //Minor correction checker
        if (selectionType == SelectionType::Single && numberOfCardsHaveToBeSelected != 1)
        {
            totalCardsToBeSelected = 1;
        }

    }

};

namespace Ui {
class CardSelector;
}

class CardSelector : public QDialog
{
    Q_OBJECT




public:
    explicit CardSelector(const std::vector<ActiveIncativeCard>& cards,
                          QSize windowSize,
                          const AllDecksToBePassed &data,
                          CardSelectorSetup setup,
                          QWidget *parent = nullptr);
    ~CardSelector();

private:
    Ui::CardSelector *ui;

private:

    Logger logger;

private:

    SelectableCardMode _generalMode;
    CardSelectorMode _selectorMode;
    SelectionType _selectionType;
    NecessityOfChoice _typeOfChoice;
    uint32_t _totalCardsHaveToBeSelected;

    std::vector<ActiveIncativeCard> _givenCards;
    std::vector<SimpleCard> _selectableCards;
    std::vector<SelectableCardWidget*> _cardsToBeSelected;
    SelectableCardWidget* _lastSelectedCardWt = nullptr;

    //В общем случае может быть и одна.
    //По размеру этого вектора можно делать видимой/скрывать кнопку "Ок"
    std::vector<SimpleCard> _selectedCards;


private:

    void AddCard(SimpleCard card);

    //Методы получения важной инфы
    CardToBeAmplifiedData GetCardToBeAmplifiedCredentials(SimpleCard card);

private:

    QSize _windowSize;


    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.10f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    CardPosition GetCurrentCardPosition();

private:
    //колоды и у него должны быть

    std::map <int, gameCardDoorMonster> _monstersDeck;
    std::map <int, gameCardDoorAmplifier> _amplifiersDeck;
    std::map <int, gameCardDoorCurse> _cursesDeck;
    std::map <int, gameCardDoorProfession> _professionsDeck;
    std::map <int, gameCardDoorRace> _racesDeck;
    std::map <int, gameCardDoorSpecialMechanic> _specialMechanicsDeck;

    std::map <int, gameCardTreasureArmor> _armorDeck;
    std::map <int, gameCardTreasureArmorAmplifier> _armorAmplifiersDeck;
    std::map <int, gameCardTreasureBattleAmplifier> _battleAmplifiersDeck;
    std::map <int, gameCardTreasureLevelUp> _levelUpDeck;
    std::map <int, gameCardTreasureSpecialMechanic> _specialMechanicsTreasureDeck;
    std::map <int, gameCardTreasureThingsAmplifiers> _thingsAmplifiersDeck;
    std::map <int, gameCardTreasureWeapon> _weaponsDeck;

private:

    void SetDecks(const AllDecksToBePassed& data);

public slots:

    void SlotCardWasSelectedByUser(SimpleCard card, bool selected, SelectableCardWidget* wt);

signals:

    void SignalReportCardsWereSelected(const std::vector<SimpleCard>& cards);
    void SignalUserClosedCardSelector();

private:

    void SetUpSignalsSlotsConnections();
    void closeEvent(QCloseEvent *event);

    void SetFontAndAlignment(QLabel* lbl);


};

#endif // CARDSELECTOR_H
