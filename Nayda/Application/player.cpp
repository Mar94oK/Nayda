#include "player.h"

player::player()
{
    _isMainPlayer = false;

    _playerLevel = 1;
    _warPower = 1;
    _totalCardsOnHands = 0;
    _cardsOnHandsLimit = 5;
    _totalCardsInGame = 0;

    _headSlotFull = false;
    _legsSlotFull = false;
    _leftHandSlotFull = false;
    _rightHandSlotFull = false;
    _thereIsOneBigThing = false;
    _thereIsLimitOnBigThings = true;

    _race = Race::Human;
    _profession = Profession::No_Profession;

    _halfBreed = false;
    _superMunchkin = false;

    _second_race = Race::Human;
    _second_profession = Profession::No_Profession;

    _halfBlood_without_second_race = false;
    _superMunchkin_without_second_profession = false;









}

void player::addRaceActiveAbility(Race_Active_Abilities raceActiveAbility, Abilities_Keys_Races raceAbilityKey)
{
    _raceActiveAbilities.insert({raceActiveAbility, raceAbilityKey});
}

void player::addRacePassiveAbility(Race_Passive_Abilities racePassiveAbility, Abilities_Keys_Races raceAbilityKey)
{
    _racePassiveAbilities.insert({racePassiveAbility, raceAbilityKey});
}

void player::addProfessionActiveAbility(Profession_Active_Abilities professionActiveAbility, Abilities_Keys_Professions professionAbilityKey)
{
    _professionActiveAbilities.insert({professionActiveAbility, professionAbilityKey});
}

void player::addProfessionPassiveAbility(Profession_Passive_Abilities professionPassiveAbility, Abilities_Keys_Professions professionAbilityKey)
{
    _professionPassiveAbilites.insert({professionPassiveAbility,professionAbilityKey});
}

bool player::superMunchkin_without_second_profession() const
{
    return _superMunchkin_without_second_profession;
}

void player::setSuperMunchkin_without_second_profession(bool superMunchkin_without_second_profession)
{
    _superMunchkin_without_second_profession = superMunchkin_without_second_profession;
}

bool player::halfBlood_without_second_race() const
{
    return _halfBlood_without_second_race;
}

void player::setHalfBlood_without_second_race(bool halfBlood_without_second_race)
{
    _halfBlood_without_second_race = halfBlood_without_second_race;
}

Profession player::second_profession() const
{
    return _second_profession;
}

void player::setSecond_profession(const Profession &second_profession)
{
    _second_profession = second_profession;
}

Race player::second_race() const
{
    return _second_race;
}

void player::setSecond_race(const Race &second_race)
{
    _second_race = second_race;
}





Profession player::profession() const
{
    return _profession;
}

void player::setProfession(const Profession &profession)
{
    _profession = profession;
}

Race player::race() const
{
    return _race;
}

void player::setRace(const Race &race)
{
    _race = race;
}

bool player::thereIsLimitOnBigThings() const
{
    return _thereIsLimitOnBigThings;
}

void player::setThereIsLimitOnBigThings(bool thereIsLimitOnBigThings)
{
    _thereIsLimitOnBigThings = thereIsLimitOnBigThings;
}

bool player::thereIsOneBigThing() const
{
    return _thereIsOneBigThing;
}

void player::setThereIsOneBigThing(bool thereIsOneBigThing)
{
    _thereIsOneBigThing = thereIsOneBigThing;
}

bool player::rightHandSlotFull() const
{
    return _rightHandSlotFull;
}

void player::setRightHandSlotFull(bool rightHandSlotFull)
{
    _rightHandSlotFull = rightHandSlotFull;
}

bool player::leftHandSlotFull() const
{
    return _leftHandSlotFull;
}

void player::setLeftHandSlotFull(bool leftHandSlotFull)
{
    _leftHandSlotFull = leftHandSlotFull;
}

bool player::legsSlotFull() const
{
    return _legsSlotFull;
}

void player::setLegsSlotFull(bool legsSlotFull)
{
    _legsSlotFull = legsSlotFull;
}

bool player::headSlotFull() const
{
    return _headSlotFull;
}

void player::setHeadSlotFull(bool headSlotFull)
{
    _headSlotFull = headSlotFull;
}

int player::cards_in_game() const
{
    return _totalCardsInGame;
}

void player::setCards_in_game(int cards_in_game)
{
    _totalCardsInGame = cards_in_game;
}

int player::cardsOnHandsLimit() const
{
    return _cardsOnHandsLimit;
}

void player::setCardsOnHandsLimit(int cardsOnHandsLimit)
{
    _cardsOnHandsLimit = cardsOnHandsLimit;
}

int player::cardsOnHands() const
{
    return _totalCardsOnHands;
}

void player::setCardsOnHands(int cardsOnHands)
{
    _totalCardsOnHands = cardsOnHands;
}

int player::warPower() const
{
    return _warPower;
}

void player::setWarPower(int warPower)
{
    _warPower = warPower;
}

int player::playerLevel() const
{
    return _playerLevel;
}

void player::setPlayerLevel(int playerLevel)
{
    _playerLevel = playerLevel;
}
