#ifndef CARDSTACKS_H
#define CARDSTACKS_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <vector>
#include <QApplication>
#include <QDesktopWidget>
#include <Application/card.h>
#include <QDebug>
#include "munchkinglobaldefines.h"


#define DEBUG_CARDSTACKS_WIDGET


//#defin_showTheNumberOfCardsLeftft true

#define increasingStacksSizeDeltaWidth 0.015
#define increasingStacksSizeDeltaHeight 0.015*2.71

namespace Ui {
class CardStacks;
}

class CardStacks : public QWidget
{
    Q_OBJECT

public:
    explicit CardStacks(QWidget *parent = 0);
    ~CardStacks();

private:
    Ui::CardStacks *ui;

private:

#ifndef USE_RESOURCES
    std::vector<QString> _doorsStackLevelsPictures = {{"Pictures/stacksLevels/DoorsStack1.png"},
                                                      {"Pictures/stacksLevels/DoorsStack2.png"},
                                                      {"Pictures/stacksLevels/DoorsStack3.png"},
                                                      {"Pictures/stacksLevels/DoorsStack4.png"},
                                                      {"Pictures/stacksLevels/DoorsStack5_SingleCard.png"},
                                                      {"Pictures/stacksLevels/doorsAreOpened.jpg"}};
#else
    std::vector<QString> _doorsStackLevelsPictures = {{":/Pictures/stacksLevels/DoorsStack1.png"},
                                                      {":/Pictures/stacksLevels/DoorsStack2.png"},
                                                      {":/Pictures/stacksLevels/DoorsStack3.png"},
                                                      {":/Pictures/stacksLevels/DoorsStack4.png"},
                                                      {":/Pictures/stacksLevels/DoorsStack5_SingleCard.png"},
                                                      {":/Pictures/stacksLevels/doorsAreOpened.jpg"}};
#endif

#ifndef USE_RESOURCES
    std::vector<QString> _treasuresStackLevelPictures = {{"Pictures/stacksLevels/TreasureStack1.png"},
                                                         {"Pictures/stacksLevels/TreasureStack2.png"},
                                                         {"Pictures/stacksLevels/TreasureStack3.png"},
                                                         {"Pictures/stacksLevels/TreasureStack4.png"},
                                                         {"Pictures/stacksLevels/TreasureStack5_SingleCard.png"},
                                                         {"Pictures/stacksLevels/AllTreasuresAreFound.jpg"}};
#else
    std::vector<QString> _treasuresStackLevelPictures = {{":/Pictures/stacksLevels/TreasureStack1.png"},
                                                         {":/Pictures/stacksLevels/TreasureStack2.png"},
                                                         {":/Pictures/stacksLevels/TreasureStack3.png"},
                                                         {":/Pictures/stacksLevels/TreasureStack4.png"},
                                                         {":/Pictures/stacksLevels/TreasureStack5_SingleCard.png"},
                                                         {":/Pictures/stacksLevels/AllTreasuresAreFound.jpg"}};
#endif



public slots:

    void changeTheDoorsStackView(unsigned int cardsLeft);
    void changeTheTreasureStackView(unsigned int cardsLeft);

private:

    //setup the koefficients;
    const float _race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float _race_class_btn_size_width = 0.035f;
    const float _race_class_btn_size_height = _race_class_btn_size_geometric_width_to_height_ratio*_race_class_btn_size_width;

private:

    bool _showTheNumberOfCardsLeft = true;


private:

    std::vector<SimpleCard> _doorsFold;
    std::vector<SimpleCard> _treasuresFold;


public slots:

    void passTheCardToFoldStack(SimpleCard card);


private:

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

    unsigned int treasuresLeft() const;
    void setTreasuresLeft(unsigned int treasuresLeft);

    unsigned int doorsLeft() const;
    void setDoorsLeft(unsigned int doorsLeft);

    unsigned int totalDoors() const;
    void setTotalDoors(unsigned int totalDoors);

    unsigned int totalTreasures() const;
    void setTotalTreasures(unsigned int totalTreasures);

private:

    unsigned int _treasuresLeft;
    unsigned int _doorsLeft;

    unsigned int _totalDoors;
    unsigned int _totalTreasures;


public slots:

    void updateTreasuresLeft(unsigned int treasuresLeft);
    void updateDoorsLeft(unsigned int doorsLeft);


public slots:

    void testTheFoldProcess();
    void startTheTest();

private:

    unsigned int _currCardsArrayRepresentationStep = 0;

    QTimer* _testTimer;

    bool _testIsRunning = false;

};

#endif // CARDSTACKS_H
