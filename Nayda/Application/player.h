#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include "card.h" //since it is better to store "Races", "Professions" inside the class of card.h
#include <QDebug>
#include "munchkinglobaldefines.h"
#include "smartqtlogger.h"


class Player
{
    Logger logger;

    QString _name = "";

    bool _isMainPlayer = false;

    uint32_t _playerLevel = 1;
    int _battlePower = 1;

    uint32_t _additionalBonusAgainstAndead = 0;
    uint32_t _additionalBonusAgainst_J = 0;

    bool _automaticLooseToCalmadzilla = false;

    int _fleeChance = 5; //less than - loose

    uint32_t _totalCardsOnHands = HardCodedSettingsLimitations::totalCardsToGiveFromTheStart *2;
    uint32_t _cardsOnHandsLimit = HardCodedSettingsLimitations::maximumCardsOnHandsInitialLimitation;
    uint32_t _totalCardsInGame = 0;

    bool _headSlotFull = false;
    bool _legsSlotFull = false;
    bool _leftHandSlotFull = false;
    bool _rightHandSlotFull = false;
    bool _armorSlotFull = false;

    int32_t _freeHands = 2;
    uint32_t _totalHands = 2;
    bool _affectedByTinyHands = false;

    bool _hasAdditionalClericalAbility = false;
    bool _hasAdditionalTheftAbility = false;

    bool     _thereIsOneBigThing = false;
    uint32_t _totalBigThings = 0;
    bool     _thereIsLimitOnBigThings= true; //may be remove it if checking the race

    //А вот эта конструкция легко бы влезла в std::optional
    bool _thereIsBigThingModifiedByConvinientHandles = false;
    uint32_t _cardIdModifiedByConvinientHandles = 0;

    bool _hasFreeHireling = false;
    uint32_t _totalHireLings = 0;

    Race _race = Race::Human;
    Profession _profession = Profession::No_Profession;
    PlayerSex _playersSex = PlayerSex::Man;

    bool _halfBreed = false;
    bool _superMunchkin = false;

    Race _secondRace = Race::Human;
    Profession _second_profession = Profession::No_Profession;

    bool _halfBloodWithoutSecondRace = false;
    bool _superMunchkinWithoutSecondProfession = false;

    std::map <Race_Active_Abilities, Abilities_Keys_Races> _raceActiveAbilities;
    std::map <Race_Passive_Abilities, Abilities_Keys_Races> _racePassiveAbilities;
    std::map <Profession_Active_Abilities, Abilities_Keys_Professions> _professionActiveAbilities;
    std::map <Profession_Passive_Abilities, Abilities_Keys_Professions> _professionPassiveAbilites;

    std::vector<SimpleCard> _cardsOnHands;

    std::vector<SimpleCard> _activeCardsInGame;
    std::vector<SimpleCard> _disabledCardsInGame;
    std::vector<AmplifierCard> _amplifiersInGame;

    //Cards responsible for the Races and Classes
    SimpleCard _race1Card;
    SimpleCard _race2Card;
    SimpleCard _class1Card;
    SimpleCard _class2Card;


    //Enabling additional passive mechanics:
    bool _protectedFromCursesFromPlayers = false; // Шапочка из фольги
    bool _protecetedFromCursesFromDoors = false; // Сандалеты-Протекторы
    bool _cursesMirroring = false; // Сиятельная шляпа
    bool _notAbleToHelp = false; // Вонючие потники
    bool _protectedFromOthersPotions = false; //Дождевик
    bool _bonusFromNoseActive = false; //вонючие носки дадут плюс 5; 
    bool _hasFireArmor = false; //Пламенный доспех
    bool _ableToChangeSexOnline = false; //Опорки по Фрейду
    bool _protectedFromTheft = false; // Шлем заднего вида

    //Enabling additional special mechanics from weapon:
    bool _hasBoomDagger = false;
    bool _hasRatOnAStick = false;
    bool _hasSiegeEngine = false;
    bool _hasStabAMatic = false;
    bool _hasTubaOfCharm = false;

    //Для более лёгкого определения, какую карту стоит сбросить в процессе удаления основной
    uint32_t _combinedFeet = 0;
    uint32_t _combinedArmor = 0;
    uint32_t _combinedHead = 0;

public:

    bool CheckCardIsFromCardsInGame(SimpleCard card);
    bool CheckCardIsFromCardsOnHand(SimpleCard card);

public:

    explicit Player(const QString& player);

    void addRaceActiveAbility(Race_Active_Abilities raceActiveAbility, Abilities_Keys_Races raceAbilityKey);
    void addRacePassiveAbility(Race_Passive_Abilities racePassiveAbility, Abilities_Keys_Races raceAbilityKey);
    void addProfessionActiveAbility(Profession_Active_Abilities professionActiveAbility, Abilities_Keys_Professions professionAbilityKey);
    void addProfessionPassiveAbility(Profession_Passive_Abilities professionPassiveAbility, Abilities_Keys_Professions professionAbilityKey);

    uint32_t GetPlayerLevel() const;
    void SetPlayerLevel(uint32_t GetPlayerLevel);
    int GetBattlePower() const;
    void SetBattlePower(int battlePower);
    int GetFleeChance() const;
    void SetFleeChance(int GetFleeChance);

    uint32_t GetCardsOnHands() const;
    uint32_t GetCardsOnHandsLimit() const;
    void SetCardsOnHandsLimit(int GetCardsOnHandsLimit);
    uint32_t GetTotalCardsInGame() const;
    void SetTotalCardsInGame(int cards_in_game);


    bool GetHeadSlotIsFull() const;
    void SetHeadSlotIsFull(bool GetHeadSlotIsFull);
    bool GetLegsSlotIsFull() const;
    void SetLegsSlotIsFull(bool GetLegsSlotIsFull);

    //May be useless...
    bool GetLeftHandSlotIsFull() const;
    void SetLeftHandSlotIsFull(bool GetLeftHandSlotIsFull);
    bool GetRightHandSlotFull() const;
    void SetRightHandSlotFull(bool GetRightHandSlotFull);

    int32_t GetFreeHands() const { return _freeHands; }
    void ChangeFreeHands(int32_t diff);

    bool GetIsAffectedByTinyHands() const;
    void SetIsAffectedByTinyHands(bool GetIsAffectedByTinyHands);

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
    PlayerSex GetPlayerSex() const;
    void SetPlayerSex(const PlayerSex &GetPlayerSex);
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

    void AddCardToCardsInGame(CardInGame);
    void RemoveCardFromCardsInGame(SimpleCard);

    void AddAmplifierToCardsInGame(AmplifierCard amplifier);

    bool CardIsActive(SimpleCard card);

    std::vector<SimpleCard>* cardsOnHandsVector();

    const std::vector<SimpleCard>& GetCardsOnHands()
    { return _cardsOnHands; }

    std::vector<SimpleCard> GetCardsInGame()
    { return (_activeCardsInGame + _disabledCardsInGame); }

    //Игрок не может выполнить эту процедуру - у него нет доступа к наполняемым массивам карт
    //std::vector<ActiveIncativeCard> GetBigThingsInGame();

    QString GetPlayerName() const;
    void SetPlayersName(const QString &GetPlayerName);

    void RemoveGivenCardsFromHand(const std::vector<SimpleCard>& cards);
    void RemoveGivenCardsFromCardsInGame(const std::vector<SimpleCard>& cards);

    void RemoveGivenCardFromHand(SimpleCard card);

    bool GetHasFreeHireling() const;
    void SetHasFreeHireling(bool GetHasFreeHireling);

    bool GetIsProtectedFromCursesFromPlayers() const;
    void SetIsProtectedFromCursesFromPlayers(bool GetIsProtectedFromCursesFromPlayers);

    bool GetProtecetdFromCursesFromDoors() const;
    void SetIsProtecetedFromCursesFromDoors(bool GetProtecetdFromCursesFromDoors);

    bool GetCursesMirroring() const;
    void SetHasCursesMirroring(bool GetCursesMirroring);

    bool GetNotAbleToHelp() const;
    void SetNotAbleToHelp(bool GetNotAbleToHelp);

    bool GetIsProtectedFromOthersPotions() const;
    void SetIsProtectedFromOthersPotions(bool GetIsProtectedFromOthersPotions);

    bool GetBonusFromNoseActive() const;
    void SetBonusFromNoseActive(bool GetBonusFromNoseActive);

    bool GetHasFireArmor() const;
    void SetHasFireArmor(bool GetHasFireArmor);
    
    bool GetAbleToChangeSexOnline() const;
    void SetIsAbleToChangeSexOnline(bool GetAbleToChangeSexOnline);
    
    bool GetProtectedFromTheft() const;
    void SetIsProtectedFromTheft(bool protectedFromTheft);



    uint32_t GetCombinedFeet() const;
    void SetCombinedFeet(const uint32_t &GetCombinedFeet);

    uint32_t GetCombinedArmor() const;
    void SetCombinedArmor(const uint32_t &GetCombinedArmor);

    uint32_t GetCombinedHead() const;
    void SetCombinedHead(const uint32_t &GetCombinedHead);

    uint32_t GetAdditionalBonusAgainstAndead() const;
    void SetAdditionalBonusAgainstUndead(const uint32_t &GetAdditionalBonusAgainstAndead);

    uint32_t GetAdditionalBonusAgainst_J() const;
    void SetAdditionalBonusAgainst_J(const uint32_t &GetAdditionalBonusAgainst_J);

    bool GetAutomaticLooseToCalmadzilla() const;
    void SetAutomaticLooseToCalmadzilla(bool GetAutomaticLooseToCalmadzilla);

    bool HasAdditionalClericalAbility() const;
    void SetHasAdditionalClericalAbility(bool HasAdditionalClericalAbility);

    bool HasAdditionalTheftAbility() const;
    void SetHasAdditionalTheftAbility(bool HasAdditionalTheftAbility);

    bool HasBoomDagger() const;
    void SetHasBoomDagger(bool HasBoomDagger);

    bool HasRatOnAStick() const;
    void SetHasRatOnAStick(bool HasRatOnAStick);

    bool HasSiegeEngine() const;
    void SetHasSiegeEngine(bool HasSiegeEngine);

    bool HasStabAMatic() const;
    void SetHasStabAMatic(bool HasStabAMatic);

    bool HasTubaOfCharm() const;
    void SetHasTubaOfCharm(bool HasTubaOfCharm);

    std::vector<SimpleCard> GetActiveCardsInGame() const;
    std::vector<SimpleCard> GetDisabledCardsInGame() const;

    bool IsDwarf() const;

public:

    bool CheckThereIsBigThingModifiedByConvinientHandles() {return _thereIsBigThingModifiedByConvinientHandles; }
    void SetThereIsThingModifiedByConvinientHandles(uint32_t cardId)
    {
        _thereIsBigThingModifiedByConvinientHandles = true;
        _cardIdModifiedByConvinientHandles = cardId;
    }

    uint32_t GetTotalBigThings() const;
    void SetTotalBigThings(const uint32_t &GetTotalBigThings);

private:
    
    //it is necessary to save the property in the player class of the card responsible for the
    //class review
    //SimpleCard

};

#endif // PLAYER_H
