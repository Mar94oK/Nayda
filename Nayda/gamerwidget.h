#ifndef GAMERWIDGET_H
#define GAMERWIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>

#include "Application/card.h"
#include <QTimer>


#define DEBUG_GAMER_WIDGET

namespace Ui {
class GamerWidget;
}

class GamerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GamerWidget(QWidget *parent = 0);
    ~GamerWidget();



    bool is_MainPlayer() const;
    void setIs_MainPlayer(bool is_MainPlayer);
    void redraw_as_a_secondary_player();


    void setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck);
    void setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck);
    void setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck);
    void setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck);
    void setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck);
    void setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck);
    void setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck);
    void setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck);
    void setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck);
    void setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck);
    void setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck);
    void setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck);
    void setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck);





private:


    Ui::GamerWidget *ui;
    bool _is_MainPlayer;

    const std::map<int, gameCardDoorMonster> *_monstersDeck;
    const std::map<int, gameCardDoorAmplifier> *_amplifiersDeck;
    const std::map<int, gameCardDoorCurse> *_cursesDeck;
    const std::map<int, gameCardDoorProfession> *_professionsDeck;
    const std::map<int, gameCardDoorRace> *_racesDeck;
    const std::map<int, gameCardDoorSpecialMechanic> *_specialMechanicsDeck;

    const std::map<int, gameCardTreasureArmor> *_armorDeck;
    const std::map<int, gameCardTreasureArmorAmplifier> *_armorAmplifiersDeck;
    const std::map<int, gameCardTreasureBattleAmplifier> *_battleAmplifiersDeck;
    const std::map<int, gameCardTreasureLevelUp> *_levelUpDeck;
    const std::map<int, gameCardTreasureSpecialMechanic> *_specialMechanicsTreasureDeck;
    const std::map<int, gameCardTreasureThingsAmplifiers> *_thingsAmplifiersDeck;
    const std::map<int, gameCardTreasureWeapon> *_weaponsDeck;



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






public:

    void passCardsDecksToHandsWidget();
    void addTheCardToHandsWidget(SimpleCard card);

    bool eventFilter(QObject *o, QEvent *e);


private:

    QTimer *_showCardsTimer;
    unsigned int _timeToShowTheCard = 100; //ms
    SimpleCard _currentCardToShowInCentre;
    PositionedCard _currentCardToShowNearItsPosition;

    std::vector<SimpleCard> _cardsOnHandsGamerWidgetProperty;
    std::vector<SimpleCard> _cardsRacesClassesGamerWidgetProperty;
    std::vector<SimpleCard> _cardsInGameWidgetGamerProperty;


signals:

    void _representTheCardInCentre(PositionedCard);
    void _hideTheCardInCentre(bool);



public slots:

    void _representTheCardInCenterSlot();
    void _representTheCardFromHandsInCentre(PositionedCard);
    void _hideTheCardInCentreSlot(bool);



private:

    std::vector<QString> _levelsPictures = {{"Pictures/levels/match1_transparent.png"},
                                            {"Pictures/levels/match2_transparent.png"},
                                            {"Pictures/levels/match3_transparent.png"},
                                            {"Pictures/levels/match4_transparent.png"},
                                            {"Pictures/levels/match5_transparent.png"},
                                            {"Pictures/levels/match6_transparent.png"},
                                            {"Pictures/levels/match7_transparent.png"},
                                            {"Pictures/levels/match8_transparent.png"},
                                            {"Pictures/levels/match9_transparent.png"},
                                            {"Pictures/levels/match10_transparent.png"}};

    unsigned int _gamerLevel = 1;

public slots:

    void _changeTheGamerLevel(int levelDelta);


private:

    //setup the koefficients;
    const float _race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float _race_class_btn_size_width = 0.035f;
    const float _race_class_btn_size_height = _race_class_btn_size_geometric_width_to_height_ratio*_race_class_btn_size_width;


private:

    QTimer* _testTimer;
    bool _testBtnIsPressed = false;

private slots:

    void _slotTestGamerLevels();
    void _slotStartTestCards();



};

#endif // GAMERWIDGET_H
