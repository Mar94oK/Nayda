#ifndef SELLMENU_H
#define SELLMENU_H

#include <QWidget>
#include <Application/card.h>
#include <selectablecardwidget.h>
#include <QLabel>


struct CardToBeSoldCredentials
{
    QString     _picturePath;
    uint32_t    _price;

    explicit CardToBeSoldCredentials(const QString& str, uint32_t price) :
        _picturePath(str), _price(price)
    { }

    explicit CardToBeSoldCredentials()
    { }
};


struct CardPosition
{
    uint32_t posColumn;
    uint32_t posRow;

    explicit CardPosition(uint32_t posCol, uint32_t posRow) :
        posColumn(posCol), posRow(posRow)
    { }
};

namespace Ui {
class SellMenu;
}

class SellMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SellMenu(AllDecksToBePassed decksData, QSize mainWindowSize, const std::vector<SimpleCard>& data, QWidget *parent = nullptr);
    ~SellMenu();

private:
    Ui::SellMenu *ui;

private:

    QString _nameBaseText = "Продажа карт ";
    QString _sumBaseText = "Сумма: ";
    QString _cardsToSellBaseText = "Карт на продажу: ";

    uint32_t _totalSumOfSelectedCards = 0;
    uint32_t _totalCardsToBeSold = 0;

    void AddCard(SimpleCard card);
    CardToBeSoldCredentials GetCardToBeSoldCredentials(SimpleCard card);
    uint32_t GetCardPrice(SimpleCard card);

public:
    void SetDecks(const AllDecksToBePassed& data);

//Visualization. The same as in the CardInspector Size.
private:

    //setup the koefficients;
    const float handCardSize_width_to_height_ratio = 2.71f;
    const float handCardSizeWidht = 0.10f;
    const float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

    uint32_t _windowSizeHeight;
    uint32_t _widnowSizeWidth;

   CardPosition GetCurrentCardPosition();

private:

    std::vector<SelectableCardWidget* > _cardsToBeSoldOut;
    std::vector<SimpleCard> _cardsToBeSold;

private:

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


public slots:

    void SlotCardWasSelectedToBeSoldByUser(SimpleCard card, bool selected);

signals:

    void SignalReportCardsToBeSold(const std::vector<SimpleCard>& cards);
    void SignalUserClosedTradeMenu();

private:

    void SetUpSignalsSlotsConnections();
    void closeEvent(QCloseEvent *event);

    void SetFontAndAlignment(QLabel* lbl);

};

#endif // SELLMENU_H
