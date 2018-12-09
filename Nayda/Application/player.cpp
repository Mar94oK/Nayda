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
               _cardsOnHands.erase(_cardsOnHands.begin() + var);
            }
        }
    }
    _cardsOnHands.shrink_to_fit();
    qDebug() << "NAY-002: New size of the CardsOnHands Vector: " << _cardsOnHands.size();
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

Player::Player(const QString& name) : _name(name)
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


bool Player::superMunchkin_without_second_profession() const
{
    return _superMunchkin_without_second_profession;
}


void Player::setSuperMunchkin_without_second_profession(bool superMunchkin_without_second_profession)
{
    _superMunchkin_without_second_profession = superMunchkin_without_second_profession;
}


void Player::addCardToHands(SimpleCard cardToBeAdded)
{
    _cardsOnHands.push_back(cardToBeAdded);
    //qDebug() << "Card"<< (cardToBeAdded.first == 0 ? "Door" : "Treasure") << "with cardID = " << cardToBeAdded.second << "was successfully added to _cardsOnHands!";

}


void Player::removeCardFromHands(SimpleCard cardToBeRemoved)
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


std::vector<SimpleCard> *Player::cardsOnHandsVector()
{
    return &_cardsOnHands;
}


std::vector<SimpleCard> *Player::cardsInGameVector()
{
    return &_cardsInGame;
}


bool Player::halfBlood_without_second_race() const
{
    return _halfBlood_without_second_race;
}


void Player::setHalfBlood_without_second_race(bool halfBlood_without_second_race)
{
    _halfBlood_without_second_race = halfBlood_without_second_race;
}


Profession Player::second_profession() const
{
    return _second_profession;
}


void Player::setSecond_profession(const Profession &second_profession)
{
    _second_profession = second_profession;
}


Race Player::second_race() const
{
    return _second_race;
}


void Player::setSecond_race(const Race &second_race)
{
    _second_race = second_race;
}


Profession Player::profession() const
{
    return _profession;
}


void Player::setProfession(const Profession &profession)
{
    _profession = profession;
}


Race Player::race() const
{
    return _race;
}


void Player::setRace(const Race &race)
{
    _race = race;
}


bool Player::thereIsLimitOnBigThings() const
{
    return _thereIsLimitOnBigThings;
}


void Player::setThereIsLimitOnBigThings(bool thereIsLimitOnBigThings)
{
    _thereIsLimitOnBigThings = thereIsLimitOnBigThings;
}


bool Player::thereIsOneBigThing() const
{
    return _thereIsOneBigThing;
}


void Player::setThereIsOneBigThing(bool thereIsOneBigThing)
{
    _thereIsOneBigThing = thereIsOneBigThing;
}


bool Player::rightHandSlotFull() const
{
    return _rightHandSlotFull;
}


void Player::setRightHandSlotFull(bool rightHandSlotFull)
{
    _rightHandSlotFull = rightHandSlotFull;
}


bool Player::leftHandSlotFull() const
{
    return _leftHandSlotFull;
}


void Player::setLeftHandSlotFull(bool leftHandSlotFull)
{
    _leftHandSlotFull = leftHandSlotFull;
}


bool Player::legsSlotFull() const
{
    return _legsSlotFull;
}


void Player::setLegsSlotFull(bool legsSlotFull)
{
    _legsSlotFull = legsSlotFull;
}


bool Player::headSlotFull() const
{
    return _headSlotFull;
}


void Player::setHeadSlotFull(bool headSlotFull)
{
    _headSlotFull = headSlotFull;
}


uint32_t Player::cardsInGame() const
{
    return _cardsInGame.size();
}


void Player::setCards_in_game(int cards_in_game)
{
    _totalCardsInGame = cards_in_game;
}


uint32_t Player::cardsOnHandsLimit() const
{
    return _cardsOnHandsLimit;
}


void Player::setCardsOnHandsLimit(int cardsOnHandsLimit)
{
    _cardsOnHandsLimit = cardsOnHandsLimit;
}


uint32_t Player::GetCardsOnHands() const
{
    return _cardsOnHands.size();
}



int Player::GetWarPower() const
{
    return _warPower;
}


void Player::SetWarPower(int warPower)
{
    _warPower = warPower;
}


uint32_t Player::GetPlayerLevel() const
{
    return _playerLevel;
}


void Player::SetPlayerLevel(uint32_t playerLevel)
{
    _playerLevel = playerLevel;
}
