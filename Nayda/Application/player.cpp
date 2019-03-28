#include "player.h"

QString Player::GetPlayerName() const
{
    return _name;
}

void Player::SetPlayersName(const QString &name)
{
    _name = name;
}

void Player::RemoveGivenCardsFromHand(const std::vector<SimpleCard> &cards)
{
    qDebug() << "Delete correction checker: Player::RemoveGivenCardsFromHand: cards Size: " << cards.size();
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        for (uint32_t y = 0; y < _cardsOnHands.size(); ++y)
        {
            if (_cardsOnHands[y] == cards[var])
            {
               qDebug() << "Delete correction checker: Player::RemoveGivenCardsFromHand: ID: " << _cardsOnHands[var].second;
                _cardsOnHands.erase(_cardsOnHands.begin() + static_cast<int32_t>(y));
            }
        }
    }
    _cardsOnHands.shrink_to_fit();
    qDebug() << "NAY-002: New size of the CardsOnHands Vector: " << _cardsOnHands.size();
}

void Player::RemoveGivenCardsFromCardsInGame(const std::vector<SimpleCard> &cards)
{
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        RemoveCardFromCardsInGame(cards[var]);
    }
}

void Player::RemoveGivenCardFromHand(SimpleCard card)
{
    for (uint32_t var = 0; var < _cardsOnHands.size(); ++var)
    {
        if (_cardsOnHands[var] == card)
        {
            _cardsOnHands.erase(_cardsOnHands.begin() + static_cast<int32_t>(var));
            return;
        }
    }
    qDebug() << "NAY-002: ERROR WHILE void Player::RemoveGivenCardFromHand(SimpleCard card). Card not found!";
}

PlayerSex Player::GetPlayerSex() const
{
    return _playersSex;
}

void Player::SetPlayerSex(const PlayerSex &playersSex)
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

void Player::ChangeFreeHands(int32_t diff)
{ _freeHands = _freeHands + diff; }


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

bool Player::GetIsAffectedByTinyHands() const
{
    return _affectedByTinyHands;
}

void Player::SetIsAffectedByTinyHands(bool affectedByTinyHands)
{
    _affectedByTinyHands = affectedByTinyHands;
}

uint32_t Player::GetAdditionalBonusAgainstAndead() const
{
    return _additionalBonusAgainstAndead;
}

void Player::SetAdditionalBonusAgainstUndead(const uint32_t &additionalBonusAgainstAndead)
{
    _additionalBonusAgainstAndead = additionalBonusAgainstAndead;
}

uint32_t Player::GetAdditionalBonusAgainst_J() const
{
    return _additionalBonusAgainst_J;
}

void Player::SetAdditionalBonusAgainst_J(const uint32_t &additionalBonusAgainst_J)
{
    _additionalBonusAgainst_J = additionalBonusAgainst_J;
}

bool Player::GetAutomaticLooseToCalmadzilla() const
{
    return _automaticLooseToCalmadzilla;
}

void Player::SetAutomaticLooseToCalmadzilla(bool automaticLooseToCalmadzilla)
{
    _automaticLooseToCalmadzilla = automaticLooseToCalmadzilla;
}

bool Player::HasAdditionalClericalAbility() const
{
    return _hasAdditionalClericalAbility;
}

void Player::SetHasAdditionalClericalAbility(bool hasAdditionalClericalAbility)
{
    _hasAdditionalClericalAbility = hasAdditionalClericalAbility;
}

bool Player::HasAdditionalTheftAbility() const
{
    return _hasAdditionalTheftAbility;
}

void Player::SetHasAdditionalTheftAbility(bool hasAdditionalTheftAbility)
{
    _hasAdditionalTheftAbility = hasAdditionalTheftAbility;
}

bool Player::HasBoomDagger() const
{
    return _hasBoomDagger;
}

void Player::SetHasBoomDagger(bool hasBoomDagger)
{
    _hasBoomDagger = hasBoomDagger;
}

bool Player::HasRatOnAStick() const
{
    return _hasRatOnAStick;
}

void Player::SetHasRatOnAStick(bool hasRatOnAStick)
{
    _hasRatOnAStick = hasRatOnAStick;
}

bool Player::HasSiegeEngine() const
{
    return _hasSiegeEngine;
}

void Player::SetHasSiegeEngine(bool hasSiegeEngine)
{
    _hasSiegeEngine = hasSiegeEngine;
}

bool Player::HasStabAMatic() const
{
    return _hasStabAMatic;
}

void Player::SetHasStabAMatic(bool hasStabAMatic)
{
    _hasStabAMatic = hasStabAMatic;
}

bool Player::HasTubaOfCharm() const
{
    return _hasTubaOfCharm;
}

void Player::SetHasTubaOfCharm(bool hasTubaOfCharm)
{
    _hasTubaOfCharm = hasTubaOfCharm;
}

std::vector<SimpleCard> Player::GetActiveCardsInGame() const
{
    return _activeCardsInGame;
}

std::vector<SimpleCard> Player::GetDisabledCardsInGame() const
{
    return _disabledCardsInGame;
}

bool Player::CheckCardIsFromCardsInGame(SimpleCard card)
{
    for (uint32_t var = 0; var < _activeCardsInGame.size(); ++var)
    {
        if (_activeCardsInGame[var] == card)
            return true;
    }
    for (uint32_t var = 0; var < _disabledCardsInGame.size(); ++var)
    {
        if (_disabledCardsInGame[var] == card)
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
    DECLARE_NAMED_LOGGER(Player);

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

void Player::AddCardToCardsInGame(CardInGame card)
{
    if (card.first)
        _activeCardsInGame.push_back(card.second);
    else
        _disabledCardsInGame.push_back(card.second);

}


//Удаление карты удалит и её усилитель
void Player::RemoveCardFromCardsInGame(SimpleCard card)
{
    std::vector<SimpleCard>::iterator itActive;
    itActive = std::find(_activeCardsInGame.begin(), _activeCardsInGame.end(), card);

    for (std::vector<AmplifierCard>::iterator it = _amplifiersInGame.begin(); it != _amplifiersInGame.end(); ++it)
    {
        if (it->second == card)
        {
            logger.Algorithm() << "Amplifier with cardID = " << it->second.second << " was successfully removed from _amplifiersInGame!";
            _amplifiersInGame.erase(it);
            _activeCardsInGame.shrink_to_fit();
        }
    }

    if (itActive != _activeCardsInGame.end())
    {
        logger.Algorithm() << "Card"<< ((*itActive).first == 0 ? "Door" : "Treasure") << "with cardID = " << (*itActive).second << "was successfully removed from _activeCardsInGame!";
        _activeCardsInGame.erase(itActive);
        _activeCardsInGame.shrink_to_fit();
        return;
    }
    else
    {
        logger.Error() << "WARNING: During deleting a card from _activeCardsInGame. May be card is not active?" ;
    }

    std::vector<SimpleCard>::iterator itDisabled;
    itDisabled = std::find(_disabledCardsInGame.begin(), _disabledCardsInGame.end(), card);
    if (itDisabled != _activeCardsInGame.end()) {

        logger.Algorithm() << "Card"<< ((*itDisabled).first == 0 ? "Door" : "Treasure") << "with cardID = " << (*itDisabled).second << "was successfully removed from _disabledCardsInGame!";
        _disabledCardsInGame.erase(itDisabled);
        _disabledCardsInGame.shrink_to_fit();
        return;
    }
    else
    {
        logger.Debug() << "ERROR: During deleting a card from _disabledCardsInGame. CARD NOT FOUND." ;
    }
}

void Player::AddAmplifierToCardsInGame(AmplifierCard amplifier)
{
    _amplifiersInGame.push_back(amplifier);
}

std::vector<SimpleCard> *Player::cardsOnHandsVector()
{
    return &_cardsOnHands;
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
    return _disabledCardsInGame.size() + _activeCardsInGame.size();
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

bool Player::CardIsActive(SimpleCard card)
{
    for (uint32_t var = 0; var < _activeCardsInGame.size(); ++var)
    {
        if (card == _activeCardsInGame[var])
        {
            return true;
        }
    }
    for (uint32_t var = 0; var < _disabledCardsInGame.size(); ++var)
    {
        if (card == _disabledCardsInGame[var])
        {
            return false;
        }
    }
    qDebug() << "ERROR! bool Player::CardIsActive(SimpleCard card) Card NOT FOUND!";
    return false;
}
