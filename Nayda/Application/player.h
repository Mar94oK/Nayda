#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include "card.h" //since it is better to store "Races", "Professions" inside the class of card.h
#include <QDebug>
#include "munchkinglobaldefines.h"



class Player
{
    QString _name = "";

    bool _isMainPlayer = false;

    uint32_t _playerLevel = 1;
    int _warPower = 1;

    int _fleeChance = 5; //less than - loose

    uint32_t _totalCardsOnHands = HardCodedSettingsLimitations::totalCardsToGiveFromTheStart *2;
    uint32_t _cardsOnHandsLimit = HardCodedSettingsLimitations::maximumCardsOnHandsInitialLimitation;
    uint32_t _totalCardsInGame = 0;

    bool _headSlotFull = false;
    bool _legsSlotFull = false;
    bool _leftHandSlotFull = false;
    bool _rightHandSlotFull = false;
    bool _armorSlotFull = false;

    bool _thereIsOneBigThing = false;
    bool _thereIsLimitOnBigThings= true; //may be remove it if checking the race

    bool _hasFreeHireling = false;
    uint32_t _totalHireLings = 0;

    Race _race = Race::Human;
    Profession _profession = Profession::No_Profession;
    Players_Sex _playersSex = Players_Sex::Man;

    bool _halfBreed = false;
    bool _superMunchkin = false;

    Race _second_race = Race::Human;
    Profession _second_profession = Profession::No_Profession;

    bool _halfBloodWithoutSecondRace = false;
    bool _superMunchkinWithoutSecondProfession = false;

    std::map <Race_Active_Abilities, Abilities_Keys_Races> _raceActiveAbilities;
    std::map <Race_Passive_Abilities, Abilities_Keys_Races> _racePassiveAbilities;
    std::map <Profession_Active_Abilities, Abilities_Keys_Professions> _professionActiveAbilities;
    std::map <Profession_Passive_Abilities, Abilities_Keys_Professions> _professionPassiveAbilites;

    std::vector<SimpleCard> _cardsOnHands;
    std::vector<SimpleCard> _cardsInGame;

    //Cards responsible for the Races and Classes
    SimpleCard _race1Card;
    SimpleCard _race2Card;
    SimpleCard _class1Card;
    SimpleCard _class2Card;


    //Enabling additional passive mechanics:
    bool _protectedFromCursesFromDoors = false; // Шапочка из фольги
    bool _protecetdFromCursesFromDoors = false; // Саналеты-Протекторы
    bool _cursesMirroring = false; // Сиятельная шляпа
    bool _notAbleToHelp = false; // Вонючие потники
    bool _protectedFromOthersPotions = false; //Дождевик

    bool _bonusFromNoseActive = false; //вонючие носки дадут плюс 5;

public:

    explicit Player(const QString& player);

    void addRaceActiveAbility(Race_Active_Abilities raceActiveAbility, Abilities_Keys_Races raceAbilityKey);
    void addRacePassiveAbility(Race_Passive_Abilities racePassiveAbility, Abilities_Keys_Races raceAbilityKey);
    void addProfessionActiveAbility(Profession_Active_Abilities professionActiveAbility, Abilities_Keys_Professions professionAbilityKey);
    void addProfessionPassiveAbility(Profession_Passive_Abilities professionPassiveAbility, Abilities_Keys_Professions professionAbilityKey);

    uint32_t GetPlayerLevel() const;
    void SetPlayerLevel(uint32_t GetPlayerLevel);
    int GetWarPower() const;
    void SetWarPower(int GetWarPower);
    int GetFleeChance() const;
    void SetFleeChance(int GetFleeChance);


    uint32_t GetCardsOnHands() const;
    uint32_t GetCardsOnHandsLimit() const;
    void SetCardsOnHandsLimit(int GetCardsOnHandsLimit);
    uint32_t GetTotalCardsInGame() const;
    void SetTotalCardsInGame(int GetTotalCardsInGame);


    bool GetHeadSlotIsFull() const;
    void SetHeadSlotIsFull(bool GetHeadSlotIsFull);
    bool GetLegsSlotIsFull() const;
    void SetLegsSlotIsFull(bool GetLegsSlotIsFull);
    bool GetLeftHandSlotIsFull() const;
    void SetLeftHandSlotIsFull(bool GetLeftHandSlotIsFull);
    bool GetRightHandSlotFull() const;
    void SetRightHandSlotFull(bool GetRightHandSlotFull);
    bool GetArmorSlotFull() const;
    void SetArmorSlotFull(bool GetArmorSlotFull);


    bool GetRightHandSlotIsFull() const;
    void SetRightHandSlotIsFull(bool GetRightHandSlotIsFull);
    bool GetThereIsOneBigThing() const;
    void SetThereIsOneBigThing(bool GetThereIsOneBigThing);
    bool GetThereIsLimitOnBigThings() const;
    void SetThereIsLimitOnBigThings(bool GetThereIsLimitOnBigThings);
    Race GetRace() const;
    void SetRace(const Race &GetRace);
    Profession GetProfession() const;
    void SetProfession(const Profession &GetProfession);
    Race GetSecondRace() const;
    void SetSecondRace(const Race &GetSecondRace);
    Profession GetSecondProfession() const;
    void SetSecondProfession(const Profession &GetSecondProfession);
    bool GetIsHalfBloodWithoutSecondRace() const;
    void SetHalfBloodWithoutSecondRace(bool GetIsHalfBloodWithoutSecondRace);
    bool GetIsSuperMunchkinWithoutSecondProfession() const;
    void SetSuperMunchkinWithoutSecondProfession(bool GetIsSuperMunchkinWithoutSecondProfession);

    void AddCardToHands(SimpleCard);
    void RemoveCardFromHands(SimpleCard);

    std::vector<SimpleCard>* cardsOnHandsVector();
    std::vector<SimpleCard>* cardsInGameVector();

    const std::vector<SimpleCard>& GetCardsOnHands()
    { return _cardsOnHands; }

    const std::vector<SimpleCard>& GetCardsInGame()
    { return _cardsInGame; }

    QString GetPlayersName() const;
    void SetPlayersName(const QString &GetPlayersName);

    void RemoveGivenCardsFromHand(const std::vector<SimpleCard>& cards);
    void RemoveGivenCardFromHand(SimpleCard card);

    Players_Sex playersSex() const;
    void setPlayersSex(const Players_Sex &playersSex);

    bool GetHasFreeHireling() const;
    void SetHasFreeHireling(bool GetHasFreeHireling);

    bool GetIsProtectedFromCursesFromDoors() const;
    void SetIsProtectedFromCursesFromDoors(bool GetIsProtectedFromCursesFromDoors);

    bool GetProtecetdFromCursesFromDoors() const;
    void SetProtecetdFromCursesFromDoors(bool GetProtecetdFromCursesFromDoors);

    bool GetCursesMirroring() const;
    void SetCursesMirroring(bool GetCursesMirroring);

    bool GetNotAbleToHelp() const;
    void SetNotAbleToHelp(bool GetNotAbleToHelp);

    bool GetIsProtectedFromOthersPotions() const;
    void SetIsProtectedFromOthersPotions(bool GetIsProtectedFromOthersPotions);

    bool GetBonusFromNoseActive() const;
    void SetBonusFromNoseActive(bool GetBonusFromNoseActive);

private:

    //it is necessary to save the property in the player class of the card responsible for the
    //class review
    //SimpleCard

};

#endif // PLAYER_H
