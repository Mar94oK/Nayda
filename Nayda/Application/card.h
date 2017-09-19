#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QMap>
#include <map>


/*
 * There are .csv tables of all the cards.
 * The_Game receives from Before_The_Game stock type (calculated basing on the settings selected in a
 * specific Before_The_Game menu).
 * According to this stock type it fills up the basis maps of the cards. This will be needed to show cards
 * in the game.
 * At the same time the Server does the same job and also makes the vectors from initial maps
 * taking away cards from basis maps.
 * So the program-client will have basis maps of cards and small maps of the cards that player has.
 * It will be two maps: things_in_the_game, races_professions and one vector "cards_on_the_hands";
 * About the other players client-programm knows things_in_the_game, races_professions.
 * There are some mechanics, that show the other player's hands to another or all the players. But for the
 * main time they are unknown to the program-client. So the vector!!! "cards_on_the_hands" exisists, but is filled
 * with a specific card_type "rubashka". Client knows the quantity, but not the fullfilment.
 * "cards_on_the_hands" should be the vector, since the order might be important: there are mechanics, that allows
 * to take some cards from player. Might be a good idea to allow player to change cards in places from time to time.
 *
*/


enum class cardAddon {Basic, WildAxe, ClericalErrors };
enum class doorType {Monster, MonsterAmplifier, Curse, Race, Profession, SpecialMechanics };



#define DEFAULT_GAME_STOCK

//Depending on the game stock!!!!!

#ifdef DEFAULT_GAME_STOCK
//There will be five Races and five Classes (Here and Further Renamed to Professions) in the Basic Game
//Player can only have 4 abilities from Races and 4 abilities from Classes;
//Therefore there will be an array of each group;
//Passive abilities should have a special sign near Avatar, active abilities should have not only the sign,
//but also the button in the specific menu (the total of six buttons for Mage-Priest & Halfling-Ork for ex).
//There will be maximum of
// Race-Active-Abilities == 2
// Race-Passive-Abilities == 4
// Profession-Active-Abilities == 4
// Profession-Passive-Abilities == 2
//Therefore maximum of
// Passive_labels == 6
// Active_labels == 6 (will be made as buttons in a spec. menu)



enum class Race { Human, Elf, Dwarf, Gnome, Halfling, Ork };
enum class Profession {No_Profession, Warrior, Rogue, Priest, Bard, Mage}; //using "profession instead of class



enum class Race_Active_Abilities {No_Abilities, Power_of_the_Lonesome, The_Second_Chance, Rejecting};
enum class Race_Passive_Abilities {No_Abilities, Big_Guy, Big_Hands, Escaping, Semi_Altruism,
                                   Power_of_GN_Nose_Auto_Escape, Businessman, Overpower};

enum class Profession_Active_Abilities {No_Abilities,  Ressurection, Banishment, Theft, Shrinking, Berserking, Enchanting,
                             Flight, Pacification };
enum class Profession_Passive_Abilities {No_Abilities, Power_of_the_Parity, Bards_Luck };

enum class Abilities_Keys_Races {elven_ability_1, elven_ability_2, dwarfs_ability_1, dwarfs_ability_2,
                           gnomes_ability_1, gnomes_ability_2, halflings_ability_1, halflings_ability_2,
                           orks_ability_1, orks_ability_2 };
enum class Abilities_Keys_Professions {warriors_ability_1, warriors_ability_2, rogue_ability_1, rogue_ability_2,
                                      priests_ability_1, priests_ability_2, bards_ability_1, bards_ability_2,
                                      mage_ability_1, mage_ability_2};

enum class Players_Sex {Man, Woman};

enum class Card_Type {Monster, Monsters_Amplifier, Curse, Race, Profession, Special_Mechanics};



#endif





class Game_Card
{

public:
    Game_Card();
    Game_Card (int card_ID, QString picture_address, QString card_name, cardAddon card_Addon);

    int card_ID() const;
    void setCard_ID(int card_ID);

    QString card_Picture_address() const;
    void setCard_Picture_address(const QString &card_Picture_address);

    QString card_Name() const;
    void setCard_Name(const QString &card_Name);

    cardAddon cardAddOn() const;
    void setCardAddOn(const cardAddon &cardAddOn);

protected:

    int _card_ID;
    QString _card_Picture_address;
    QString _card_Name;
    cardAddon _cardAddOn;




};

class gameCardDoorMonster {

    int _cardID;
    QString _pictureAddress;
    QString _cardName;
    QString _monsterName;
    cardAddon _addOn;
    doorType _type;

    bool _isUndead;
    bool _fromHell;

    int _monsterLevel;

    int _strongAgainstHuman;
    int _strongAgainstElf;
    int _strongAgainstHalfling;
    int _strongAgainstDwarf;
    int _strongAgainstOrk;
    int _strongAgainstGnome;
    int _strongAgainstNoClass;
    int _strongAgainstHalfBreed;
    int _strongAgainstSuperMunchkin;
    int _strongAgainstWoman;
    int _strongAgainstWarrior;
    int _strongAgainstWizard;
    int _strongAgainstThief;
    int _strongAgainstBard;
    int _strongAgainstCleric;
    int _strongAgainstSaturday;

    bool _dontFightWithWoman;
    bool _dontFightWithThief;
    bool _dontFightWithElf;
    bool _dontFightwithOrk;

    int _dontFightTillLevel;

    bool _specialMechanicAgainstAll;
    bool _specialMechanicAgainstWoman;
    bool _specialMechanicAgainstCleric;
    bool _specialMechanicAginstThief;
    bool _specialMechanicAgainstElf;
    bool _specialMechanicAgainstWizard;
    bool _specialMechanicAgainstHalfling;


public:

    //I will try default constructor with no parameters;
    //The parameters will be filled up in the Parser;
    gameCardDoorMonster() {}

//    gameCardDoorMonster(int card_ID, QString picture_Address, QString card_Name,
//                        QString monster_Name, cardAddon card_Addon, doorType the_type,
//                        bool is_Undead, bool is_from_Hell, int monster_Level,
//                        int strong_AgainstHuman, int strong_AgainstElf,
//                        int strong_AgainstHalfling, int strong_Against);


    int cardID() const;
    void setCardID(int cardID);
    QString pictureAddress() const;
    void setPictureAddress(const QString &pictureAddress);
    QString cardName() const;
    void setCardName(const QString &cardName);
    QString monsterName() const;
    void setMonsterName(const QString &monsterName);
    cardAddon addOn() const;
    void setAddOn(const cardAddon &addOn);
    doorType type() const;
    void setType(const doorType &type);
    bool isUndead() const;
    void setIsUndead(bool isUndead);
    bool fromHell() const;
    void setFromHell(bool fromHell);
    int monsterLevel() const;
    void setMonsterLevel(int monsterLevel);
    int strongAgainstHuman() const;
    void setStrongAgainstHuman(int strongAgainstHuman);
    int strongAgainstElf() const;
    void setStrongAgainstElf(int strongAgainstElf);
    int strongAgainstHalfling() const;
    void setStrongAgainstHalfling(int strongAgainstHalfling);
    int strongAgainstDwarf() const;
    void setStrongAgainstDwarf(int strongAgainstDwarf);
    int strongAgainstOrk() const;
    void setStrongAgainstOrk(int strongAgainstOrk);
    int strongAgainstGnome() const;
    void setStrongAgainstGnome(int strongAgainstGnome);
    int strongAgainstNoClass() const;
    void setStrongAgainstNoClass(int strongAgainstNoClass);
    int strongAgainstHalfBreed() const;
    void setStrongAgainstHalfBreed(int strongAgainstHalfBreed);
    int strongAgainstSuperMunchkin() const;
    void setStrongAgainstSuperMunchkin(int strongAgainstSuperMunchkin);
    int strongAgainstWoman() const;
    void setStrongAgainstWoman(int strongAgainstWoman);
    int strongAgainstWarrior() const;
    void setStrongAgainstWarrior(int strongAgainstWarrior);
    int strongAgainstWizard() const;
    void setStrongAgainstWizard(int strongAgainstWizard);
    int strongAgainstThief() const;
    void setStrongAgainstThief(int strongAgainstThief);
    int strongAgainstBard() const;
    void setStrongAgainstBard(int strongAgainstBard);
    int strongAgainstCleric() const;
    void setStrongAgainstCleric(int strongAgainstCleric);
    int strongAgainstSaturday() const;
    void setStrongAgainstSaturday(int strongAgainstSaturday);
    bool dontFightWithWoman() const;
    void setDontFightWithWoman(bool dontFightWithWoman);
    bool dontFightWithThief() const;
    void setDontFightWithThief(bool dontFightWithThief);
    bool dontFightWithElf() const;
    void setDontFightWithElf(bool dontFightWithElf);
    bool dontFightwithOrk() const;
    void setDontFightwithOrk(bool dontFightwithOrk);
    int dontFightTillLevel() const;
    void setDontFightTillLevel(int dontFightTillLevel);
    bool specialMechanicAgainstAll() const;
    void setSpecialMechanicAgainstAll(bool specialMechanicAgainstAll);
    bool specialMechanicAgainstWoman() const;
    void setSpecialMechanicAgainstWoman(bool specialMechanicAgainstWoman);
    bool specialMechanicAgainstCleric() const;
    void setSpecialMechanicAgainstCleric(bool specialMechanicAgainstCleric);
    bool specialMechanicAginstThief() const;
    void setSpecialMechanicAginstThief(bool specialMechanicAginstThief);
    bool specialMechanicAgainstElf() const;
    void setSpecialMechanicAgainstElf(bool specialMechanicAgainstElf);
    bool specialMechanicAgainstWizard() const;
    void setSpecialMechanicAgainstWizard(bool specialMechanicAgainstWizard);
    bool specialMechanicAgainstHalfling() const;
    void setSpecialMechanicAgainstHalfling(bool specialMechanicAgainstHalfling);
};


class gameCardDoorAmplifier {

    int _cardID;
    QString _pictureAddress;
    QString _cardName;
    cardAddon _addOn;
    doorType _type;

    bool _isSleeping;
    bool _isEnraged;
    bool _isAncient;
    bool _isBaby;
    bool _isUndead;
    bool _isFromHell;
    bool _isVeryDepressed;

    int amplification;
    int additionalTreasures;



public:
    int cardID() const;
    void setCardID(int cardID);
    QString pictureAddress() const;
    void setPictureAddress(const QString &pictureAddress);
    QString cardName() const;
    void setCardName(const QString &cardName);
    QString monsterName() const;
    void setMonsterName(const QString &monsterName);
    cardAddon addOn() const;
    void setAddOn(const cardAddon &addOn);
    doorType type() const;
    void setType(const doorType &type);
    bool isSleeping() const;
    void setIsSleeping(bool isSleeping);
    bool isEnraged() const;
    void setIsEnraged(bool isEnraged);
    bool isAncient() const;
    void setIsAncient(bool isAncient);
    bool isBaby() const;
    void setIsBaby(bool isBaby);
    bool isUndead() const;
    void setIsUndead(bool isUndead);
    bool isFromHell() const;
    void setIsFromHell(bool isFromHell);
    int getAmplification() const;
    void setAmplification(int value);
    int getAdditionalTreasures() const;
    void setAdditionalTreasures(int value);

    bool getIsVeryDepressed() const;
    void setIsVeryDepressed(bool isVeryDepressed);
};

class Game_Card_Stock


{
public:
    Game_Card_Stock();
    Game_Card_Stock (int stock_type, int total_cards_to_be_played, int cards_left_to_be_played, int time_replayed);

  int type() const;
  void setType(int type);

private:

  int _type;  //make it as a specific type!
  int _total_cards; //how many card were in an initial stock
  int _cards_left; //how many cards left in a game;
  int _time_replayed; //how many times were the stock replayed (somekind of a debug info)

  std::vector<Game_Card> _stock;


};






#endif // CARD_H


