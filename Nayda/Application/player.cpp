#include "player.h"

QString Player::GetPlayersName() const
{
    return _name;
}

void Player::SetPlayersName(const QString &name)
{
    _name = name;
}

void Player::RemoveGivenCardsFromHand(const std::vector<SimpleCard> &cards)
{
    for (uint32_t var = 0; var < _cardsOnHands.size(); ++var)
    {
        for (uint32_t y = 0; y < cards.size(); ++y)
        {
            if (_cardsOnHands[var] == cards[y])
            {
               _cardsOnHands.erase(_cardsOnHands.begin() + static_cast<int32_t>(var));
            }
        }
    }
    _cardsOnHands.shrink_to_fit();
    qDebug() << "NAY-002: New size of the CardsOnHands Vector: " << _cardsOnHands.size();
}

void Player::RemoveGivenCardsFromCardsInGame(const std::vector<SimpleCard> &cards)
{
    for (uint32_t var = 0; var < _cardsInGame.size(); ++var)
    {
        for (uint32_t y = 0; y < cards.size(); ++y)
        {
            if (_cardsInGame[var] == cards[y])
            {
               _cardsInGame.erase(_cardsInGame.begin() + static_cast<int32_t>(var));
            }
        }
    }
    _cardsInGame.shrink_to_fit();
    qDebug() << "NAY-002: New size of the CardsInGame Vector: " << _cardsInGame.size();

}

void Player::RemoveGivenCardFromHand(SimpleCard card)
{
    for (uint32_t var = 0; var < _cardsOnHands.size(); ++var)
    {
        if (_cardsOnHands[var] == card)
        {
            _cardsOnHands.erase(_cardsOnHands.begin() + var);
            return;
        }
    }
    qDebug() << "NAY-002: ERROR WHILE void Player::RemoveGivenCardFromHand(SimpleCard card). Card not found!";
}

Players_Sex Player::playersSex() const
{
    return _playersSex;
}

void Player::setPlayersSex(const Players_Sex &playersSex)
{
    _playersSex = playersSex;
}

bool Player::GetHasFreeHireling() const
{
    return _hasFreeHireling;
}

void Player::SetHasFreeHireling(bool hasFreeHireling)
{
    _hasFreeHireling = hasFreeHireling;
}

bool Player::GetRightHandSlotFull() const
{
    return _rightHandSlotFull;
}

void Player::SetRightHandSlotFull(bool rightHandSlotFull)
{
    _rightHandSlotFull = rightHandSlotFull;
}


bool Player::GetArmorSlotFull() const
{
    return _armorSlotFull;
}

void Player::SetArmorSlotFull(bool armorSlotFull)
{
    _armorSlotFull = armorSlotFull;
}

int Player::GetFleeChance() const
{
    return _fleeChance;
}

void Player::SetFleeChance(int fleeChance)
{
    _fleeChance = fleeChance;
}

bool Player::GetIsProtectedFromCursesFromPlayers() const
{
    return _protectedFromCursesFromPlayers;
}

void Player::SetIsProtectedFromCursesFromPlayers(bool protectedFromCursesFromPlayers)
{
    _protectedFromCursesFromPlayers = protectedFromCursesFromPlayers;
}

bool Player::GetProtecetdFromCursesFromDoors() const
{
    return _protecetedFromCursesFromDoors;
}

void Player::SetIsProtecetedFromCursesFromDoors(bool protecetdFromCursesFromDoors)
{
    _protecetedFromCursesFromDoors = protecetdFromCursesFromDoors;
}

bool Player::GetCursesMirroring() const
{
    return _cursesMirroring;
}

void Player::SetHasCursesMirroring(bool cursesMirroring)
{
    _cursesMirroring = cursesMirroring;
}

bool Player::GetNotAbleToHelp() const
{
    return _notAbleToHelp;
}

void Player::SetNotAbleToHelp(bool notAbleToHelp)
{
    _notAbleToHelp = notAbleToHelp;
}

bool Player::GetIsProtectedFromOthersPotions() const
{
    return _protectedFromOthersPotions;
}

void Player::SetIsProtectedFromOthersPotions(bool protectedFromOthersPotions)
{
    _protectedFromOthersPotions = protectedFromOthersPotions;
}

bool Player::GetBonusFromNoseActive() const
{
    return _bonusFromNoseActive;
}

void Player::SetBonusFromNoseActive(bool bonusFromNoseActive)
{
    _bonusFromNoseActive = bonusFromNoseActive;
}

bool Player::GetHasFireArmor() const
{
    return _hasFireArmor;
}

void Player::SetHasFireArmor(bool hasFireArmor)
{
    _hasFireArmor = hasFireArmor;
}

bool Player::GetAbleToChangeSexOnline() const
{
    return _ableToChangeSexOnline;
}

void Player::SetIsAbleToChangeSexOnline(bool ableToChangeSexOnline)
{
    _ableToChangeSexOnline = ableToChangeSexOnline;
}

bool Player::GetProtectedFromTheft() const
{
    return _protectedFromTheft;
}

void Player::SetIsProtectedFromTheft(bool protectedFromTheft)
{
    _protectedFromTheft = protectedFromTheft;
}


uint32_t Player::GetCombinedFeet() const
{
    return _combinedFeet;
}

void Player::SetCombinedFeet(const uint32_t &combinedFeet)
{
    _combinedFeet = combinedFeet;
}

uint32_t Player::GetCombinedArmor() const
{
    return _combinedArmor;
}

void Player::SetCombinedArmor(const uint32_t &combinedArmor)
{
    _combinedArmor = combinedArmor;
}

uint32_t Player::GetCombinedHead() const
{
    return _combinedHead;
}

void Player::SetCombinedHead(const uint32_t &combinedHead)
{
    _combinedHead = combinedHead;
}

bool Player::CheckCardIsFromCardsInGame(SimpleCard card)
{
    for (uint32_t var = 0; var < _cardsInGame.size(); ++var)
    {
        if (_cardsInGame[var] == card)
            return true;
    }
    return false;
}

bool Player::CheckCardIsFromCardsOnHand(SimpleCard card)
{
    for (uint32_t var = 0; var < _cardsOnHands.size(); ++var)
    {
        if (_cardsOnHands[var] == card)
            return true;
    }
    return false;
}

Player::Player(const QString& name) : _name(name)
{
    _isMainPlayer = false;
    
    _playerLevel = 1;
    _battlePower = 1;
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

    _halfBloodWithoutSecondRace = false;
    _superMunchkinWithoutSecondProfession = false;

    //set default cards for races and classes;

    _race1Card.first = 0;
    _race1Card.second = 0;

    _race2Card.first = 0;
    _race2Card.second = 0;

    _class1Card.first = 0;
    _class1Card.second = 0;

    _class2Card.first = 0;
    _class2Card.second = 0;

}

void Player::addRaceActiveAbility(Race_Active_Abilities raceActiveAbility, Abilities_Keys_Races raceAbilityKey)
{
    _raceActiveAbilities.insert({raceActiveAbility, raceAbilityKey});
}


void Player::addRacePassiveAbility(Race_Passive_Abilities racePassiveAbility, Abilities_Keys_Races raceAbilityKey)
{
    _racePassiveAbilities.insert({racePassiveAbility, raceAbilityKey});
}


void Player::addProfessionActiveAbility(Profession_Active_Abilities professionActiveAbility, Abilities_Keys_Professions professionAbilityKey)
{
    _professionActiveAbilities.insert({professionActiveAbility, professionAbilityKey});
}


void Player::addProfessionPassiveAbility(Profession_Passive_Abilities professionPassiveAbility, Abilities_Keys_Professions professionAbilityKey)
{
    _professionPassiveAbilites.insert({professionPassiveAbility,professionAbilityKey});
}


bool Player::GetIsSuperMunchkinWithoutSecondProfession() const
{
    return _superMunchkinWithoutSecondProfession;
}


void Player::SetSuperMunchkinWithoutSecondProfession(bool superMunchkin_without_second_profession)
{
    _superMunchkinWithoutSecondProfession = superMunchkin_without_second_profession;
}


void Player::AddCardToHands(SimpleCard cardToBeAdded)
{
    _cardsOnHands.push_back(cardToBeAdded);
    //qDebug() << "Card"<< (cardToBeAdded.first == 0 ? "Door" : "Treasure") << "with cardID = " << cardToBeAdded.second << "was successfully added to _cardsOnHands!";

}


void Player::RemoveCardFromHands(SimpleCard cardToBeRemoved)
{
    std::vector<SimpleCard>::iterator it;
    it = std::find(_cardsOnHands.begin(), _cardsOnHands.end(), cardToBeRemoved);
    if (it != _cardsOnHands.end()) {


        qDebug() << "Card"<< ((*it).first == 0 ? "Door" : "Treasure") << "with cardID = " << (*it).second << "was successfully removed from _cardsOnHands!";
        _cardsOnHands.erase(it);
    }
    else {
        qDebug() << "ERROR During deleting a card from _cardsOnHandsVector!" ;
    }
}

void Player::AddCardToCardsInGame(SimpleCard card)
{
    _cardsInGame.push_back(card);
}

void Player::RemoveCardFromCardsInGame(SimpleCard card)
{
    std::vector<SimpleCard>::iterator it;
    it = std::find(_cardsInGame.begin(), _cardsOnHands.end(), card);
    if (it != _cardsInGame.end()) {


        qDebug() << "Card"<< ((*it).first == 0 ? "Door" : "Treasure") << "with cardID = " << (*it).second << "was successfully removed from _cardsOnHands!";
        _cardsInGame.erase(it);
    }
    else {
        qDebug() << "ERROR During deleting a card from _cardsInGameVector!" ;
    }
}


std::vector<SimpleCard> *Player::cardsOnHandsVector()
{
    return &_cardsOnHands;
}


std::vector<SimpleCard> *Player::cardsInGameVector()
{
    return &_cardsInGame;
}


bool Player::GetIsHalfBloodWithoutSecondRace() const
{
    return _halfBloodWithoutSecondRace;
}


void Player::SetHalfBloodWithoutSecondRace(bool halfBlood_without_second_race)
{
    _halfBloodWithoutSecondRace = halfBlood_without_second_race;
}


Profession Player::GetSecondProfession() const
{
    return _second_profession;
}


void Player::SetSecondProfession(const Profession &second_profession)
{
    _second_profession = second_profession;
}


Race Player::GetSecondRace() const
{
    return _second_race;
}


void Player::SetSecondRace(const Race &second_race)
{
    _second_race = second_race;
}


Profession Player::GetProfession() const
{
    return _profession;
}


void Player::SetProfession(const Profession &profession)
{
    _profession = profession;
}


Race Player::GetRace() const
{
    return _race;
}


void Player::SetRace(const Race &race)
{
    _race = race;
}


bool Player::GetThereIsLimitOnBigThings() const
{
    return _thereIsLimitOnBigThings;
}


void Player::SetThereIsLimitOnBigThings(bool thereIsLimitOnBigThings)
{
    _thereIsLimitOnBigThings = thereIsLimitOnBigThings;
}


bool Player::GetThereIsOneBigThing() const
{
    return _thereIsOneBigThing;
}


void Player::SetThereIsOneBigThing(bool thereIsOneBigThing)
{
    _thereIsOneBigThing = thereIsOneBigThing;
}


bool Player::GetRightHandSlotIsFull() const
{
    return _rightHandSlotFull;
}


void Player::SetRightHandSlotIsFull(bool rightHandSlotFull)
{
    _rightHandSlotFull = rightHandSlotFull;
}


bool Player::GetLeftHandSlotIsFull() const
{
    return _leftHandSlotFull;
}


void Player::SetLeftHandSlotIsFull(bool leftHandSlotFull)
{
    _leftHandSlotFull = leftHandSlotFull;
}


bool Player::GetLegsSlotIsFull() const
{
    return _legsSlotFull;
}


void Player::SetLegsSlotIsFull(bool legsSlotFull)
{
    _legsSlotFull = legsSlotFull;
}


bool Player::GetHeadSlotIsFull() const
{
    return _headSlotFull;
}


void Player::SetHeadSlotIsFull(bool headSlotFull)
{
    _headSlotFull = headSlotFull;
}


uint32_t Player::GetTotalCardsInGame() const
{
    return _cardsInGame.size();
}


void Player::SetTotalCardsInGame(int cards_in_game)
{
    _totalCardsInGame = cards_in_game;
}


uint32_t Player::GetCardsOnHandsLimit() const
{
    return _cardsOnHandsLimit;
}


void Player::SetCardsOnHandsLimit(int cardsOnHandsLimit)
{
    _cardsOnHandsLimit = cardsOnHandsLimit;
}


uint32_t Player::GetCardsOnHands() const
{
    return _cardsOnHands.size();
}



int Player::GetBattlePower() const
{
    return _battlePower;
}


void Player::SetBattlePower(int battlePower)
{
    _battlePower = battlePower;
}


uint32_t Player::GetPlayerLevel() const
{
    return _playerLevel;
}


void Player::SetPlayerLevel(uint32_t playerLevel)
{
    _playerLevel = playerLevel;
}
