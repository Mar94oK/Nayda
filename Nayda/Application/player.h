#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include "card.h" //since it is better to store "Races", "Professions" inside the class of card.h




class player
{

    bool _isMainPlayer;

    int _playerLevel;
    int _warPower;
    int _cardsOnHands;
    int _cardsOnHandsLimit;
    int _cards_in_game;


    bool _headSlotFull;
    bool _legsSlotFull;
    bool _leftHandSlotFull;
    bool _rightHandSlotFull;
    bool _thereIsOneBigThing;
    bool _thereIsLimitOnBigThings; //may be remove it if checking the race


    Race _race;
    Profession _profession;
    Players_Sex _playersSex;


    bool _halfBlood;
    bool _superMunchkin;

    Race _second_race;
    Profession _second_profession;

    bool _halfBlood_without_second_race;
    bool _superMunchkin_without_second_profession;

    std::map <Race_Active_Abilities, Abilities_Keys_Races> _raceActiveAbilities;
    std::map <Race_Passive_Abilities, Abilities_Keys_Races> _racePassiveAbilities;
    std::map <Profession_Active_Abilities, Abilities_Keys_Professions> _professionActiveAbilities;
    std::map <Profession_Passive_Abilities, Abilities_Keys_Professions> _professionPassiveAbilites;


public:


    player();


    void addRaceActiveAbility(Race_Active_Abilities raceActiveAbility, Abilities_Keys_Races raceAbilityKey);
    void addRacePassiveAbility(Race_Passive_Abilities racePassiveAbility, Abilities_Keys_Races raceAbilityKey);
    void addProfessionActiveAbility(Profession_Active_Abilities professionActiveAbility, Abilities_Keys_Professions professionAbilityKey);
    void addProfessionPassiveAbility(Profession_Passive_Abilities professionPassiveAbility, Abilities_Keys_Professions professionAbilityKey);


    int playerLevel() const;
    void setPlayerLevel(int playerLevel);
    int warPower() const;
    void setWarPower(int warPower);
    int cardsOnHands() const;
    void setCardsOnHands(int cardsOnHands);
    int cardsOnHandsLimit() const;
    void setCardsOnHandsLimit(int cardsOnHandsLimit);
    int cards_in_game() const;
    void setCards_in_game(int cards_in_game);
    bool headSlotFull() const;
    void setHeadSlotFull(bool headSlotFull);
    bool legsSlotFull() const;
    void setLegsSlotFull(bool legsSlotFull);
    bool leftHandSlotFull() const;
    void setLeftHandSlotFull(bool leftHandSlotFull);
    bool rightHandSlotFull() const;
    void setRightHandSlotFull(bool rightHandSlotFull);
    bool thereIsOneBigThing() const;
    void setThereIsOneBigThing(bool thereIsOneBigThing);
    bool thereIsLimitOnBigThings() const;
    void setThereIsLimitOnBigThings(bool thereIsLimitOnBigThings);
    Race race() const;
    void setRace(const Race &race);
    Profession profession() const;
    void setProfession(const Profession &profession);
    Race second_race() const;
    void setSecond_race(const Race &second_race);
    Profession second_profession() const;
    void setSecond_profession(const Profession &second_profession);
    bool halfBlood_without_second_race() const;
    void setHalfBlood_without_second_race(bool halfBlood_without_second_race);
    bool superMunchkin_without_second_profession() const;
    void setSuperMunchkin_without_second_profession(bool superMunchkin_without_second_profession);


};

#endif // PLAYER_H