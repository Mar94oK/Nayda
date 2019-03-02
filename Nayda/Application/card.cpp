#include "card.h"

Game_Card_Stock::Game_Card_Stock()
{

}


Game_Card_Stock::Game_Card_Stock(int stock_type, int total_cards_to_be_played, int cards_left_to_be_played, int time_replayed)
{
   _type = stock_type; //I suppose, this should
   _total_cards = total_cards_to_be_played;
   _cards_left = cards_left_to_be_played;
   _time_replayed = time_replayed;
   //stock initialized;

}


int Game_Card_Stock::type() const
{
    return _type;
}


void Game_Card_Stock::setType(int type)
{
    _type = type;
}


GameCard::GameCard() { }


GameCard::GameCard(int card_ID, QString picture_address, QString card_name, cardAddon card_Addon)
{
    _card_ID = card_ID;
    _card_Picture_address = picture_address;
    _card_Name = card_name;
    _cardAddOn = card_Addon;
}


int GameCard::card_ID() const
{
    return _card_ID;
}


void GameCard::setCard_ID(int card_ID)
{
    _card_ID = card_ID;
}


QString GameCard::card_Picture_address() const
{
    return _card_Picture_address;
}


void GameCard::setCard_Picture_address(const QString &card_Picture_address)
{
    _card_Picture_address = card_Picture_address;
}


QString GameCard::card_Name() const
{
    return _card_Name;
}


void GameCard::setCard_Name(const QString &card_Name)
{
    _card_Name = card_Name;
}


cardAddon GameCard::cardAddOn() const
{
    return _cardAddOn;
}


void GameCard::setCardAddOn(const cardAddon &cardAddOn)
{
    _cardAddOn = cardAddOn;
}


QString gameCardDoorMonster::pictureAddress() const
{
    return _pictureAddress;
}


void gameCardDoorMonster::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardDoorMonster::cardName() const
{
    return _cardName;
}


void gameCardDoorMonster::setCardName(const QString &cardName)
{
    _cardName = cardName;
}


QString gameCardDoorMonster::monsterName() const
{
    return _monsterName;
}


void gameCardDoorMonster::setMonsterName(const QString &monsterName)
{
    _monsterName = monsterName;
}


cardAddon gameCardDoorMonster::addOn() const
{
    return _addOn;
}


void gameCardDoorMonster::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}


doorType gameCardDoorMonster::type() const
{
    return _type;
}


void gameCardDoorMonster::setType(const doorType &type)
{
    _type = type;
}

bool gameCardDoorMonster::isUndead() const
{
    return _isUndead;
}


void gameCardDoorMonster::setIsUndead(bool isUndead)
{
    _isUndead = isUndead;
}


bool gameCardDoorMonster::fromHell() const
{
    return _fromHell;
}

void gameCardDoorMonster::setFromHell(bool fromHell)
{
    _fromHell = fromHell;
}


int gameCardDoorMonster::monsterLevel() const
{
    return _monsterLevel;
}


void gameCardDoorMonster::setMonsterLevel(int monsterLevel)
{
    _monsterLevel = monsterLevel;
}


int gameCardDoorMonster::strongAgainstHuman() const
{
    return _strongAgainstHuman;
}


void gameCardDoorMonster::setStrongAgainstHuman(int strongAgainstHuman)
{
    _strongAgainstHuman = strongAgainstHuman;
}


int gameCardDoorMonster::strongAgainstElf() const
{
    return _strongAgainstElf;
}


void gameCardDoorMonster::setStrongAgainstElf(int strongAgainstElf)
{
    _strongAgainstElf = strongAgainstElf;
}


int gameCardDoorMonster::strongAgainstHalfling() const
{
    return _strongAgainstHalfling;
}


void gameCardDoorMonster::setStrongAgainstHalfling(int strongAgainstHalfling)
{
    _strongAgainstHalfling = strongAgainstHalfling;
}


int gameCardDoorMonster::strongAgainstDwarf() const
{
    return _strongAgainstDwarf;
}


void gameCardDoorMonster::setStrongAgainstDwarf(int strongAgainstDwarf)
{
    _strongAgainstDwarf = strongAgainstDwarf;
}


int gameCardDoorMonster::strongAgainstOrk() const
{
    return _strongAgainstOrk;
}


void gameCardDoorMonster::setStrongAgainstOrk(int strongAgainstOrk)
{
    _strongAgainstOrk = strongAgainstOrk;
}


int gameCardDoorMonster::strongAgainstGnome() const
{
    return _strongAgainstGnome;
}


void gameCardDoorMonster::setStrongAgainstGnome(int strongAgainstGnome)
{
    _strongAgainstGnome = strongAgainstGnome;
}


int gameCardDoorMonster::strongAgainstNoClass() const
{
    return _strongAgainstNoClass;
}


void gameCardDoorMonster::setStrongAgainstNoClass(int strongAgainstNoClass)
{
    _strongAgainstNoClass = strongAgainstNoClass;
}


int gameCardDoorMonster::strongAgainstHalfBreed() const
{
    return _strongAgainstHalfBreed;
}


void gameCardDoorMonster::setStrongAgainstHalfBreed(int strongAgainstHalfBreed)
{
    _strongAgainstHalfBreed = strongAgainstHalfBreed;
}


int gameCardDoorMonster::strongAgainstSuperMunchkin() const
{
    return _strongAgainstSuperMunchkin;
}


void gameCardDoorMonster::setStrongAgainstSuperMunchkin(int strongAgainstSuperMunchkin)
{
    _strongAgainstSuperMunchkin = strongAgainstSuperMunchkin;
}


int gameCardDoorMonster::strongAgainstWoman() const
{
    return _strongAgainstWoman;
}


void gameCardDoorMonster::setStrongAgainstWoman(int strongAgainstWoman)
{
    _strongAgainstWoman = strongAgainstWoman;
}


int gameCardDoorMonster::strongAgainstWarrior() const
{
    return _strongAgainstWarrior;
}


void gameCardDoorMonster::setStrongAgainstWarrior(int strongAgainstWarrior)
{
    _strongAgainstWarrior = strongAgainstWarrior;
}


int gameCardDoorMonster::strongAgainstWizard() const
{
    return _strongAgainstWizard;
}


void gameCardDoorMonster::setStrongAgainstWizard(int strongAgainstWizard)
{
    _strongAgainstWizard = strongAgainstWizard;
}


int gameCardDoorMonster::strongAgainstThief() const
{
    return _strongAgainstThief;
}


void gameCardDoorMonster::setStrongAgainstThief(int strongAgainstThief)
{
    _strongAgainstThief = strongAgainstThief;
}


int gameCardDoorMonster::strongAgainstBard() const
{
    return _strongAgainstBard;
}


void gameCardDoorMonster::setStrongAgainstBard(int strongAgainstBard)
{
    _strongAgainstBard = strongAgainstBard;
}


int gameCardDoorMonster::strongAgainstCleric() const
{
    return _strongAgainstCleric;
}


void gameCardDoorMonster::setStrongAgainstCleric(int strongAgainstCleric)
{
    _strongAgainstCleric = strongAgainstCleric;
}


int gameCardDoorMonster::strongAgainstSaturday() const
{
    return _strongAgainstSaturday;
}


void gameCardDoorMonster::setStrongAgainstSaturday(int strongAgainstSaturday)
{
    _strongAgainstSaturday = strongAgainstSaturday;
}


bool gameCardDoorMonster::dontFightWithWoman() const
{
    return _dontFightWithWoman;
}


void gameCardDoorMonster::setDontFightWithWoman(bool dontFightWithWoman)
{
    _dontFightWithWoman = dontFightWithWoman;
}


bool gameCardDoorMonster::dontFightWithThief() const
{
    return _dontFightWithThief;
}


void gameCardDoorMonster::setDontFightWithThief(bool dontFightWithThief)
{
    _dontFightWithThief = dontFightWithThief;
}


bool gameCardDoorMonster::dontFightWithElf() const
{
    return _dontFightWithElf;
}

void gameCardDoorMonster::setDontFightWithElf(bool dontFightWithElf)
{
    _dontFightWithElf = dontFightWithElf;
}


bool gameCardDoorMonster::dontFightwithOrk() const
{
    return _dontFightwithOrk;
}


void gameCardDoorMonster::setDontFightwithOrk(bool dontFightwithOrk)
{
    _dontFightwithOrk = dontFightwithOrk;
}


int gameCardDoorMonster::dontFightTillLevel() const
{
    return _dontFightTillLevel;
}


void gameCardDoorMonster::setDontFightTillLevel(int dontFightTillLevel)
{
    _dontFightTillLevel = dontFightTillLevel;
}


bool gameCardDoorMonster::specialMechanicAgainstAll() const
{
    return _specialMechanicAgainstAll;
}


void gameCardDoorMonster::setSpecialMechanicAgainstAll(bool specialMechanicAgainstAll)
{
    _specialMechanicAgainstAll = specialMechanicAgainstAll;
}


bool gameCardDoorMonster::specialMechanicAgainstWoman() const
{
    return _specialMechanicAgainstWoman;
}


void gameCardDoorMonster::setSpecialMechanicAgainstWoman(bool specialMechanicAgainstWoman)
{
    _specialMechanicAgainstWoman = specialMechanicAgainstWoman;
}


bool gameCardDoorMonster::specialMechanicAgainstCleric() const
{
    return _specialMechanicAgainstCleric;
}


void gameCardDoorMonster::setSpecialMechanicAgainstCleric(bool specialMechanicAgainstCleric)
{
    _specialMechanicAgainstCleric = specialMechanicAgainstCleric;
}


bool gameCardDoorMonster::specialMechanicAginstThief() const
{
    return _specialMechanicAginstThief;
}


void gameCardDoorMonster::setSpecialMechanicAginstThief(bool specialMechanicAginstThief)
{
    _specialMechanicAginstThief = specialMechanicAginstThief;
}


bool gameCardDoorMonster::specialMechanicAgainstElf() const
{
    return _specialMechanicAgainstElf;
}


void gameCardDoorMonster::setSpecialMechanicAgainstElf(bool specialMechanicAgainstElf)
{
    _specialMechanicAgainstElf = specialMechanicAgainstElf;
}


bool gameCardDoorMonster::specialMechanicAgainstWizard() const
{
    return _specialMechanicAgainstWizard;
}


void gameCardDoorMonster::setSpecialMechanicAgainstWizard(bool specialMechanicAgainstWizard)
{
    _specialMechanicAgainstWizard = specialMechanicAgainstWizard;
}


bool gameCardDoorMonster::specialMechanicAgainstHalfling() const
{
    return _specialMechanicAgainstHalfling;
}


void gameCardDoorMonster::setSpecialMechanicAgainstHalfling(bool specialMechanicAgainstHalfling)
{
    _specialMechanicAgainstHalfling = specialMechanicAgainstHalfling;
}


int gameCardDoorMonster::cardID() const
{
    return _cardID;
}


void gameCardDoorMonster::setCardID(int cardID)
{
    _cardID = cardID;
}


QString gameCardDoorAmplifier::pictureAddress() const
{
    return _pictureAddress;
}


void gameCardDoorAmplifier::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardDoorAmplifier::cardName() const
{
    return _cardName;
}

void gameCardDoorAmplifier::setCardName(const QString &cardName)
{
    _cardName = cardName;
}



cardAddon gameCardDoorAmplifier::addOn() const
{
    return _addOn;
}

void gameCardDoorAmplifier::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

doorType gameCardDoorAmplifier::type() const
{
    return _type;
}

void gameCardDoorAmplifier::setType(const doorType &type)
{
    _type = type;
}


bool gameCardDoorAmplifier::isSleeping() const
{
    return _isSleeping;
}

void gameCardDoorAmplifier::setIsSleeping(bool isSleeping)
{
    _isSleeping = isSleeping;
}

bool gameCardDoorAmplifier::isEnraged() const
{
    return _isEnraged;
}

void gameCardDoorAmplifier::setIsEnraged(bool isAngry)
{
    _isEnraged = isAngry;
}

bool gameCardDoorAmplifier::isAncient() const
{
    return _isAncient;
}

void gameCardDoorAmplifier::setIsAncient(bool isOld)
{
    _isAncient = isOld;
}

bool gameCardDoorAmplifier::isBaby() const
{
    return _isBaby;
}

void gameCardDoorAmplifier::setIsBaby(bool isYoung)
{
    _isBaby = isYoung;
}

bool gameCardDoorAmplifier::isUndead() const
{
    return _isUndead;
}

void gameCardDoorAmplifier::setIsUndead(bool isUndead)
{
    _isUndead = isUndead;
}

bool gameCardDoorAmplifier::isFromHell() const
{
    return _isFromHell;
}

void gameCardDoorAmplifier::setIsFromHell(bool isFromHell)
{
    _isFromHell = isFromHell;
}

int gameCardDoorAmplifier::getAmplification() const
{
    return amplification;
}

void gameCardDoorAmplifier::setAmplification(int value)
{
    amplification = value;
}

int gameCardDoorAmplifier::getAdditionalTreasures() const
{
    return additionalTreasures;
}

void gameCardDoorAmplifier::setAdditionalTreasures(int value)
{
    additionalTreasures = value;
}



bool gameCardDoorAmplifier::getIsVeryDepressed() const
{
    return _isVeryDepressed;
}

void gameCardDoorAmplifier::setIsVeryDepressed(bool isVeryDepressed)
{
    _isVeryDepressed = isVeryDepressed;
}

int gameCardDoorAmplifier::cardID() const
{
    return _cardID;
}

void gameCardDoorAmplifier::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardDoorCurse::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardDoorCurse::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardDoorCurse::cardName() const
{
    return _cardName;
}

void gameCardDoorCurse::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardDoorCurse::addOn() const
{
    return _addOn;
}

void gameCardDoorCurse::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

doorType gameCardDoorCurse::type() const
{
    return _type;
}

void gameCardDoorCurse::setType(const doorType &type)
{
    _type = type;
}

int gameCardDoorCurse::getCurseMechanicID() const
{
    return _curseMechanicID;
}

void gameCardDoorCurse::setCurseMechanicID(int value)
{
    _curseMechanicID = value;
}

QString gameCardDoorCurse::getMechanic() const
{
    return _mechanic;
}

void gameCardDoorCurse::setMechanic(const QString &mechanic)
{
    _mechanic = mechanic;
}

int gameCardDoorCurse::cardID() const
{
    return _cardID;
}

void gameCardDoorCurse::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardDoorProfession::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardDoorProfession::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardDoorProfession::cardName() const
{
    return _cardName;
}

void gameCardDoorProfession::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardDoorProfession::addOn() const
{
    return _addOn;
}

doorType gameCardDoorProfession::type() const
{
    return _type;
}

void gameCardDoorProfession::setType(const doorType &type)
{
    _type = type;
}

Profession gameCardDoorProfession::profession() const
{
    return _profession;
}

void gameCardDoorProfession::setProfession(const Profession &profession)
{
    _profession = profession;
}

void gameCardDoorProfession::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

int gameCardDoorProfession::cardID() const
{
    return _cardID;
}

void gameCardDoorProfession::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardDoorRace::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardDoorRace::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardDoorRace::cardName() const
{
    return _cardName;
}

void gameCardDoorRace::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardDoorRace::addOn() const
{
    return _addOn;
}

void gameCardDoorRace::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

doorType gameCardDoorRace::type() const
{
    return _type;
}

void gameCardDoorRace::setType(const doorType &type)
{
    _type = type;
}

Race gameCardDoorRace::race() const
{
    return _race;
}

void gameCardDoorRace::setRace(const Race &race)
{
    _race = race;
}

int gameCardDoorRace::cardID() const
{
    return _cardID;
}

void gameCardDoorRace::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardDoorSpecialMechanic::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardDoorSpecialMechanic::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardDoorSpecialMechanic::cardName() const
{
    return _cardName;
}

void gameCardDoorSpecialMechanic::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardDoorSpecialMechanic::addOn() const
{
    return _addOn;
}

void gameCardDoorSpecialMechanic::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

doorType gameCardDoorSpecialMechanic::type() const
{
    return _type;
}

void gameCardDoorSpecialMechanic::setType(const doorType &type)
{
    _type = type;
}

int gameCardDoorSpecialMechanic::specialFunctionId() const
{
    return _specialFunctionId;
}

void gameCardDoorSpecialMechanic::setSpecialFunctionId(int specialFunctionId)
{
    _specialFunctionId = specialFunctionId;
}

int gameCardDoorSpecialMechanic::cardID() const
{
    return _cardID;
}

void gameCardDoorSpecialMechanic::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureArmor::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureArmor::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureArmor::cardName() const
{
    return _cardName;
}

void gameCardTreasureArmor::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureArmor::addOn() const
{
    return _addOn;
}

void gameCardTreasureArmor::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureArmor::type() const
{
    return _type;
}

void gameCardTreasureArmor::setType(const treasureType &type)
{
    _type = type;
}

Body_Part gameCardTreasureArmor::GetBodyPart() const
{
    return _part;
}

void gameCardTreasureArmor::setPart(const Body_Part &part)
{
    _part = part;
}

Size gameCardTreasureArmor::size() const
{
    return _size;
}

void gameCardTreasureArmor::setSize(const Size &size)
{
    _size = size;
}

int gameCardTreasureArmor::GetBonus() const
{
    return _bonus;
}

void gameCardTreasureArmor::setBonus(int bonus)
{
    _bonus = bonus;
}

int gameCardTreasureArmor::GetAdditionalBonusforElf() const
{
    return _additionalBonusforElf;
}

void gameCardTreasureArmor::SetAdditionalBonusforElf(int additionalBonusforElf)
{
    _additionalBonusforElf = additionalBonusforElf;
}

int gameCardTreasureArmor::GetAdditionalBonusforOrk() const
{
    return _additionalBonusforOrk;
}

void gameCardTreasureArmor::SetAdditionalBonusforOrk(int additionalBonusforOrk)
{
    _additionalBonusforOrk = additionalBonusforOrk;
}

bool gameCardTreasureArmor::isOnlyForHuman() const
{
    return _isOnlyForHuman;
}

void gameCardTreasureArmor::setIsOnlyForHuman(bool isOnlyForHuman)
{
    _isOnlyForHuman = isOnlyForHuman;
}

bool gameCardTreasureArmor::isOnlyForWizard() const
{
    return _isOnlyForWizard;
}

void gameCardTreasureArmor::setIsOnlyForWizard(bool isOnlyForWizard)
{
    _isOnlyForWizard = isOnlyForWizard;
}

bool gameCardTreasureArmor::isOnlyForDwarf() const
{
    return _isOnlyForDwarf;
}

void gameCardTreasureArmor::setIsOnlyForDwarf(bool isOnlyForDwarf)
{
    _isOnlyForDwarf = isOnlyForDwarf;
}

bool gameCardTreasureArmor::isOnlyForGnome() const
{
    return _isOnlyForGnome;
}

void gameCardTreasureArmor::setIsOnlyForGnome(bool isOnlyForGnome)
{
    _isOnlyForGnome = isOnlyForGnome;
}

bool gameCardTreasureArmor::isRestrictedToWizard() const
{
    return _isRestrictedToWizard;
}

void gameCardTreasureArmor::setIsRestrictedToWizard(bool isRestrictedToWizard)
{
    _isRestrictedToWizard = isRestrictedToWizard;
}

bool gameCardTreasureArmor::isRestrictedToGnome() const
{
    return _isRestrictedToGnome;
}

void gameCardTreasureArmor::setIsRestrictedToGnome(bool isRestrictedToGnome)
{
    _isRestrictedToGnome = isRestrictedToGnome;
}

bool gameCardTreasureArmor::hasSpecialMechanic() const
{
    return _hasSpecialMechanic;
}

void gameCardTreasureArmor::setHasSpecialMechanic(bool hasSpecialMechanic)
{
    _hasSpecialMechanic = hasSpecialMechanic;
}

int gameCardTreasureArmor::price() const
{
    return _price;
}

void gameCardTreasureArmor::setPrice(int price)
{
    _price = price;
}

int gameCardTreasureArmor::bonusToFleeing() const
{
    return _bonusToFleeing;
}

void gameCardTreasureArmor::setBonusToFleeing(int bonusToFleeing)
{
    _bonusToFleeing = bonusToFleeing;
}

bool gameCardTreasureArmor::isCombined() const
{
    return _isCombined;
}

void gameCardTreasureArmor::setIsCombined(bool isCombined)
{
    _isCombined = isCombined;
}

gameCardTreasureArmor::gameCardTreasureArmor(const gameCardTreasureArmor *ptr)
{
    _cardID = ptr->GetCardID();
    _pictureAddress = ptr->pictureAddress();
    _cardName = ptr->cardName();
    _addOn = ptr->addOn();
    _type = ptr->type();

    _part = ptr->GetBodyPart();
    _size = ptr->size();

    _bonus = ptr->GetBonus();
    _additionalBonusforElf = ptr->GetAdditionalBonusforElf();
    _additionalBonusforOrk = ptr->GetAdditionalBonusforOrk();

    _isOnlyForHuman = ptr->isOnlyForHuman();
    _isOnlyForWizard = ptr->isOnlyForWizard();
    _isOnlyForDwarf = ptr->isOnlyForDwarf();
    _isOnlyForGnome = ptr->isOnlyForGnome();

    _isRestrictedToWizard = ptr->isRestrictedToWizard();
    _isRestrictedToGnome = ptr->isRestrictedToGnome();

    _hasSpecialMechanic = ptr->hasSpecialMechanic();

    _price = ptr->price();

    _bonusToFleeing = ptr->bonusToFleeing();

    _isCombined = ptr->isCombined();
}

gameCardTreasureArmor::gameCardTreasureArmor(const gameCardTreasureArmor& other)
{
    SetCardType(other.GetCardType());

    _cardID = other.GetCardID();
    _pictureAddress = other.pictureAddress();
    _cardName = other.cardName();
    _addOn = other.addOn();
    _type = other.type();

    _part = other.GetBodyPart();
    _size = other.size();

    _bonus = other.GetBonus();
    _additionalBonusforElf = other.GetAdditionalBonusforElf();
    _additionalBonusforOrk = other.GetAdditionalBonusforOrk();

    _isOnlyForHuman = other.isOnlyForHuman();
    _isOnlyForWizard = other.isOnlyForWizard();
    _isOnlyForDwarf = other.isOnlyForDwarf();
    _isOnlyForGnome = other.isOnlyForGnome();

    _isRestrictedToWizard = other.isRestrictedToWizard();
    _isRestrictedToGnome = other.isRestrictedToGnome();

    _hasSpecialMechanic = other.hasSpecialMechanic();

    _price = other.price();

    _bonusToFleeing = other.bonusToFleeing();

    _isCombined = other.isCombined();
}

int gameCardTreasureArmor::GetCardID() const
{
    return _cardID;
}

void gameCardTreasureArmor::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureArmorAmplifier::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureArmorAmplifier::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureArmorAmplifier::cardName() const
{
    return _cardName;
}

void gameCardTreasureArmorAmplifier::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureArmorAmplifier::addOn() const
{
    return _addOn;
}

void gameCardTreasureArmorAmplifier::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureArmorAmplifier::type() const
{
    return _type;
}

void gameCardTreasureArmorAmplifier::setType(const treasureType &type)
{
    _type = type;
}

int gameCardTreasureArmorAmplifier::bonus() const
{
    return _bonus;
}

void gameCardTreasureArmorAmplifier::setBonus(int bonus)
{
    _bonus = bonus;
}

int gameCardTreasureArmorAmplifier::cardID() const
{
    return _cardID;
}

void gameCardTreasureArmorAmplifier::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureBattleAmplifier::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureBattleAmplifier::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureBattleAmplifier::cardName() const
{
    return _cardName;
}

void gameCardTreasureBattleAmplifier::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureBattleAmplifier::addOn() const
{
    return _addOn;
}

void gameCardTreasureBattleAmplifier::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureBattleAmplifier::type() const
{
    return _type;
}

void gameCardTreasureBattleAmplifier::setType(const treasureType &type)
{
    _type = type;
}

int gameCardTreasureBattleAmplifier::bonus() const
{
    return _bonus;
}

void gameCardTreasureBattleAmplifier::setBonus(int bonus)
{
    _bonus = bonus;
}

bool gameCardTreasureBattleAmplifier::isPotion() const
{
    return _isPotion;
}

void gameCardTreasureBattleAmplifier::setIsPotion(bool isPotion)
{
    _isPotion = isPotion;
}

bool gameCardTreasureBattleAmplifier::hasSpecialMechanic() const
{
    return _hasSpecialMechanic;
}

void gameCardTreasureBattleAmplifier::setHasSpecialMechanic(bool hasSpecialMechanic)
{
    _hasSpecialMechanic = hasSpecialMechanic;
}

uint32_t gameCardTreasureBattleAmplifier::price() const
{
    return _price;
}

void gameCardTreasureBattleAmplifier::setPrice(const uint32_t &price)
{
    _price = price;
}

int gameCardTreasureBattleAmplifier::cardID() const
{
    return _cardID;
}

void gameCardTreasureBattleAmplifier::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureLevelUp::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureLevelUp::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureLevelUp::cardName() const
{
    return _cardName;
}

void gameCardTreasureLevelUp::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureLevelUp::addOn() const
{
    return _addOn;
}

void gameCardTreasureLevelUp::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureLevelUp::type() const
{
    return _type;
}

void gameCardTreasureLevelUp::setType(const treasureType &type)
{
    _type = type;
}

bool gameCardTreasureLevelUp::hasSpecialMechanic() const
{
    return _hasSpecialMechanic;
}

void gameCardTreasureLevelUp::setHasSpecialMechanic(bool specialMechanic)
{
    _hasSpecialMechanic = specialMechanic;
}

int gameCardTreasureLevelUp::cardID() const
{
    return _cardID;
}

void gameCardTreasureLevelUp::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureSpecialMechanic::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureSpecialMechanic::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureSpecialMechanic::cardName() const
{
    return _cardName;
}

void gameCardTreasureSpecialMechanic::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureSpecialMechanic::addOn() const
{
    return _addOn;
}

void gameCardTreasureSpecialMechanic::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureSpecialMechanic::type() const
{
    return _type;
}

void gameCardTreasureSpecialMechanic::setType(const treasureType &type)
{
    _type = type;
}

int gameCardTreasureSpecialMechanic::price() const
{
    return _price;
}

void gameCardTreasureSpecialMechanic::setPrice(int price)
{
    _price = price;
}

bool gameCardTreasureSpecialMechanic::isPotion() const
{
    return _isPotion;
}

void gameCardTreasureSpecialMechanic::setIsPotion(bool isPotion)
{
    _isPotion = isPotion;
}

Time_To_Use gameCardTreasureSpecialMechanic::timeToUse() const
{
    return _timeToUse;
}

void gameCardTreasureSpecialMechanic::setTimeToUse(const Time_To_Use &timeToUse)
{
    _timeToUse = timeToUse;
}

Additional_Request gameCardTreasureSpecialMechanic::additionalRequest() const
{
    return _additionalRequest;
}

void gameCardTreasureSpecialMechanic::setAdditionalRequest(const Additional_Request &additionalRequest)
{
    _additionalRequest = additionalRequest;
}

int gameCardTreasureSpecialMechanic::cardID() const
{
    return _cardID;
}

void gameCardTreasureSpecialMechanic::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureThingsAmplifiers::pictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureThingsAmplifiers::setPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureThingsAmplifiers::cardName() const
{
    return _cardName;
}

void gameCardTreasureThingsAmplifiers::setCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureThingsAmplifiers::addOn() const
{
    return _addOn;
}

void gameCardTreasureThingsAmplifiers::setAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureThingsAmplifiers::type() const
{
    return _type;
}

void gameCardTreasureThingsAmplifiers::setType(const treasureType &type)
{
    _type = type;
}

Size gameCardTreasureThingsAmplifiers::size() const
{
    return _size;
}

void gameCardTreasureThingsAmplifiers::setSize(const Size &size)
{
    _size = size;
}

int gameCardTreasureThingsAmplifiers::bonus() const
{
    return _bonus;
}

void gameCardTreasureThingsAmplifiers::setBonus(int bonus)
{
    _bonus = bonus;
}

bool gameCardTreasureThingsAmplifiers::hasSpecialMechanic() const
{
    return _hasSpecialMechanic;
}

void gameCardTreasureThingsAmplifiers::setHasSpecialMechanic(bool hasSpecialMechanic)
{
    _hasSpecialMechanic = hasSpecialMechanic;
}

bool gameCardTreasureThingsAmplifiers::isKnees() const
{
    return _isKnees;
}

void gameCardTreasureThingsAmplifiers::setIsKnees(bool isKnees)
{
    _isKnees = isKnees;
}

bool gameCardTreasureThingsAmplifiers::isOnlyForHalfling() const
{
    return _isOnlyForHalfling;
}

void gameCardTreasureThingsAmplifiers::setIsOnlyForHalfling(bool isOnlyForHalfling)
{
    _isOnlyForHalfling = isOnlyForHalfling;
}

bool gameCardTreasureThingsAmplifiers::isOnlyForThief() const
{
    return _isOnlyForThief;
}

void gameCardTreasureThingsAmplifiers::setIsOnlyForThief(bool isOnlyForThief)
{
    _isOnlyForThief = isOnlyForThief;
}

bool gameCardTreasureThingsAmplifiers::isOnlyForCleric() const
{
    return _isOnlyForCleric;
}

void gameCardTreasureThingsAmplifiers::setIsOnlyForCleric(bool isOnlyForCleric)
{
    _isOnlyForCleric = isOnlyForCleric;
}

bool gameCardTreasureThingsAmplifiers::isOnlyForWizard() const
{
    return _isOnlyForWizard;
}

void gameCardTreasureThingsAmplifiers::setIsOnlyForWizard(bool isOnlyForWizard)
{
    _isOnlyForWizard = isOnlyForWizard;
}

bool gameCardTreasureThingsAmplifiers::isRestrictedToWarrior() const
{
    return _isRestrictedToWarrior;
}

void gameCardTreasureThingsAmplifiers::setIsRestrictedToWarrior(bool isRestrictedToWarrior)
{
    _isRestrictedToWarrior = isRestrictedToWarrior;
}

bool gameCardTreasureThingsAmplifiers::isRestrictedToCleric() const
{
    return _isRestrictedToCleric;
}

void gameCardTreasureThingsAmplifiers::setIsRestrictedToCleric(bool isRestrictedToCleric)
{
    _isRestrictedToCleric = isRestrictedToCleric;
}

bool gameCardTreasureThingsAmplifiers::isRestrictedToThief() const
{
    return _isRestrictedToThief;
}

void gameCardTreasureThingsAmplifiers::setIsRestrictedToThief(bool isRestrictedToThief)
{
    _isRestrictedToThief = isRestrictedToThief;
}

int gameCardTreasureThingsAmplifiers::price() const
{
    return _price;
}

void gameCardTreasureThingsAmplifiers::setPrice(int price)
{
    _price = price;
}

int gameCardTreasureThingsAmplifiers::bonusToFlee() const
{
    return _bonusToFlee;
}

void gameCardTreasureThingsAmplifiers::setBonusToFlee(int bonusToFlee)
{
    _bonusToFlee = bonusToFlee;
}

int gameCardTreasureThingsAmplifiers::bonusToHands() const
{
    return _bonusToHands;
}

void gameCardTreasureThingsAmplifiers::setBonusToHands(int bonusToHands)
{
    _bonusToHands = bonusToHands;
}

int gameCardTreasureThingsAmplifiers::bonusToMan() const
{
    return _bonusToMan;
}

void gameCardTreasureThingsAmplifiers::setBonusToMan(int bonusToMan)
{
    _bonusToMan = bonusToMan;
}

int gameCardTreasureThingsAmplifiers::bonusToWoman() const
{
    return _bonusToWoman;
}

void gameCardTreasureThingsAmplifiers::setBonusToWoman(int bonusToWoman)
{
    _bonusToWoman = bonusToWoman;
}

bool gameCardTreasureThingsAmplifiers::allowedToWearDwarven() const
{
    return _allowedToWearDwarven;
}

void gameCardTreasureThingsAmplifiers::setAllowedToWearDwarven(bool allowedToWearDwarven)
{
    _allowedToWearDwarven = allowedToWearDwarven;
}

bool gameCardTreasureThingsAmplifiers::allowedToWearElven() const
{
    return _allowedToWearElven;
}

void gameCardTreasureThingsAmplifiers::setAllowedToWearElven(bool allowedToWearElven)
{
    _allowedToWearElven = allowedToWearElven;
}

int gameCardTreasureThingsAmplifiers::cardID() const
{
    return _cardID;
}

void gameCardTreasureThingsAmplifiers::setCardID(int cardID)
{
    _cardID = cardID;
}

QString gameCardTreasureWeapon::GetPictureAddress() const
{
    return _pictureAddress;
}

void gameCardTreasureWeapon::SetPictureAddress(const QString &pictureAddress)
{
    _pictureAddress = pictureAddress;
}

QString gameCardTreasureWeapon::CardName() const
{
    return _cardName;
}

void gameCardTreasureWeapon::SetCardName(const QString &cardName)
{
    _cardName = cardName;
}

cardAddon gameCardTreasureWeapon::GetAddOn() const
{
    return _addOn;
}

void gameCardTreasureWeapon::SetAddOn(const cardAddon &addOn)
{
    _addOn = addOn;
}

treasureType gameCardTreasureWeapon::GetType() const
{
    return _type;
}

void gameCardTreasureWeapon::SetType(const treasureType &type)
{
    _type = type;
}

uint32_t gameCardTreasureWeapon::GetNecessaryHands() const
{
    return _hands;
}

void gameCardTreasureWeapon::SetNecessaryHands(int hands)
{
    //Костыль. Я и так знаю, что это число должно быть неотрицательным.
    //И таблицы тоже составляю я. Если писать все эти проверки, Манчкин никогда не будет написан.
    _hands = static_cast<uint32_t>(hands);
}

int gameCardTreasureWeapon::GetBonus() const
{
    return _bonus;
}

void gameCardTreasureWeapon::SetBonus(int bonus)
{
    _bonus = bonus;
}

bool gameCardTreasureWeapon::isOnlyForElf() const
{
    return _isOnlyForElf;
}

void gameCardTreasureWeapon::SetIsOnlyForElf(bool isOnlyForElf)
{
    _isOnlyForElf = isOnlyForElf;
}

bool gameCardTreasureWeapon::isOnlyForMan() const
{
    return _isOnlyForMan;
}

void gameCardTreasureWeapon::SetIsOnlyForMan(bool isOnlyForMan)
{
    _isOnlyForMan = isOnlyForMan;
}

bool gameCardTreasureWeapon::isOnlyForDwarf() const
{
    return _isOnlyForDwarf;
}

void gameCardTreasureWeapon::SetIsOnlyForDwarf(bool isOnlyForDwarf)
{
    _isOnlyForDwarf = isOnlyForDwarf;
}

bool gameCardTreasureWeapon::isOnlyForHuman() const
{
    return _isOnlyForHuman;
}

void gameCardTreasureWeapon::SetIsOnlyForHuman(bool isOnlyForHuman)
{
    _isOnlyForHuman = isOnlyForHuman;
}

bool gameCardTreasureWeapon::isOnlyForWizard() const
{
    return _isOnlyForWizard;
}

void gameCardTreasureWeapon::SetIsOnlyForWizard(bool isOnlyForWizard)
{
    _isOnlyForWizard = isOnlyForWizard;
}

bool gameCardTreasureWeapon::isOnlyForWoman() const
{
    return _isOnlyForWoman;
}

void gameCardTreasureWeapon::SetIsOnlyForWoman(bool isOnlyForWoman)
{
    _isOnlyForWoman = isOnlyForWoman;
}

bool gameCardTreasureWeapon::isOnlyForWarrior() const
{
    return _isOnlyForWarrior;
}

void gameCardTreasureWeapon::SetIsOnlyForWarrior(bool isOnlyForWarrior)
{
    _isOnlyForWarrior = isOnlyForWarrior;
}

bool gameCardTreasureWeapon::isOnlyForOrk() const
{
    return _isOnlyForOrk;
}

void gameCardTreasureWeapon::SetIsOnlyForOrk(bool isOnlyForOrk)
{
    _isOnlyForOrk = isOnlyForOrk;
}

bool gameCardTreasureWeapon::isOnlyForThief() const
{
    return _isOnlyForThief;
}

void gameCardTreasureWeapon::SetIsOnlyForThief(bool isOnlyForThief)
{
    _isOnlyForThief = isOnlyForThief;
}

bool gameCardTreasureWeapon::isOnlyForHalfling() const
{
    return _isOnlyForHalfling;
}

void gameCardTreasureWeapon::SetIsOnlyForHalfling(bool isOnlyForHalfling)
{
    _isOnlyForHalfling = isOnlyForHalfling;
}

bool gameCardTreasureWeapon::isOnlyForGnome() const
{
    return _isOnlyForGnome;
}

void gameCardTreasureWeapon::SetIsOnlyForGnome(bool isOnlyForGnome)
{
    _isOnlyForGnome = isOnlyForGnome;
}

bool gameCardTreasureWeapon::isOnlyForBard() const
{
    return _isOnlyForBard;
}

void gameCardTreasureWeapon::SetIsOnlyForBard(bool isOnlyForBard)
{
    _isOnlyForBard = isOnlyForBard;
}

bool gameCardTreasureWeapon::GetHasSpecialMechanic() const
{
    return _hasSpecialMechanic;
}

void gameCardTreasureWeapon::SetHasSpecialMechanic(bool hasSpecialMechanic)
{
    _hasSpecialMechanic = hasSpecialMechanic;
}

int gameCardTreasureWeapon::GetPrice() const
{
    return _price;
}

void gameCardTreasureWeapon::SetPrice(int price)
{
    _price = price;
}

int gameCardTreasureWeapon::GetBonusToFlee() const
{
    return _bonusToFlee;
}

void gameCardTreasureWeapon::SetBonusToFlee(int bonusToFlee)
{
    _bonusToFlee = bonusToFlee;
}

uint32_t gameCardTreasureWeapon::GetAdditionalBonusAgainstUndead() const
{
    return _additionalBonusAgainstUndead;
}

void gameCardTreasureWeapon::SetAdditionalBonusAgainstUndead(uint32_t additionalBonusAgainstUndead)
{
    _additionalBonusAgainstUndead = additionalBonusAgainstUndead;
}

bool gameCardTreasureWeapon::GetAutomaticLooseToCalmadzila() const
{
    return _automaticLooseToCalmadzila;
}

void gameCardTreasureWeapon::SetAutomaticLooseToCalmadzila(bool automaticLooseToCalmadzila)
{
    _automaticLooseToCalmadzila = automaticLooseToCalmadzila;
}

uint32_t gameCardTreasureWeapon::GetAdditionalBonusAgainst_J() const
{
    return _additionalBonusAgainst_J;
}

void gameCardTreasureWeapon::SetAdditionalBonusAgainst_J(uint32_t additionalBonusAgainst_J)
{
    _additionalBonusAgainst_J = additionalBonusAgainst_J;
}

bool gameCardTreasureWeapon::AddingClericalAbility() const
{
    return _addingClericalAbility;
}

void gameCardTreasureWeapon::SetAddingClericalAbility(bool addingClericalAbility)
{
    _addingClericalAbility = addingClericalAbility;
}

bool gameCardTreasureWeapon::GetAddingThiefAbility() const
{
    return _addingThiefAbility;
}

void gameCardTreasureWeapon::SetAddingThiefAbility(bool addingThiefAbility)
{
    _addingThiefAbility = addingThiefAbility;
}

bool gameCardTreasureWeapon::isOnlyForCleric() const
{
    return _isOnlyForCleric;
}

void gameCardTreasureWeapon::SetIsOnlyForCleric(bool isOnlyForCleric)
{
    _isOnlyForCleric = isOnlyForCleric;
}

Size gameCardTreasureWeapon::GetSize() const
{
    return _size;
}

void gameCardTreasureWeapon::SetSize(const Size &size)
{
    _size = size;
}

gameCardTreasureWeapon::gameCardTreasureWeapon(const gameCardTreasureWeapon *ptr)
{
    _size = ptr->GetSize();
    _type = ptr->GetType();
    _addOn = ptr->GetAddOn();
    _bonus = ptr->GetBonus();
    _hands = ptr->GetNecessaryHands();
    _price = ptr->GetPrice();
    _cardID = ptr->GetCardID();
    _cardName = ptr->CardName();
    _bonusToFlee = ptr->GetBonusToFlee();

    _isOnlyForElf = ptr->isOnlyForElf();
    _isOnlyForMan = ptr->isOnlyForMan();
    _isOnlyForOrk = ptr->isOnlyForOrk();
    _isOnlyForBard = ptr->isOnlyForBard();
    _isOnlyForDwarf = ptr->isOnlyForDwarf();
    _isOnlyForGnome = ptr->isOnlyForGnome();
    _isOnlyForHuman = ptr->isOnlyForHuman();
    _isOnlyForThief = ptr->isOnlyForThief();
    _isOnlyForWoman = ptr->isOnlyForWoman();
    _isOnlyForCleric = ptr->isOnlyForCleric();
    _isOnlyForWizard = ptr->isOnlyForWizard();
    _isOnlyForWarrior = ptr->isOnlyForWarrior();
    _isOnlyForHalfling = ptr->isOnlyForHalfling();

    _pictureAddress = ptr->GetPictureAddress();
    _addingThiefAbility = ptr->GetAddingThiefAbility();
    _hasSpecialMechanic = ptr->GetHasSpecialMechanic();
    _addingClericalAbility = ptr->AddingClericalAbility();
    _additionalBonusAgainst_J = ptr->GetAdditionalBonusAgainst_J();
    _automaticLooseToCalmadzila = ptr->GetAutomaticLooseToCalmadzila();
    _additionalBonusAgainstUndead = ptr->GetAdditionalBonusAgainstUndead();
}

gameCardTreasureWeapon::gameCardTreasureWeapon(const gameCardTreasureWeapon &other)
{
    _size = other.GetSize();
    _type = other.GetType();
    _addOn = other.GetAddOn();
    _bonus = other.GetBonus();
    _hands = other.GetNecessaryHands();
    _price = other.GetPrice();
    _cardID = other.GetCardID();
    _cardName = other.CardName();
    _bonusToFlee = other.GetBonusToFlee();

    _isOnlyForElf = other.isOnlyForElf();
    _isOnlyForMan = other.isOnlyForMan();
    _isOnlyForOrk = other.isOnlyForOrk();
    _isOnlyForBard = other.isOnlyForBard();
    _isOnlyForDwarf = other.isOnlyForDwarf();
    _isOnlyForGnome = other.isOnlyForGnome();
    _isOnlyForHuman = other.isOnlyForHuman();
    _isOnlyForThief = other.isOnlyForThief();
    _isOnlyForWoman = other.isOnlyForWoman();
    _isOnlyForCleric = other.isOnlyForCleric();
    _isOnlyForWizard = other.isOnlyForWizard();
    _isOnlyForWarrior = other.isOnlyForWarrior();
    _isOnlyForHalfling = other.isOnlyForHalfling();

    _pictureAddress = other.GetPictureAddress();
    _addingThiefAbility = other.GetAddingThiefAbility();
    _hasSpecialMechanic = other.GetHasSpecialMechanic();
    _addingClericalAbility = other.AddingClericalAbility();
    _additionalBonusAgainst_J = other.GetAdditionalBonusAgainst_J();
    _automaticLooseToCalmadzila = other.GetAutomaticLooseToCalmadzila();
    _additionalBonusAgainstUndead = other.GetAdditionalBonusAgainstUndead();
}


int gameCardTreasureWeapon::GetCardID() const
{
    return _cardID;
}

void gameCardTreasureWeapon::SetCardID(int cardID)
{
    _cardID = cardID;
}

QDebug operator<<(QDebug debug, const SelectableCardMode& dt) {

    switch (dt) {
    case SelectableCardMode::DiplomacyTrade:
        debug << "DiplomacyTrade";
        break;
    case SelectableCardMode::HandAlignment:
        debug << "HandAlignment";
        break;
    case SelectableCardMode::Theft:
        debug << "Theft";
        break;
    case SelectableCardMode::SellMenu:
        debug << "SellMenu";
        break;
    }

    return debug;
}

QDebug operator<<(QDebug debug, const CardType& dt)
{
    switch (dt) {
    case CardType::DoorAmplifier:
        debug << "CardType::DoorAmplifier";
        break;
    case CardType::DoorCurse:
        debug << "CardType::DoorCurse";
        break;
    case CardType::DoorMonster:
        debug << "CardType::DoorMonster";
        break;
    case CardType::DoorProfession:
        debug << "CardType::DoorProfession";
        break;
    case CardType::DoorRace:
        debug << "CardType::DoorRace";
        break;
    case CardType::DoorSpecialMechanic:
        debug << "CardType::DoorSpecialMechanic";
        break;
    case CardType::TreasureArmor:
        debug << "CardType::TreasureArmor";
        break;
    case CardType::TreasureArmorAmplifier:
        debug << "CardType::TreasureArmorAmplifier";
        break;
    case CardType::TreasureBattleAmplifier:
        debug << "CardType::TreasureBattleAmplifier";
        break;
    case CardType::TreasureLevelUp:
        debug << "CardType::TreasureLevelUp";
        break;
    case CardType::TreasureSpecialMechanic:
        debug << "CardType::TreasureSpecialMechanic";
        break;
    case CardType::TreasureThingAmplifier:
        debug << "CardType::TreasureThingAmplifier";
        break;
    case CardType::TreasureWeapon:
        debug << "CardType::TreasureWeapon";
        break;
    case CardType::NotSupported:
        debug << "CardType::NotSupported";
        break;

    }

    return debug;
}


std::vector<SimpleCard> PositionedCard::RevertToSimpleCardsVector(const std::vector<PositionedCard> &cards)
{
    std::vector<SimpleCard> simpleCards;
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        simpleCards.push_back(cards[var].GetCard());
    }
    return simpleCards;
}

std::vector<PositionedCard> operator+(const std::vector<PositionedCard> &left, const std::vector<PositionedCard> &right)
{
    std::vector<PositionedCard> result = left;
    for (uint32_t var = 0; var < right.size(); ++var)
    {
        result.push_back(right[var]);
    }
    return result;
}

std::vector<SimpleCard> operator+(const std::vector<SimpleCard> &left, const std::vector<SimpleCard> &right)
{
    std::vector<SimpleCard> result = left;
    for (uint32_t var = 0; var < right.size(); ++var)
    {
        result.push_back(right[var]);
    }
    return result;
}

QDebug operator<<(QDebug debug, const CardImplementationDirection &dt)
{
    switch (dt)
    {
        case CardImplementationDirection::CardsInGameToBattlefield:
            debug << "CardImplementationDirection::CardsInGameToBattlefield";
            break;
        case CardImplementationDirection::HandToBattleField:
            debug << "CardImplementationDirection::HandToBattleField";
            break;
        case CardImplementationDirection::HandToCardsInGame:
            debug << "CardType::HandToCardsInGame";
            break;
    }

    return debug;
}
