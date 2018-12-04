#include "Application/The_Game/The_Game.h"
#include "ui_the_game.h"
#include <ctime>
#include <QTime>
#include "popupcard.h"
#include "munchkinglobaldefines.h"

The_Game::The_Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::The_Game)
{
    ui->setupUi(this);

    InitializePopUpWidgets();
    SetUpBackgroundPicture();

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    uint32_t HW_Screen_Size_Width = HW_Screen_Size.width();
    uint32_t HW_Screen_Size_Heigh = HW_Screen_Size.height();

    //Regarding this note
    //https://stackoverflow.com/questions/44875309/why-does-qdesktopwidget-give-me-the-wrong-available-geometry-when-i-use-two-moni
    //It is necessary to adjust size while using Linux internally.
    //make it 0.8 of height for example

#ifdef __linux
//    static_cast<uint32_t>(HW_Screen_Size_Heigh *= 0.9);
//    static_cast<uint32_t>(HW_Screen_Size_Width *= 0.8);
#endif

    //1. SetUp Initial Signals-Slots connections
    SetUpSignalSlotsConnections();

    //2. GUI Adjustment
    SetUpWidgetsProperties(HW_Screen_Size_Heigh, HW_Screen_Size_Width);
    //SetUpPlayersAndWidgets(HW_Screen_Size_Heigh, HW_Screen_Size_Width);

    //3. Parse cards
    MainParser();

    // NAY-001: MARK_EXPECTED_IMPROVEMENT
    //Here I should implement selection of the selected cards by the user.
    //4. Pass cards to widgets to display


    //Алгоритм на будущее (когда настройки дополнений действительно будут работать)
    //Игра получает от Предыгры настройки
    //Далее далее каждый раз парсит их
    //В итоге на момент запуска Игры она уже знает все свои настройки
    //И на самом деле перерисована, следовательно запускается мгновенно
    //В данный момент времени Аддоны будут просто забиты цифрами в сервер

    //По-правильному: игра при запуске сразу парсит все поддерживаемые колоды.
    //При апдейте настроек перестраивает колоды
    //Запускается с уже известными настройками
    //Сервер выполняет лишь начальную рандомизацию.

    //Сейчас:
    //"Приколотить" цифры к серверу. 225 - двери и 163 сокровища
    //При начале игры передать эти цифры каждому клиенту
    //Далее ими управляет уже непосредственно клиент


    //Here was the setting up of cards and showing initials.
    //Now to make it in a special viewing Slots.


    //disbale CardRepresenter
    //_debugShowAllTheCards();

    //change the Game Phase:
    _currentGamePhase = GamePhase::GameInitialization;

    //Initialize timers;
    InitializeMoveTimer();
    InitializePhaseTimer();
    InitializeTicksTimers();
}

The_Game::~The_Game()
{
    delete ui;
}



gameCardDoorMonster The_Game::monsterStringParser(const QString &monster_string)
{

    gameCardDoorMonster theMonster;
    QStringList lst = monster_string.split(";");
    theMonster.setCardID((lst.first()).toInt());
    lst.removeFirst();
#ifndef USE_RESOURCES
    theMonster.setPictureAddress(lst.first());
#else
    theMonster.setPictureAddress(":/" + lst.first());
#endif
    lst.removeFirst();
    theMonster.setCardName(lst.first());
    theMonster.setMonsterName(lst.first());
    lst.removeFirst();
    if (lst.first() == "Basic") theMonster.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theMonster.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theMonster.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();
    theMonster.setType(doorType::Monster);
    lst.removeFirst();
    theMonster.setMonsterLevel(lst.first().toInt());
    lst.removeFirst();
    //for debug; needed to be reworked;
    strongAgainst monsterStruct = theMonsterStrongAgainstParser(lst.first());
    theMonster.setStrongAgainstWoman(monsterStruct.strongAgainstWoman);
    theMonster.setStrongAgainstBard(monsterStruct.strongAgainstBard);
    theMonster.setStrongAgainstCleric(monsterStruct.strongAgainstCleric);
    theMonster.setStrongAgainstDwarf(monsterStruct.strongAgainstDwarf);
    theMonster.setStrongAgainstElf(monsterStruct.strongAgainstElf);
    theMonster.setStrongAgainstGnome(monsterStruct.strongAgainstGnome);
    theMonster.setStrongAgainstHalfBreed(monsterStruct.strongAgainstHalfBreed);
    theMonster.setStrongAgainstHalfling(monsterStruct.strongAgainstHalfling);
    theMonster.setStrongAgainstHuman(monsterStruct.strongAgainstHuman);
    theMonster.setStrongAgainstNoClass(monsterStruct.strongAgainstNoClass);
    theMonster.setStrongAgainstOrk(monsterStruct.strongAgainstOrk);
    theMonster.setStrongAgainstSaturday(monsterStruct.strongAgainstSaturday);
    theMonster.setStrongAgainstSuperMunchkin(monsterStruct.strongAgainstSuperMunchkin);
    theMonster.setStrongAgainstThief(monsterStruct.strongAgainstThief);
    theMonster.setStrongAgainstWarrior(monsterStruct.strongAgainstWarrior);
    theMonster.setStrongAgainstWizard(monsterStruct.strongAgainstWizard);

    lst.removeFirst();
    //
    lst.first() == "false" ? theMonster.setIsUndead(false) :  theMonster.setIsUndead(true);
    lst.removeFirst();
    lst.first() == "false" ? theMonster.setFromHell(false) : theMonster.setFromHell(true);
    lst.removeFirst();
    theMonster.setDontFightWithWoman(false);
    theMonster.setDontFightWithElf(false);
    theMonster.setDontFightWithThief(false);
    theMonster.setDontFightwithOrk(false);

    if (lst.first() == "Woman") theMonster.setDontFightWithWoman(true);
    if (lst.first() == "Thief") theMonster.setDontFightWithThief(true);
    if (lst.first() == "Ork") theMonster.setDontFightwithOrk(true);
    if (lst.first() == "Elf") theMonster.setDontFightWithElf(true);
    lst.removeFirst();
    theMonster.setDontFightTillLevel(lst.first().toInt());
    lst.removeFirst();

    theMonster.setSpecialMechanicAgainstAll(false);
    theMonster.setSpecialMechanicAgainstCleric(false);
    theMonster.setSpecialMechanicAgainstElf(false);
    theMonster.setSpecialMechanicAgainstHalfling(false);
    theMonster.setSpecialMechanicAgainstWizard(false);
    theMonster.setSpecialMechanicAgainstWoman(false);
    theMonster.setSpecialMechanicAginstThief(false);

    if (lst.first() == "noone\n") { lst.removeFirst(); }
        else {
        if (lst.first() == "Woman\n") theMonster.setSpecialMechanicAgainstWoman(true);
        if (lst.first() == "Cleric\n") theMonster.setSpecialMechanicAgainstCleric(true);
        if (lst.first() == "all\n") theMonster.setSpecialMechanicAgainstAll(true);
        if (lst.first() == "Thief\n") theMonster.setSpecialMechanicAginstThief(true);
        if (lst.first() == "Elf\n") theMonster.setSpecialMechanicAgainstElf(true);
        if (lst.first() == "Halfling\n") theMonster.setSpecialMechanicAgainstHalfling(true);
        if (lst.first() == "Wizard\n") theMonster.setSpecialMechanicAgainstWizard(true);

    }

    return theMonster;


}

strongAgainst The_Game::theMonsterStrongAgainstParser(const QString &strongAgainstString)
{
    strongAgainst strong;
    strong.strongAgainstBard = 0;
    strong.strongAgainstCleric = 0;
    strong.strongAgainstDwarf = 0;
    strong.strongAgainstElf = 0;
    strong.strongAgainstGnome = 0;
    strong.strongAgainstHalfBreed = 0;
    strong.strongAgainstHalfling = 0;
    strong.strongAgainstHuman = 0;
    strong.strongAgainstNoClass = 0;
    strong.strongAgainstOrk = 0;
    strong.strongAgainstSuperMunchkin = 0;
    strong.strongAgainstThief = 0;
    strong.strongAgainstWarrior = 0;
    strong.strongAgainstWizard = 0;
    strong.strongAgainstWoman = 0;
    strong.strongAgainstSaturday = 0;

    QStringList lst = strongAgainstString.split("#");
    if (lst.first() == "noone") {

        return strong;
    }
    else {
        for (int var = 0; var < lst.size(); ++var) {
            //qDebug() << lst.at(var);
            const QStringList& newLst = lst.at(var).split("_");

            if (newLst.first() == "Bard") strong.strongAgainstBard = newLst.at(1).toInt();
            if (newLst.first() == "Cleric") strong.strongAgainstCleric = newLst.at(1).toInt();
            if (newLst.first() == "Dwarf") strong.strongAgainstDwarf = newLst.at(1).toInt();
            if (newLst.first() == "Elf") strong.strongAgainstElf= newLst.at(1).toInt();
            if (newLst.first() == "Gnome") strong.strongAgainstGnome = newLst.at(1).toInt();
            if (newLst.first() == "HalfBreed") strong.strongAgainstHalfBreed = newLst.at(1).toInt();
            if (newLst.first() == "Halfling") strong.strongAgainstHalfling = newLst.at(1).toInt();
            if (newLst.first() == "Human") strong.strongAgainstHuman = newLst.at(1).toInt();
            if (newLst.first() == "NoClass") strong.strongAgainstNoClass = newLst.at(1).toInt();
            if (newLst.first() == "Ork") strong.strongAgainstOrk = newLst.at(1).toInt();
            if (newLst.first() == "SuperMunchkin") strong.strongAgainstSuperMunchkin = newLst.at(1).toInt();
            if (newLst.first() == "Thief") strong.strongAgainstThief = newLst.at(1).toInt();
            if (newLst.first() == "Warrior") strong.strongAgainstWarrior = newLst.at(1).toInt();
            if (newLst.first() == "Woman") strong.strongAgainstWoman = newLst.at(1).toInt();
            if (newLst.first() == "Saturday") strong.strongAgainstSaturday = newLst.at(1).toInt();
        }
        return strong;
    }
}

void The_Game::theAmplifiersParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Amplifiers parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            QStringList lst = str.split(";");

            _amplifiersDeck.insert({(lst.first()).toInt(), amplifierStringParser(str)});

        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }

}

#ifndef USE_RESOURCES

#else

#endif

gameCardDoorAmplifier The_Game::amplifierStringParser(const QString &amplifier_string)
{
    gameCardDoorAmplifier theAmplifier;
    QStringList lst = amplifier_string.split(";");
    theAmplifier.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theAmplifier.setPictureAddress(lst.first());
#else
    theAmplifier.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();
    theAmplifier.setCardName(lst.first());
    //setting specifiers
    theAmplifier.setIsEnraged(false);
    theAmplifier.setIsFromHell(false);
    theAmplifier.setIsUndead(false);
    theAmplifier.setIsAncient(false);
    theAmplifier.setIsSleeping(false);
    theAmplifier.setIsBaby(false);
    theAmplifier.setIsVeryDepressed(false);

    if (lst.first() == "Enraged") theAmplifier.setIsEnraged(true);
    if (lst.first() == "Ancient") theAmplifier.setIsAncient(true);
    if (lst.first() == "Baby") theAmplifier.setIsBaby(true);
    if (lst.first() == "Sleeping") theAmplifier.setIsSleeping(true);
    if ((lst.first() == "Undead_1") || (lst.first() == "Undead_2")) theAmplifier.setIsUndead(true);
    if (lst.first() == "From Hell_1") theAmplifier.setIsFromHell(true);
    if (lst.first() == "Very Depressed") theAmplifier.setIsVeryDepressed(true);

    lst.removeFirst();
    if (lst.first() == "Basic") theAmplifier.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theAmplifier.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theAmplifier.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();
    theAmplifier.setType(doorType::MonsterAmplifier);
    lst.removeFirst();

    theAmplifier.setAmplification(lst.first().toInt());
    lst.removeFirst();

    theAmplifier.setAdditionalTreasures(lst.first().toInt());

    return theAmplifier;
}

void The_Game::theCursesParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Curses parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            QStringList lst = str.split(";");

            _cursesDeck.insert({(lst.first()).toInt(), curseStringParser(str)});

        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardDoorCurse The_Game::curseStringParser(const QString &curse_string)
{
    gameCardDoorCurse theCurse;
    QStringList lst = curse_string.split(";");
    theCurse.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theCurse.setPictureAddress(lst.first());
#else
    theCurse.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();
    theCurse.setCardName(lst.first());
    lst.removeFirst();
    if (lst.first() == "Basic") theCurse.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theCurse.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theCurse.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();
    theCurse.setType(doorType::Curse);
    lst.removeFirst();
    theCurse.setMechanic(lst.first());
    lst.removeFirst();
    theCurse.setCurseMechanicID(lst.first().toInt());

    return theCurse;
}

void The_Game::theProfessionsParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Professions parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");
           _professionsDeck.insert({(lst.first()).toInt(), professionStringParser(str)});
        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardDoorProfession The_Game::professionStringParser(const QString &profession_string)
{
    gameCardDoorProfession theProfession;
    QStringList lst = profession_string.split(";");
    theProfession.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theProfession.setPictureAddress(lst.first());
#else
    theProfession.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();
    theProfession.setCardName(lst.first());
    QStringList newLst = lst.first().split("_");
    if (newLst.first() == "Cleric") theProfession.setProfession(Profession::Cleric);
    if (newLst.first() == "Bard") theProfession.setProfession(Profession::Bard);
    if (newLst.first() == "Warrior") theProfession.setProfession(Profession::Warrior);
    if (newLst.first() == "Thief") theProfession.setProfession(Profession::Thief);
    if (newLst.first() == "Wizard") theProfession.setProfession(Profession::Wizard);

    lst.removeFirst();
    if (lst.first() == "Basic") theProfession.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theProfession.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theProfession.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();
    theProfession.setType(doorType::Profession);

    return theProfession;
}

void The_Game::theRacesParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Races parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");
            _racesDeck.insert({(lst.first()).toInt(), racesStringParser(str)});
        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardDoorRace The_Game::racesStringParser(const QString &race_string)
{
    gameCardDoorRace theRace;
    QStringList lst = race_string.split(";");
    theRace.setCardID((lst.first()).toInt());
    lst.removeFirst();
    theRace.setPictureAddress(lst.first());

#ifndef USE_RESOURCES
    theRace.setPictureAddress(lst.first());
#else
    theRace.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();
    theRace.setCardName(lst.first());
    QStringList newLst = lst.first().split("_");
    theRace.setRace(Race::Human);
    if (newLst.first() == "Dwarf") theRace.setRace(Race::Dwarf);
    if (newLst.first() == "Elf") theRace.setRace(Race::Elf);
    if (newLst.first() == "Gnome") theRace.setRace(Race::Gnome);
    if (newLst.first() == "Halfling") theRace.setRace(Race::Halfling);
    if (newLst.first() == "Ork") theRace.setRace(Race::Ork);

    lst.removeFirst();
    if (lst.first() == "Basic") theRace.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theRace.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theRace.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();
    theRace.setType(doorType::Race);

    return theRace;
}

void The_Game::theSpecialMechanicsParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "SpecialMechanics parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");
            _specialMechanicsDeck.insert({(lst.first()).toInt(), specialMechanicStringParser(str)});
        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardDoorSpecialMechanic The_Game::specialMechanicStringParser(const QString &specialMechanic_string)
{
    gameCardDoorSpecialMechanic theSpecialMechanic;
    QStringList lst = specialMechanic_string.split(";");
    theSpecialMechanic.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theSpecialMechanic.setPictureAddress(lst.first());
#else
    theSpecialMechanic.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();
    theSpecialMechanic.setCardName(lst.first());
    lst.removeFirst();
    if (lst.first() == "Basic") theSpecialMechanic.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theSpecialMechanic.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theSpecialMechanic.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();
    theSpecialMechanic.setType(doorType::SpecialMechanic);
    lst.removeFirst();
    lst.removeFirst();
    theSpecialMechanic.setSpecialFunctionId(lst.first().toInt());

    return theSpecialMechanic;
}

void The_Game::theArmorsParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Armors parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");

            _armorDeck.insert({(lst.first()).toInt(), armorsStringParser(str)});
        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }



}

gameCardTreasureArmor The_Game::armorsStringParser(const QString &armor_string)
{
    gameCardTreasureArmor theArmor;
    QStringList lst = armor_string.split(";");

    theArmor.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theArmor.setPictureAddress(lst.first());
#else
    theArmor.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();
    theArmor.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theArmor.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theArmor.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theArmor.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theArmor.setType(treasureType::Armor);
    lst.removeFirst();

    if (lst.first() == "Head") theArmor.setPart(Body_Part::Head);
    else if (lst.first() == "Feet") theArmor.setPart(Body_Part::Feet);
    else if (lst.first() == "Armor") theArmor.setPart(Body_Part::Armor);
    lst.removeFirst();

    if (lst.first() == "Big") theArmor.setSize(Size::Big);
    else theArmor.setSize(Size::Small);
    lst.removeFirst();

    theArmor.setBonus(lst.first().toInt());
    lst.removeFirst();

    //some cheat here! Needed to be reworked to work with everyone
    theArmor.setAdditionalBonusforElf(0);
    theArmor.setAdditionalBonusforOrk(0);
    QStringList newLst = lst.first().split("_");
    if (newLst.first() == "Elf_2") theArmor.setAdditionalBonusforElf(2);
    else if (newLst.first() == "Ork_2") theArmor.setAdditionalBonusforOrk(2);
    lst.removeFirst();

    //parsing "is..for"
    isOnlyFor restrictions = TheArmorIsForParser(lst.first());
    theArmor.setIsOnlyForDwarf(restrictions.isOnlyForDwarf);
    theArmor.setIsOnlyForHuman(restrictions.isOnlyForHuman);
    theArmor.setIsOnlyForWizard(restrictions.isOnlyForWizard);
    theArmor.setIsOnlyForGnome(restrictions.isOnlyForGnome);
    theArmor.setIsRestrictedToGnome(restrictions.isRestrictedToGnome);
    theArmor.setIsRestrictedToWizard(restrictions.isRestrictedToWizard);

    lst.removeFirst();

    theArmor.setHasSpecialMechanic(false);
    if (lst.first() == "yes") theArmor.setHasSpecialMechanic(true);
    lst.removeFirst();

    theArmor.setPrice(lst.first().toInt());
    lst.removeFirst();

    theArmor.setBonusToFleeing(lst.first().toInt());
    lst.removeFirst();

    theArmor.setIsCombined(false);
    if (lst.first() == "yes\n") {
        theArmor.setIsCombined(true);
    };

    return theArmor;
}

isOnlyFor The_Game::TheArmorIsForParser(const QString &isFor_string)
{
     QStringList newLst = isFor_string.split("_");
     isOnlyFor armor;

     armor.isOnlyForDwarf = false;
     armor.isOnlyForHuman = false;
     armor.isOnlyForGnome = false;
     armor.isOnlyForWizard = false;

     armor.isRestrictedToGnome = false;
     armor.isRestrictedToWizard = false;

     if (newLst.first() == "ex") {
         if (newLst.last() == "Wizard") {
         armor.isRestrictedToWizard = true;
         };
         if (newLst.last() == "Gnome") {
         armor.isRestrictedToGnome = true;
         };
     }
     else {
         if (newLst.first() == "Human") {
             armor.isOnlyForHuman = true;
         };
         if (newLst.first() == "Wizard") {
             armor.isOnlyForWizard = true;
         };
         if (newLst.first() == "Dwarf") {
             armor.isOnlyForDwarf = true;
         };
         if (newLst.first() == "Gnome") {
             armor.isOnlyForGnome = true;
         };
     }

     return armor;
}

void The_Game::theArmorAmplifiersParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "ArmorAmplifiers parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            QStringList lst = str.split(";");

            _armorAmplifiersDeck.insert({(lst.first()).toInt(), armorAmplifierStringParser(str)});

        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardTreasureArmorAmplifier The_Game::armorAmplifierStringParser(const QString &armorAmplifier_string)
{
    gameCardTreasureArmorAmplifier theArmorAmplifier;
    QStringList lst = armorAmplifier_string.split(";");

    theArmorAmplifier.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
     theArmorAmplifier.setPictureAddress(lst.first());
#else
    theArmorAmplifier.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theArmorAmplifier.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theArmorAmplifier.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theArmorAmplifier.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theArmorAmplifier.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theArmorAmplifier.setType(treasureType::ArmorAmplifier);
    lst.removeFirst();

    theArmorAmplifier.setBonus(lst.first().toInt());

    return theArmorAmplifier;
}

void The_Game::theBattleAmplifiersParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "BattleAmplifiers parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            QStringList lst = str.split(";");

            _battleAmplifiersDeck.insert({(lst.first()).toInt(), battleAmplifierStringParser(str)});

        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardTreasureBattleAmplifier The_Game::battleAmplifierStringParser(const QString &battleAmplifier_string)
{
    gameCardTreasureBattleAmplifier theBattleAmplifier;
    QStringList lst = battleAmplifier_string.split(";");

    theBattleAmplifier.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theBattleAmplifier.setPictureAddress(lst.first());
#else
    theBattleAmplifier.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theBattleAmplifier.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theBattleAmplifier.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theBattleAmplifier.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theBattleAmplifier.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theBattleAmplifier.setType(treasureType::BattleAmplifier);
    lst.removeFirst();

    theBattleAmplifier.setBonus(lst.first().toInt());
    lst.removeFirst();

    if (lst.first().toInt()) {
        theBattleAmplifier.setIsPotion(true);
    }
    else {
        theBattleAmplifier.setIsPotion(false);
    }

    lst.removeFirst();

    theBattleAmplifier.setHasSpecialMechanic(false);
    if (lst.first() == "yes\n") {
        theBattleAmplifier.setHasSpecialMechanic(true);
    };
    return theBattleAmplifier;



}

void The_Game::theLevelUpParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "LevelUp parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");
            _levelUpDeck.insert({(lst.first()).toInt(),levelUpStringParser(str)});
        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardTreasureLevelUp The_Game::levelUpStringParser(const QString &levelUp_string)
{
    gameCardTreasureLevelUp theLevelUp;
    QStringList lst = levelUp_string.split(";");

    theLevelUp.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
   theLevelUp.setPictureAddress(lst.first());
#else
    theLevelUp.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theLevelUp.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theLevelUp.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theLevelUp.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theLevelUp.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theLevelUp.setType(treasureType::LevelUp);
    lst.removeFirst();

    theLevelUp.setHasSpecialMechanic(false);
    if (lst.first().toInt()) {
        theLevelUp.setHasSpecialMechanic(true);
    }
    return theLevelUp;
}


//enum class Additional_Request {noCompanion, failedToFlee,
//                              succeededToFlee, win, onceReceived,
//                              haveCompanion, thereIsDwarf, noRequest};

Additional_Request The_Game::theAdditionalRequestParser(const QString &additionalRequest_string)
{
    Additional_Request request = Additional_Request::noRequest;

    if (additionalRequest_string == "noCompanion\n") {
        request = Additional_Request::noCompanion;
    }
    if (additionalRequest_string == "failedToFlee\n") {
        request = Additional_Request::failedToFlee;
    }
    if (additionalRequest_string == "succeededToFlee\n") {
        request = Additional_Request::succeededToFlee;
    }
    if (additionalRequest_string == "win\n") {
        request = Additional_Request::win;
    }
    if (additionalRequest_string == "onceReceived\n") {
        request = Additional_Request::onceReceived;
    }
    if (additionalRequest_string == "haveCompanion\n") {
        request = Additional_Request::haveCompanion;
    }
    if (additionalRequest_string == "thereIsDwarf\n") {
        request = Additional_Request::thereIsDwarf;
    }
    return request;
}


//enum class Time_To_Use {ownFight, anytime, eachFight, immediately, afterFight,
//                       dieWasPlayed, ownMove, exceptFight};

Time_To_Use The_Game::theTimeToUseParser(const QString &timeTouse_string)
{
    Time_To_Use gamePhaseToPlay = Time_To_Use::anytime;
    if (timeTouse_string == "ownFight") {
        gamePhaseToPlay = Time_To_Use::ownFight;
    }
    if (timeTouse_string == "anytime") {
        gamePhaseToPlay = Time_To_Use::anytime;
    }
    if (timeTouse_string == "eachFight") {
        gamePhaseToPlay = Time_To_Use::eachFight;
    }
    if (timeTouse_string == "immediately") {
        gamePhaseToPlay = Time_To_Use::immediately;
    }
    if (timeTouse_string == "afterFight") {
        gamePhaseToPlay = Time_To_Use::afterFight;
    }
    if (timeTouse_string == "dieWasPlayed") {
        gamePhaseToPlay = Time_To_Use::dieWasPlayed;
    }
    if (timeTouse_string == "ownMove") {
        gamePhaseToPlay = Time_To_Use::ownMove;
    }
    if (timeTouse_string == "exceptFight") {
        gamePhaseToPlay = Time_To_Use::exceptFight;
    }
    return gamePhaseToPlay;
}

void The_Game::theSpecialMechanicTreasureParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "TreasureSpecialMechanics parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            QStringList lst = str.split(";");

            _specialMechanicsTreasureDeck.insert({(lst.first()).toInt(),SpecialMechanicTreasureStringParser(str)});

        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardTreasureSpecialMechanic The_Game::SpecialMechanicTreasureStringParser(const QString &specialMechanicsTreasure_string)
{
    gameCardTreasureSpecialMechanic theSpecialMechanic;
    QStringList lst = specialMechanicsTreasure_string.split(";");

    theSpecialMechanic.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theSpecialMechanic.setPictureAddress(lst.first());
#else
    theSpecialMechanic.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theSpecialMechanic.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theSpecialMechanic.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theSpecialMechanic.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theSpecialMechanic.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theSpecialMechanic.setType(treasureType::SpecialMechanic);
    lst.removeFirst();

    theSpecialMechanic.setPrice(lst.first().toInt());
    lst.removeFirst();

    theSpecialMechanic.setIsPotion(false);
    if (lst.first().toInt()) {
        theSpecialMechanic.setIsPotion(true);
    }
    lst.removeFirst();

    theSpecialMechanic.setTimeToUse(theTimeToUseParser(lst.first()));
    lst.removeFirst();

    theSpecialMechanic.setAdditionalRequest(theAdditionalRequestParser(lst.first()));

    return theSpecialMechanic;
}

isOnlyFor_ThingsAmplifiers The_Game::TheThingsAmplifiersIsForParser(const QString &isFor_string)
{
    QStringList newLst = isFor_string.split("_");
    isOnlyFor_ThingsAmplifiers thingAmplifiers;

    thingAmplifiers.isOnlyForCleric = false;
    thingAmplifiers.isOnlyForHalfling = false;
    thingAmplifiers.isOnlyForThief = false;
    thingAmplifiers.isOnlyForWizard = false;

    thingAmplifiers.isRestrictedtoThief = false;
    thingAmplifiers.isRestrictedToCleric = false;
    thingAmplifiers.isRestrictedToWarrior = false;

    if (newLst.first() == "ex") {
        if (newLst.last() == "Warrior") {
        thingAmplifiers.isRestrictedToWarrior = true;
        };
        if (newLst.last() == "Cleric") {
        thingAmplifiers.isRestrictedToCleric = true;
        };
        if (newLst.last() == "Thief") {
        thingAmplifiers.isRestrictedtoThief = true;
        };
    }
    else {
        if (newLst.first() == "Thief") {
            thingAmplifiers.isOnlyForThief = true;
        };
        if (newLst.first() == "Wizard") {
            thingAmplifiers.isOnlyForWizard = true;
        };
        if (newLst.first() == "Halfling") {
            thingAmplifiers.isOnlyForHalfling = true;
        };
        if (newLst.first() == "Cleric") {
            thingAmplifiers.isOnlyForCleric = true;
        };
    }

    return thingAmplifiers;
}

void The_Game::theThingsAmplifiersParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Things Amplifiers parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");

            _thingsAmplifiersDeck.insert({(lst.first()).toInt(),ThingsAmplifiersStringParser(str)});
        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardTreasureThingsAmplifiers The_Game::ThingsAmplifiersStringParser(const QString &thingsAmplifiers_string)
{
    gameCardTreasureThingsAmplifiers theThingAmplifier;
    QStringList lst = thingsAmplifiers_string.split(";");

    theThingAmplifier.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theThingAmplifier.setPictureAddress(lst.first());
#else
    theThingAmplifier.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theThingAmplifier.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theThingAmplifier.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theThingAmplifier.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theThingAmplifier.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theThingAmplifier.setType(treasureType::ThingsAmplifiers);
    lst.removeFirst();

    theThingAmplifier.setSize(Size::Small);
    if (lst.first() == "big") {
        theThingAmplifier.setSize(Size::Big);
    }
    lst.removeFirst();

    theThingAmplifier.setBonus(lst.first().toInt());
    lst.removeFirst();

    theThingAmplifier.setHasSpecialMechanic(false);
    if (lst.first() == "yes") {
        theThingAmplifier.setHasSpecialMechanic(true);;
    }
    lst.removeFirst();

    theThingAmplifier.setIsKnees(false);

    if (lst.first().toInt()) {
        theThingAmplifier.setIsKnees(true);;
    }
    lst.removeFirst();

    isOnlyFor_ThingsAmplifiers restrictions = TheThingsAmplifiersIsForParser(lst.first());
    theThingAmplifier.setIsOnlyForCleric(restrictions.isOnlyForCleric);
    theThingAmplifier.setIsOnlyForHalfling(restrictions.isOnlyForHalfling);
    theThingAmplifier.setIsOnlyForThief(restrictions.isOnlyForThief);
    theThingAmplifier.setIsOnlyForWizard(restrictions.isOnlyForWizard);


    theThingAmplifier.setIsRestrictedToWarrior(restrictions.isRestrictedToWarrior);
    theThingAmplifier.setIsRestrictedToCleric(restrictions.isRestrictedToCleric);
    theThingAmplifier.setIsRestrictedToThief(restrictions.isRestrictedtoThief);

    lst.removeFirst();

    theThingAmplifier.setPrice(lst.first().toInt());
    lst.removeFirst();

    theThingAmplifier.setBonusToFlee(lst.first().toInt());
    lst.removeFirst();

    theThingAmplifier.setBonusToHands(lst.first().toInt());
    lst.removeFirst();

    theThingAmplifier.setBonusToMan(lst.first().toInt());
    lst.removeFirst();

    theThingAmplifier.setBonusToWoman(lst.first().toInt());
    lst.removeFirst();

    theThingAmplifier.setAllowedToWearDwarven(false);
    if (lst.first().toInt()) {
        theThingAmplifier.setAllowedToWearDwarven(true);
    }
    lst.removeFirst();

    theThingAmplifier.setAllowedToWearElven(false);
    if (lst.first().toInt()) {
        theThingAmplifier.setAllowedToWearElven(true);
    }

    return theThingAmplifier;
}

isOnlyFor_Weapon The_Game::TheWeaponIsForParser(const QString &isFor_string)
{
    isOnlyFor_Weapon restrictions;

    restrictions.isOnlyForBard = false;
    restrictions.isOnlyForDwarf = false;
    restrictions.isOnlyForElf = false;
    restrictions.isOnlyForGnome = false;
    restrictions.isOnlyForHalfling = false;
    restrictions.isOnlyForHuman = false;
    restrictions.isOnlyForMan = false;
    restrictions.isOnlyForOrk = false;
    restrictions.isOnlyForThief = false;
    restrictions.isOnlyForWarrior = false;
    restrictions.isOnlyForWizard = false;
    restrictions.isOnlyForWoman = false;
    restrictions.isOnlyForCleric = false;

    if (isFor_string == "Elf") {
        restrictions.isOnlyForElf = true;
    };
    if (isFor_string == "Man") {
        restrictions.isOnlyForMan = true;
    };
    if (isFor_string == "Dwarf") {
        restrictions.isOnlyForDwarf = true;
    };
    if (isFor_string == "Human") {
        restrictions.isOnlyForHuman = true;
    };
    if (isFor_string == "Wizard") {
        restrictions.isOnlyForWizard = true;
    };
    if (isFor_string == "Woman") {
        restrictions.isOnlyForWoman = true;
    };
    if (isFor_string == "Warrior") {
        restrictions.isOnlyForWarrior = true;
    };
    if (isFor_string == "Thief") {
        restrictions.isOnlyForThief = true;
    };
    if (isFor_string == "Cleric") {
        restrictions.isOnlyForCleric = true;
    };
    if (isFor_string == "Ork") {
        restrictions.isOnlyForOrk = true;
    };
    if (isFor_string == "Halfling") {
        restrictions.isOnlyForHalfling = true;
    };
    if (isFor_string == "Gnome") {
        restrictions.isOnlyForGnome = true;
    };
    if (isFor_string == "Bard") {
        restrictions.isOnlyForBard = true;
    };
    return restrictions;
}

void The_Game::theWeaponParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Weapons parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(";");
            _weaponsDeck.insert({(lst.first()).toInt(),WeaponStringParser(str)});
        }
    }

    else
    {
        qDebug()<< "Cannot open this file!";
    }
}

gameCardTreasureWeapon The_Game::WeaponStringParser(const QString &weapons_string)
{
    gameCardTreasureWeapon theWeapon;
    QStringList lst = weapons_string.split(";");

    theWeapon.setCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theWeapon.setPictureAddress(lst.first());
#else
    theWeapon.setPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theWeapon.setCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theWeapon.setAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theWeapon.setAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theWeapon.setAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theWeapon.setType(treasureType::Weapon);
    lst.removeFirst();

    theWeapon.setHands(lst.first().toInt());
    lst.removeFirst();

    theWeapon.setSize(Size::Small);
    if (lst.first() == "big") {
        theWeapon.setSize(Size::Big);
    }
    lst.removeFirst();

    theWeapon.setBonus(lst.first().toInt());
    lst.removeFirst();

    isOnlyFor_Weapon restrictions = TheWeaponIsForParser(lst.first());
    theWeapon.setIsOnlyForBard(restrictions.isOnlyForBard);
    theWeapon.setIsOnlyForCleric(restrictions.isOnlyForCleric);
    theWeapon.setIsOnlyForDwarf(restrictions.isOnlyForDwarf);
    theWeapon.setIsOnlyForElf(restrictions.isOnlyForElf);
    theWeapon.setIsOnlyForGnome(restrictions.isOnlyForGnome);
    theWeapon.setIsOnlyForHalfling(restrictions.isOnlyForHalfling);
    theWeapon.setIsOnlyForHuman(restrictions.isOnlyForHuman);
    theWeapon.setIsOnlyForMan(restrictions.isOnlyForMan);
    theWeapon.setIsOnlyForOrk(restrictions.isOnlyForOrk);
    theWeapon.setIsOnlyForThief(restrictions.isOnlyForThief);
    theWeapon.setIsOnlyForWarrior(restrictions.isOnlyForWarrior);
    theWeapon.setIsOnlyForWizard(restrictions.isOnlyForWizard);
    theWeapon.setIsOnlyForWoman(restrictions.isOnlyForWoman);

    lst.removeFirst();

    theWeapon.setHasSpecialMechanic(false);
    if (lst.first() == "yes") {
        theWeapon.setHasSpecialMechanic(true);;
    }
    lst.removeFirst();

    theWeapon.setPrice(lst.first().toInt());
    lst.removeFirst();

    theWeapon.setBonusToFlee(lst.first().toInt());
    lst.removeFirst();

    theWeapon.setAdditionalBonusAgainstUndead(lst.first().toInt());
    lst.removeFirst();

    theWeapon.setAutomaticLooseToCalmadzila(false);
    if (lst.first().toInt()) {
         theWeapon.setAutomaticLooseToCalmadzila(true);
    }
    lst.removeFirst();

    theWeapon.setAdditionalBonusAgainst_J(lst.first().toInt());
    lst.removeFirst();

    theWeapon.setAddingClericalAbility(false);
    if (lst.first().toInt()) {
         theWeapon.setAddingClericalAbility(true);
    }
    lst.removeFirst();

    theWeapon.setAddingThiefAbility(false);
    if (lst.first().toInt()) {
         theWeapon.setAddingThiefAbility(true);
    }

    return theWeapon;

}

void The_Game::_debugShowAllTheCards()
{
    ui->GameField->cardsRepresenter();
}

void The_Game::PassDecksToBattleField()
{
    ui->GameField->setMonsersDeck(monstersDeck());
    ui->GameField->setAmplifiersDeck(amplifiersDeck());
    ui->GameField->setArmorAmplifiersDeck(armorAmplifiersDeck());
    ui->GameField->setArmorDeck(armorDeck());
    ui->GameField->setBattleAmplifiersDeck(battleAmplifiersDeck());
    ui->GameField->setCursesDeck(cursesDeck());
    ui->GameField->setLevelUpDeck(levelUpDeck());
    ui->GameField->setProfessionsDeck(professionsDeck());
    ui->GameField->setRacesDeck(racesDeck());
    ui->GameField->setSpecialMechanicsDeck(specialMechanicsDeck());
    ui->GameField->setSpecialMechanicsTreasureDeck(specialMechanicsTreasureDeck());
    ui->GameField->setThingsAmplifiersDeck(thingsAmplifiersDeck());
    ui->GameField->setWeaponsDeck(weaponsDeck());
}

void The_Game::passDecksToPlayerWidgets()
{
    ui->MainGamer->setMonsersDeck(monstersDeck());
    ui->MainGamer->setAmplifiersDeck(amplifiersDeck());
    ui->MainGamer->setArmorAmplifiersDeck(armorAmplifiersDeck());
    ui->MainGamer->setArmorDeck(armorDeck());
    ui->MainGamer->setBattleAmplifiersDeck(battleAmplifiersDeck());
    ui->MainGamer->setCursesDeck(cursesDeck());
    ui->MainGamer->setLevelUpDeck(levelUpDeck());
    ui->MainGamer->setProfessionsDeck(professionsDeck());
    ui->MainGamer->setRacesDeck(racesDeck());
    ui->MainGamer->setSpecialMechanicsDeck(specialMechanicsDeck());
    ui->MainGamer->setSpecialMechanicsTreasureDeck(specialMechanicsTreasureDeck());
    ui->MainGamer->setThingsAmplifiersDeck(thingsAmplifiersDeck());
    ui->MainGamer->setWeaponsDeck(weaponsDeck());

    ui->MainGamer->passCardsDecksToHandsWidget();

    for (unsigned int var = 0; var < _widgets4Opponents.size(); ++var)
    {
        (_widgets4Opponents[var])->setMonsersDeck(monstersDeck());
        (_widgets4Opponents[var])->setAmplifiersDeck(amplifiersDeck());
        (_widgets4Opponents[var])->setArmorAmplifiersDeck(armorAmplifiersDeck());
        (_widgets4Opponents[var])->setArmorDeck(armorDeck());
        (_widgets4Opponents[var])->setBattleAmplifiersDeck(battleAmplifiersDeck());
        (_widgets4Opponents[var])->setCursesDeck(cursesDeck());
        (_widgets4Opponents[var])->setLevelUpDeck(levelUpDeck());
        (_widgets4Opponents[var])->setProfessionsDeck(professionsDeck());
        (_widgets4Opponents[var])->setRacesDeck(racesDeck());
        (_widgets4Opponents[var])->setSpecialMechanicsDeck(specialMechanicsDeck());
        (_widgets4Opponents[var])->setSpecialMechanicsTreasureDeck(specialMechanicsTreasureDeck());
        (_widgets4Opponents[var])->setThingsAmplifiersDeck(thingsAmplifiersDeck());
        (_widgets4Opponents[var])->setWeaponsDeck(weaponsDeck());
        (_widgets4Opponents[var])->passCardsDecksToHandsWidget();
    }
}

void The_Game::PassDecksToPopUpCardWidget()
{
    _popUpCardWidget->setMonsersDeck(monstersDeck());
    _popUpCardWidget->setAmplifiersDeck(amplifiersDeck());
    _popUpCardWidget->setArmorAmplifiersDeck(armorAmplifiersDeck());
    _popUpCardWidget->setArmorDeck(armorDeck());
    _popUpCardWidget->setBattleAmplifiersDeck(battleAmplifiersDeck());
    _popUpCardWidget->setCursesDeck(cursesDeck());
    _popUpCardWidget->setLevelUpDeck(levelUpDeck());
    _popUpCardWidget->setProfessionsDeck(professionsDeck());
    _popUpCardWidget->setRacesDeck(racesDeck());
    _popUpCardWidget->setSpecialMechanicsDeck(specialMechanicsDeck());
    _popUpCardWidget->setSpecialMechanicsTreasureDeck(specialMechanicsTreasureDeck());
    _popUpCardWidget->setThingsAmplifiersDeck(thingsAmplifiersDeck());
    _popUpCardWidget->setWeaponsDeck(weaponsDeck());
}

void The_Game::PassDecksToCardsStacksWidget()
{
    ui->CardStacksWidget->setMonsersDeck(monstersDeck());
    ui->CardStacksWidget->setAmplifiersDeck(amplifiersDeck());
    ui->CardStacksWidget->setArmorAmplifiersDeck(armorAmplifiersDeck());
    ui->CardStacksWidget->setArmorDeck(armorDeck());
    ui->CardStacksWidget->setBattleAmplifiersDeck(battleAmplifiersDeck());
    ui->CardStacksWidget->setCursesDeck(cursesDeck());
    ui->CardStacksWidget->setLevelUpDeck(levelUpDeck());
    ui->CardStacksWidget->setProfessionsDeck(professionsDeck());
    ui->CardStacksWidget->setRacesDeck(racesDeck());
    ui->CardStacksWidget->setSpecialMechanicsDeck(specialMechanicsDeck());
    ui->CardStacksWidget->setSpecialMechanicsTreasureDeck(specialMechanicsTreasureDeck());
    ui->CardStacksWidget->setThingsAmplifiersDeck(thingsAmplifiersDeck());
    ui->CardStacksWidget->setWeaponsDeck(weaponsDeck());

    ui->CardStacksWidget->setTotalTreasures(_monstersDeck.size());
    ui->CardStacksWidget->setTotalDoors(_treasuresDeck.size());
}

void The_Game::PassDecksToCardsInspectorWidget()
{
    ui->wdgt_CardInspector->setMonsersDeck(monstersDeck());
    ui->wdgt_CardInspector->setAmplifiersDeck(amplifiersDeck());
    ui->wdgt_CardInspector->setArmorAmplifiersDeck(armorAmplifiersDeck());
    ui->wdgt_CardInspector->setArmorDeck(armorDeck());
    ui->wdgt_CardInspector->setBattleAmplifiersDeck(battleAmplifiersDeck());
    ui->wdgt_CardInspector->setCursesDeck(cursesDeck());
    ui->wdgt_CardInspector->setLevelUpDeck(levelUpDeck());
    ui->wdgt_CardInspector->setProfessionsDeck(professionsDeck());
    ui->wdgt_CardInspector->setRacesDeck(racesDeck());
    ui->wdgt_CardInspector->setSpecialMechanicsDeck(specialMechanicsDeck());
    ui->wdgt_CardInspector->setSpecialMechanicsTreasureDeck(specialMechanicsTreasureDeck());
    ui->wdgt_CardInspector->setThingsAmplifiersDeck(thingsAmplifiersDeck());
    ui->wdgt_CardInspector->setWeaponsDeck(weaponsDeck());
}


const std::map<int, gameCardDoorMonster> *The_Game::monstersDeck()
{
    return &_monstersDeck;
}

const std::map<int, gameCardDoorAmplifier> *The_Game::amplifiersDeck()
{
    return &_amplifiersDeck;
}

const std::map<int, gameCardDoorCurse> *The_Game::cursesDeck()
{
    return &_cursesDeck;
}

const std::map<int, gameCardDoorProfession> *The_Game::professionsDeck()
{
    return &_professionsDeck;
}

const std::map<int, gameCardDoorRace> *The_Game::racesDeck()
{
    return &_racesDeck;
}

const std::map<int, gameCardDoorSpecialMechanic> *The_Game::specialMechanicsDeck()
{
    return &_specialMechanicsDeck;
}

const std::map<int, gameCardTreasureArmor> *The_Game::armorDeck()
{
    return &_armorDeck;
}

const std::map<int, gameCardTreasureArmorAmplifier> *The_Game::armorAmplifiersDeck()
{
    return &_armorAmplifiersDeck;
}

const std::map<int, gameCardTreasureBattleAmplifier> *The_Game::battleAmplifiersDeck()
{
    return &_battleAmplifiersDeck;
}

const std::map<int, gameCardTreasureLevelUp> *The_Game::levelUpDeck()
{
    return &_levelUpDeck;
}

const std::map<int, gameCardTreasureSpecialMechanic> *The_Game::specialMechanicsTreasureDeck()
{
    return &_specialMechanicsTreasureDeck;
}

const std::map<int, gameCardTreasureThingsAmplifiers> *The_Game::thingsAmplifiersDeck()
{
    return &_thingsAmplifiersDeck;
}

const std::map<int, gameCardTreasureWeapon> *The_Game::weaponsDeck()
{
    return &_weaponsDeck;
}

//This procedure is responsible for giving initial 8 cards to players.
//If the Server is Working, it is resposible for providing this info for the end-client.
//For the DEBUG version, it will give the numbers (cardIDs) to end-gamers directly.
//No #ifdef directive for now.

void The_Game::GivingCardsToPlayers()
{
#ifdef DEBUG_NO_SERVER

    //define, how many players are presented;
    //this value is received once from server side and can't be changed during the game if only the player is leaving the game;
    uint32_t totalOpponents = _gameSettings.maximumNumberOfPlayers() - 1; //6 as default
    uint32_t cardsToGive = 4;

    //then it is necessary to give m_number_of_players*4 cards from doors stack, and
    //the same quantity from the Treasures stack.

    //start with the main player... (giving cards from the top)

    uint32_t initialSizeDoors = _doorsDeck.size();
    uint32_t initialSizeTreasures = _treasuresDeck.size();

    for (unsigned int var = 0; var < cardsToGive; ++var) {

        _mainPlayer->addCardToHands(_doorsDeck.front());
        _doorsDeck.erase(_doorsDeck.begin());
    }

    //giving cards to the other players...

    for (uint32_t var = 0; var < totalOpponents; ++var) {

        for (uint32_t j = 0; j < cardsToGive; ++j ) {

            _playersOpponents[var]->addCardToHands(_doorsDeck.front());
            _doorsDeck.erase(_doorsDeck.begin());
        }
    }

    ui->CardStacksWidget->updateDoorsLeft(initialSizeDoors - cardsToGive*(_gameSettings.maximumNumberOfPlayers()));
    qDebug() << "Doors are given to the players!";

    //treasures..
    for (uint32_t var = 0; var < cardsToGive; ++var)
    {
        _mainPlayer->addCardToHands(_treasuresDeck.front());
        _treasuresDeck.erase(_treasuresDeck.begin());
    }

    //giving cards to the other players...
    for (unsigned int var = 0; var < totalOpponents; ++var) {

        for (unsigned int j = 0; j < cardsToGive; ++j ) {

            _playersOpponents[var]->addCardToHands(_treasuresDeck.front());
            _treasuresDeck.erase(_treasuresDeck.begin());
        }
    }
    qDebug() << "Treasures are given to the players!";

    ui->CardStacksWidget->updateTreasuresLeft(initialSizeTreasures - cardsToGive*_gameSettings.maximumNumberOfPlayers());
#endif
}

void The_Game::ShowInitialCardsOnHands()
{
    qDebug() << "showInitialCardsOnHands:: Started";
    for (unsigned int var = 0; var < _mainPlayer->cardsOnHandsVector()->size(); ++var)
    {
        ui->MainGamer->addTheCardToHandsWidget(*((_mainPlayer->cardsOnHandsVector())->begin() + static_cast<int>(var)));
    }

    qDebug() << "NAY-002: _playersOpponents.size(): " << _playersOpponents.size();

    for (unsigned int var = 0; var < _playersOpponents.size(); ++var)
    {
        unsigned int totalCardsToShow = _playersOpponents[var]->GetCardsOnHands().size();
        std::vector<SimpleCard> cardsOnHands = _playersOpponents[var]->GetCardsOnHands();
        for (unsigned int j = 0; j < cardsOnHands.size(); ++j)
        {            
            _widgets4Opponents[var]->addTheCardToHandsWidget(cardsOnHands[j]);
        }
    }
    qDebug() << "showInitialCardsOnHands:: Completed";
}


//this function might only be called after the cards stacks are initialized.
//If this rule is note completed, the sizes will be empty!
void The_Game::DEBUGformingInitialDecks()
{

#ifdef DEBUG_NO_SERVER

    //start with the treasures..
    std::vector<unsigned int> valuesTreasures;
    //continue with doors...
    std::vector<unsigned int> valuesDoors;

    unsigned int totalTreasures = _armorDeck.size() + _armorAmplifiersDeck.size() + _battleAmplifiersDeck.size() + _levelUpDeck.size() +
            _specialMechanicsTreasureDeck.size() + _thingsAmplifiersDeck.size() + _weaponsDeck.size();

    unsigned int totalDoors = _monstersDeck.size() + _amplifiersDeck.size() + _cursesDeck.size() + _professionsDeck.size() +
            _racesDeck.size() + _specialMechanicsDeck.size();

   //NAY-001: MARK_EXPECTED_ERROR
   //These sizes ARE USED AS DEFINES ON SERVER SIDE.
   //HERE TO CHECK AND THROW AN EXCEPTION IF THEY ARE NOT CORRECT
   //I do not want to place all the code on the server's side - with cards and so on;
   //This data should be given by master to the server while passing settings
   //(Not visible to user)

   if (!totalTreasures)  qDebug() << "Error during Treasures Stack Initialization. Stack is Empty! ";
   qDebug() << "Size of Treasures Stack Report: " << totalTreasures;
   if (!totalDoors)  qDebug() << "Error during Doors Stack Initialization. Stack is Empty! ";
   qDebug() << "Size of Doors Stack Report: " << totalDoors;

    //the server knows exact values of sizes of arrays
    for (unsigned int var = 1; var < totalTreasures+1; ++var) {
        valuesTreasures.push_back(var);
    }
    for (unsigned int var = 1; var < totalDoors+1; ++var) {
        valuesDoors.push_back(var);
    }
    for (unsigned int var = 0; var < totalTreasures; ++var) {

        unsigned int valuesLeft = valuesTreasures.size();
        unsigned int currentPosition = randUnsignedInt(0, valuesLeft-1);
        _treasuresDeck.push_back({true,valuesTreasures[currentPosition]});
        valuesTreasures.erase(valuesTreasures.begin() + static_cast<int>(currentPosition)); //remove additional
        valuesTreasures.shrink_to_fit();
    }

    qDebug() << "Treasures Stack is Filled Now!";

    for (unsigned int var = 0; var < totalDoors; ++var) {

        unsigned int valuesLeft = valuesDoors.size();
        unsigned int currentPosition = randUnsignedInt(0, valuesLeft-1);
        _doorsDeck.push_back({false,valuesDoors[currentPosition]});
        valuesDoors.erase(valuesDoors.begin() + static_cast<int>(currentPosition)); //remove additional
        valuesDoors.shrink_to_fit();
    }

    qDebug() << "Doors Stack is Filled Now!";

#endif

}

unsigned int The_Game::randUnsignedInt(unsigned int low, unsigned int high)
{
    // Random number between low and high
    return static_cast<unsigned int>(qrand() % ((high + 1) - low) + low);
}

void The_Game::theMonstersParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Monsters parsing starts!";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd())
        {

            QString str = file.readLine();
            QStringList lst = str.split(";");

            _monstersDeck.insert({(lst.first()).toInt(),monsterStringParser(str)});
        }
    }
    else
    {
        qDebug()<< "Cannot open this file!";
    }
}


void The_Game::DEBUG_SlotWasPushedToGameMode()
{   
    _playersOrder.push_back(_gameSettings.clientName());
    _playersOrder.push_back("DEBUG_Opponent");
    if (_gameSettings.maximumNumberOfPlayers() != 2)
        throw "DEBUG ERROR! _gameSettings.maximumNumberOfPlayers() != 2";

    //Set Up Players And Widgets
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    SetUpPlayersAndWidgets(HW_Screen_Size.height(), HW_Screen_Size.width(), _playersOrder);
    PassCardsToWidgets();
    ui->GameField->setPlayersOrder(_playersOrder);

    DEBUGformingInitialDecks();
    GivingCardsToPlayers();
    ShowInitialCardsOnHands();
    ui->GameField->InitializeStartUpProcedureVisualization();
    emit DEBUG_SignalToBeShown(true);
}

void The_Game::dbg_return_to_the_main_window()
{
    emit DEBUG_ReturnToBeforeTheGame(true);
}

void The_Game::SlotShowTheCardInCentre(PositionedCard card)
{
    card.AddBase(this->pos());
//    qDebug() << "Application Global Coordinates: " << "X: " <<  pos().x()<< " Y: " << pos().y();
    //pass the card to PopUpWidget

    _popUpCardWidget->setUpPointsForPoly(card.GetPositionTopLeft(), card.GetPositionBottomRight());
    _popUpCardWidget->setUpPopUpCard(card.GetCard());

#ifndef __linux__
    _popUpCardWidget->show(card.GetPositionTopLeft(), card.GetPositionBottomRight());
#else
    //_popUpCardWidget->show();
    _popUpCardWidget->show(card.GetPositionTopLeft(), card.GetPositionBottomRight());
#endif

//    qDebug() << "SlotShowTheCardInCentre() cardPositionTopLeft = " << card.GetPositionTopLeft();
//    qDebug() << "SlotShowTheCardInCentre() positionBottomRight = " << card.GetPositionBottomRight();

    _cardPointer->setUpTriangleCardPointer(card.GetPositionTopLeft(), card.GetPositionBottomRight());
    _cardPointer->show(card.GetPositionTopLeft(), card.GetPositionBottomRight());
}

void The_Game::SlotShowTheCardInGameInspector(PositionedCard card)
{
    ui->wdgt_CardInspector->SlotSetUpSimpleCardToShow(card);
}


void The_Game::SlotHideTheCardInCentre(bool)
{
    _popUpCardWidget->hideAnimation();
    _cardPointer->hideAnimation();
}

void The_Game::SetIsRoomMaster(bool master)
{
    _isRoomMaster = master;
    if (master)
        ui->MainGamer->SetIsRoomMaster();
}

GamePhase The_Game::GetCurrentGamePhase() const
{
    return _currentGamePhase;
}

void The_Game::SetCurrentGamePhase(const GamePhase &currentGamePhase)
{
    _currentGamePhase = currentGamePhase;
}

void The_Game::SlotAdjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace()
{
    ui->MainGamer->adjustSize();
}

void The_Game::SlotCheckThePossibilityForTheCardToBePlayed(PositionedCard card)
{
    qDebug() << "The Card is checking!!!";

    //check, first of all, what is the phase of the Game;
    //If the Phase is "WaitingForAnOpponentToMove", it is not possible to use any cards;
    //Even "Annihilation"

    if ((_currentGamePhase == GamePhase::GameInitialization)
            || (_currentGamePhase == GamePhase::WaitingForAnOpponentToMove)
            || (_currentGamePhase == GamePhase::Theft)
            || (_currentGamePhase == GamePhase::HandAlignment)
            || (_currentGamePhase == GamePhase::AfterOpenDoorNoMonster)
            || (_currentGamePhase == GamePhase::Diplomacy))
    {
        qDebug() << "The Game is in Phase when it is not possible to use cards!";

        emit SignalCardIsRejectedToBePlayed(true);

        //show the Rejection Message for the Card
        SlotShowTheRejectedCardMessage(card);
    }
    else
    {

        //testing
        DEBUGPassTheCardToTheBattleField(card);
        emit SignalCardIsRejectedToBePlayed(false);
    }
}

void The_Game::SlotServerReportsTheGameIsAboutToStart(const TheGameIsAboutToStartData &data)
{
    //Set Players Order;
    _playersOrder = data.playersOrder;

    qDebug() << "NAY-001: Checking playersOrder";
    if (!data.playersOrder.size())
    {
        qDebug() << "NAY-002: ERROR: No players given in SlotServerReportsTheGameIsAboutToStart(). "
                    "Game will not start!" ;
        return;
    }
    qDebug() << "NAY-002: Checking playersOrder Successfull!";

    for (uint32_t var = 1; var < data.playersOrder.size(); ++var)
        qDebug() << "NAY-001: cleint # " << var << " " << data.playersOrder[var];

    //Set Up Players And Widgets
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    SetUpPlayersAndWidgets(HW_Screen_Size.height(), HW_Screen_Size.width(), data.playersOrder);
    PassCardsToWidgets();

    //Set players order for battlefield
    ui->GameField->setPlayersOrder(_playersOrder);

    //Form initial decks
    //NAY-002: REWORK
    //Переделать формирование колод, так, чтобы каждый клиент получал свои карты.
    //И тот, кто НЕ мастер получал свои.
    //Т.е. выдавать в порядке очереди. :)
    FormingInitialDecks(data.positionsDoors, data.positionsTreasures);
    GivingCardsToPlayers();
    ShowInitialCardsOnHands();
    ui->GameField->InitializeStartUpProcedureVisualization();
    showFullScreen();
}

void The_Game::SlotShowTheRejectedCardMessage(PositionedCard card)
{
//    _rejectionCardMessage->setPopupText("The Card Can not be played \n"
//                                        "Now!");
    _rejectionCardMessage->setPopupText("Сейчас нельзя сыграть \n"
                                        "эту карту!");
    _rejectionCardMessage->show(card.GetPositionTopLeft(), card.GetPositionBottomRight());
    _handCardPointer->setUpHandCardPointer(card.GetPositionTopLeft(), card.GetPositionBottomRight());
    _handCardPointer->show(card.GetPositionTopLeft(), card.GetPositionBottomRight());

}

void The_Game::DEBUGPassTheCardToTheBattleField(PositionedCard card)
{
    QPushButton* _movingCard = new QPushButton("Animated Button", this);
    _movingCard->move(card.GetPositionTopLeft().x(), card.GetPositionTopLeft().y());
     int sizeX = card.GetPositionBottomRight().x() - card.GetPositionTopLeft().x() ;
     int sizeY = card.GetPositionBottomRight().y() - card.GetPositionTopLeft().y();

    qDebug() << "Size of the Card during moving: X: " << sizeX;
    qDebug() << "Size of the Card during moving: Y: " << sizeY;

    QString picture = findTheCardPicture(card.GetCard());

    QPixmap pxmp_movingCard(picture);
    QPalette plte_movingCard;
    plte_movingCard.setBrush(_movingCard->backgroundRole(),
    QBrush(pxmp_movingCard.scaled(sizeX*2, sizeY*2, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    _movingCard->setMaximumWidth(sizeX*2);
    _movingCard->setMaximumHeight(sizeY*2);
    _movingCard->setMinimumWidth(sizeX);
    _movingCard->setMinimumHeight(sizeY);

    //http://www.prog.org.ru/topic_7215_0.html
    _movingCard->setFlat(true);
    _movingCard->setAutoFillBackground(true);
    _movingCard->setPalette(plte_movingCard);
    _movingCard->setText("");
    //_movingCard->installEventFilter(this);
    _movingCard->show();

    QPropertyAnimation *animation = new QPropertyAnimation(_movingCard, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(card.GetPositionTopLeft().x(), card.GetPositionTopLeft().y(), sizeX, sizeY));
    animation->setEndValue(QRect(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2));
    animation->setEasingCurve(QEasingCurve::OutCubic);

    //setWindowFlags(Qt::CustomizeWindowHint);

    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation, &QPropertyAnimation::finished,
            _movingCard, &QPushButton::deleteLater);

    //Соединить этот сигнал со слотом, который добавляет карту на поле боя.
    connect(animation, &QPropertyAnimation::finished, [this, card] {SlotAddPlayedCardToTheBattleField(card.GetCard());});

    //_movingCard->deleteLater();
}

QString The_Game::findTheCardPicture(SimpleCard card)
{
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

    QString currentPictureAddress;
    bool isFound = false;
    if (!card.first) { //door

        _monstersIterator = _monstersDeck.find(static_cast <int> (card.second));
        if (_monstersIterator != _monstersDeck.end()) {
            currentPictureAddress = (*_monstersIterator).second.pictureAddress();
            isFound = true;
        }
        if (!isFound) {
            _amplifiersIterator = _amplifiersDeck.find(static_cast <int> (card.second));
            if (_amplifiersIterator != _amplifiersDeck.end()) {
                currentPictureAddress = (*_amplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _cursesIterator = _cursesDeck.find(static_cast <int> (card.second));
            if (_cursesIterator != _cursesDeck.end()) {
                currentPictureAddress = (*_cursesIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _professionsIterator = _professionsDeck.find(static_cast <int> (card.second));
            if (_professionsIterator != _professionsDeck.end()) {
                currentPictureAddress = (*_professionsIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _racesIterator = _racesDeck.find(static_cast <int> (card.second));
            if (_racesIterator != _racesDeck.end()) {
                currentPictureAddress = (*_racesIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _specialMechanicsIterator = _specialMechanicsDeck.find(static_cast <int> (card.second));
            if (_specialMechanicsIterator != _specialMechanicsDeck.end()) {
                currentPictureAddress = (*_specialMechanicsIterator).second.pictureAddress();
                isFound = true;
            }
        }
    }
    else { //treasure


        _armorIterator = _armorDeck.find(static_cast <int> (card.second));
        if (_armorIterator != _armorDeck.end()) {
            currentPictureAddress = (*_armorIterator).second.pictureAddress();
            isFound = true;
        }
        if (!isFound) {
            _armorAmplifiersIterator = _armorAmplifiersDeck.find(static_cast <int> (card.second));
            if (_armorAmplifiersIterator != _armorAmplifiersDeck.end()) {
                currentPictureAddress = (*_armorAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _battleAmplifiersIterator = _battleAmplifiersDeck.find(static_cast <int> (card.second));
            if (_battleAmplifiersIterator != _battleAmplifiersDeck.end()) {
                currentPictureAddress = (*_battleAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _levelUpIterator = _levelUpDeck.find(static_cast <int> (card.second));
            if (_levelUpIterator != _levelUpDeck.end()) {
                currentPictureAddress = (*_levelUpIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
            if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end()) {
                currentPictureAddress = (*_specialMechanicsTreasureIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
            if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end()) {
                currentPictureAddress = (*_thingsAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
            if (_weaponsIterator != _weaponsDeck.end()) {
                currentPictureAddress = (*_weaponsIterator).second.pictureAddress();
                isFound = true;
            }
        }
    }
    return currentPictureAddress;
}

GameSettings The_Game::gameSettings() const
{
    return _gameSettings;
}

void The_Game::setGameSettings(const GameSettings &gameSettings)
{
    _gameSettings = gameSettings;
}

void The_Game::SlotProcessServerReportsRoomHasChangedOwner(const QString &previousOwner, const QString &currentOwner)
{
    //Если игра уже в процессе, удалить игрока из игры!
    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
    {
        if (_playersOrder[var] == previousOwner)
        {
            qDebug() << "NAY-002 : SlotProcessServerReportsRoomHasChangedOwner() Remove Player from order! (FOR FUTHER PROCESSING!) " << previousOwner;
            _playersOrder.erase(_playersOrder.begin() + var);
            _playersOrder.shrink_to_fit();
            //С этого момента игра начнёт просто пропускать его ходы

            if (_playersOrder[0] != currentOwner)
            {
                qDebug() << "NAY-002 : Error while SlotProcessServerReportsRoomHasChangedOwner(). Current owner not equal to the one it should be."
                            "Check Logic!";
            }
            emit SignalRoomHasChangedOwner(QStringList{previousOwner, currentOwner});
            return;
        }
        qDebug() << "NAY-002: Error while SlotProcessServerReportsRoomHasChangedOwner() Previous Master Not found! "
                 << "Previous owner: " << previousOwner
                 << "Current owner: " << currentOwner;
    }
}

void The_Game::SlotGameInitialization(TheGameIsAboutToStartData data)
{
    //1. Initialize cards;
    FormingInitialDecks(data.positionsDoors, data.positionsTreasures);

    //2. Redraw GUI regarding current GameSettings

}

void The_Game::SlotSetUpGameSettings(const GameSettings &settings)
{
    _gameSettings.applyNewSettings(settings);
    ui->GameField->ApplyNewSettings(settings);
}

void The_Game::SlotInitialAnimationCompleted()
{
    RealGameStart();
}

void The_Game::FormingInitialDecks(const std::vector<uint32_t> &doorsVector, const std::vector<uint32_t> &treasuresVector)
{
    //Given vectors are the numbers in order to place in the stacks (Formed by the server!)

    uint32_t totalTreasures = _armorDeck.size() + _armorAmplifiersDeck.size() + _battleAmplifiersDeck.size() + _levelUpDeck.size() +
            _specialMechanicsTreasureDeck.size() + _thingsAmplifiersDeck.size() + _weaponsDeck.size();

    uint32_t totalDoors = _monstersDeck.size() + _amplifiersDeck.size() + _cursesDeck.size() + _professionsDeck.size() +
            _racesDeck.size() + _specialMechanicsDeck.size();

    //NAY-001: MARK_EXPECTED_ERROR
    //These sizes ARE USED AS DEFINES ON SERVER SIDE.
    //HERE TO CHECK AND THROW AN EXCEPTION IF THEY ARE NOT CORRECT
    //I do not want to place all the code on the server's side - with cards and so on;
    //This data should be given by master to the server while passing settings
    //(Not visible to user)
    if ((totalDoors != doorsVector.size()) || (totalTreasures != treasuresVector.size()))
    {
        qDebug() << "ERROR while assigning random digits to cards. Rework the procedure!";
        throw "CARDS VECTORS BAD SIZES!";
    }
    //SHOULDN'T HANDLE THIS EXCEPTION

   if (!totalTreasures)
   {
       qDebug() << "Error during Treasures Stack Initialization. Stack is Empty! ";
       throw "CARDS VECTORS BAD SIZES!";
   }
   qDebug() << "NAY-001: Size of Treasures Stack Report: " << totalTreasures;

   if (!totalDoors)
   {
       qDebug() << "Error during Doors Stack Initialization. Stack is Empty! ";
       throw "CARDS VECTORS BAD SIZES!";
   }
   qDebug() << "NAY-001: Size of Doors Stack Report: " << totalDoors;


    for (unsigned int var = 0; var < totalTreasures; ++var)
    {
        _treasuresDeck.push_back({true,treasuresVector[var]});
    }

    qDebug() << "NAY-001: Treasures Stack is Filled Now!";

    for (unsigned int var = 0; var < totalDoors; ++var)
    {
        _doorsDeck.push_back({false,doorsVector[var]});
    }

    qDebug() << "NAY-001: Doors Stack is Filled Now!";

}

void The_Game::SetUpPlayersAndWidgets(uint32_t windowHeight, uint32_t windowWidth, const std::vector<QString> &playersNames)
{
    uint32_t totalOpponents = _gameSettings.maximumNumberOfPlayers();
    qDebug() << "Total players from settings: " << totalOpponents;
    qDebug() << "Total players given by SetUp Opponents: " << playersNames.size();

    _mainPlayer = new Player(_gameSettings.clientName());
    _roomMasterName = _playersOrder[0];
    SetIsRoomMaster(CheckIsMainPlayerTheRoomMaster(_playersOrder[0]));
    qDebug() << "NAY-001: Master's name: " << playersNames[0];
    //Set Players name:

    if (totalOpponents != playersNames.size())
        qDebug() << "ERROR while The_Game::SetUpOpponents(): Total opponents from settings"
                    "and given by server differs!";

    //Один из них может быть мастером!
    for (uint32_t var = 0; var < playersNames.size(); ++var)
    {
        if (_gameSettings.clientName() != playersNames[var])
        {
            Player* currentPlayer = new Player (playersNames[var]);
            _playersOpponents.push_back(currentPlayer);
            qDebug() << "NAY-002: _playersOpponents Size: " << _playersOpponents.size();
        }
    }

    //widgets for them
    for (uint32_t var = 0; var < playersNames.size(); var++)
    {

       if (_gameSettings.clientName() != playersNames[var])
       {
            _widgets4Opponents.push_back(new GamerWidget);
            _widgets4Opponents.back()->redraw_as_a_secondary_player();
            _widgets4Opponents.back()->setIs_MainPlayer(false);
            if (playersNames[var] == _roomMasterName)
                _widgets4Opponents.back()->SetIsRoomMaster();
       }

    }
    //first two of them to the top layout
    //fixed numbers, they are allways there
    //other three on the left side.
    //For debug there should be only 1 of opponents;

    for (uint32_t var = 0; var < _widgets4Opponents.size(); ++var)
    {
        ui->top_opponents_layout->addWidget(_widgets4Opponents[var]);
    }
    //if there is(are) some other players, add them to the right_side layout
    if (totalOpponents > 2)
    {
        for (uint32_t i = 0; i < totalOpponents - 3; i++)
            ui->right_side_opponents_layout->addWidget(_widgets4Opponents[2+i]);
    }

    //resizing 'em all
    for (uint32_t j = 0; j < totalOpponents - 1; j++)
    {
        _widgets4Opponents[j]->setMinimumHeight(koeff_GamerWidget_size_Height*windowHeight);
        _widgets4Opponents[j]->setMaximumHeight(koeff_GamerWidget_size_Height*windowHeight);
        _widgets4Opponents[j]->setMaximumWidth((koeff_GamerWidget_size_Width+SecondaryGamerWidgetWidthExpansion)*windowWidth);
    }

#ifdef DEBUG_NO_SERVER

    for (unsigned int var = 0; var < _widgets4Opponents.size(); ++var)
    {
        connect(_widgets4Opponents[var], &GamerWidget::SignalRepresentTheCardInCentre, this, &The_Game::SlotShowTheCardInCentre);
        connect(_widgets4Opponents[var], &GamerWidget::SignalHideTheCardInCentre, this, &The_Game::SlotHideTheCardInCentre);
    }

#endif
}

void The_Game::SetUpWidgetsProperties(uint32_t windowHeight, uint32_t windowWidth)
{
    //setting up the GUI staff
    //Defining its coefficients with respect to the total size of availible field;

#ifdef DEBUG_NO_RETURN_TO_MENU
    ui->btn_switch_back->hide();
#endif

    //setting MainGamer
    ui->MainGamer->setIs_MainPlayer(true);
    //hide Secondary Hand Widget;
    ui->MainGamer->HideHandSecondaryPlayerWidget();

    ui->GameField->setMinimumWidth(koeff_GameField_size*windowWidth);
    ui->GameField->setMinimumHeight(koeff_GameField_size*windowHeight);

    ui->MainGamer->setMinimumHeight(koeff_GamerWidget_size_Height*windowHeight);

    ui->btn_switch_back->setMinimumWidth(koeff_GameInfoBox_size_Width*windowWidth);
    ui->btn_switch_back->setMaximumWidth(koeff_GameInfoBox_size_Width*windowWidth);

    //trying to disable the maximum size of the MainGamerHeight
    //ui->MainGamer->setMaximumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);

    //with respect to the MainGamer, the height size won't be larger then allowed,
    //but may take all the availible space if the width is concerned; Why not?
    ui->MainGamer->setMinimumWidth(koeff_GamerWidget_size_Width*windowWidth);
    ui->MainGamer->setMaximumWidth((koeff_GamerWidget_size_Width+MainGamerWidgetWidthExpansion)*windowWidth);

    ui->TimersWidget->setMinimumHeight(koeff_GameTimers_size_Height*windowHeight);
    ui->TimersWidget->setMaximumHeight(koeff_GameTimers_size_Height*windowHeight);

    ui->wdgt_Chart->setMinimumWidth(koeff_GameTimers_size_Width*windowWidth);
    ui->wdgt_Chart->setMaximumWidth(koeff_GameTimers_size_Width*windowWidth);

}


void The_Game::SetUpOpponents(uint32_t windowHeight, uint32_t windowWidth, const std::vector<QString>& opponents)
{


}

void The_Game::MainParser()
{
#ifndef USE_RESOURCES

    theMonstersParser("Tables/cards_doors_monsters.csv");
    qDebug() << "Monsters parsing complete!";

    theAmplifiersParser("Tables/cards_doors_amplifiers.csv");
    qDebug() << "Amplifiers parsing complete!";

    theCursesParser("Tables/cards_doors_curses.csv");
    qDebug() << "Curses parsing complete!";

    theProfessionsParser("Tables/cards_doors_professions.csv");
    qDebug() << "Professions parsing complete!";

    theRacesParser("Tables/cards_doors_races.csv");
    qDebug() << "Races parsing complete!";

    theSpecialMechanicsParser("Tables/cards_doors_specialmechanics.csv");
    qDebug() << "Special mechanics parsing complete!";

    theArmorsParser("Tables/cards_treasures_armor.csv");
    qDebug() << "Armor parsing complete!";

    theArmorAmplifiersParser("Tables/cards_treasures_armorAmplifiers.csv");
    qDebug() << "ArmorAmplifiers parsing complete!";

    theBattleAmplifiersParser("Tables/cards_treasures_battleAmplifiers.csv");
    qDebug() << "BattleAmplifiers parsing complete!";

    theLevelUpParser("Tables/cards_treasures_levelUp.csv");
    qDebug() << "LevelUps parsing complete!";

    theSpecialMechanicTreasureParser("Tables/cards_treasures_specialMechanics.csv");
    qDebug() << "SpecialMechanicsTreasures parsing complete!";

    theThingsAmplifiersParser("Tables/cards_treasures_thingsAmplifiers.csv");
    qDebug() << "ThingsAmplifiers parsing complete!";

    theWeaponParser("Tables/cards_treasures_Weapon.csv");
    qDebug() << "Weapons parsing complete!";

#else
    theMonstersParser(":/Tables/cards_doors_monsters.csv");
    qDebug() << "Monsters parsing complete!";

    theAmplifiersParser(":/Tables/cards_doors_amplifiers.csv");
    qDebug() << "Amplifiers parsing complete!";

    theCursesParser(":/Tables/cards_doors_curses.csv");
    qDebug() << "Curses parsing complete!";

    theProfessionsParser(":/Tables/cards_doors_professions.csv");
    qDebug() << "Professions parsing complete!";

    theRacesParser(":/Tables/cards_doors_races.csv");
    qDebug() << "Races parsing complete!";

    theSpecialMechanicsParser(":/Tables/cards_doors_specialmechanics.csv");
    qDebug() << "Special mechanics parsing complete!";

    theArmorsParser(":/Tables/cards_treasures_armor.csv");
    qDebug() << "Armor parsing complete!";

    theArmorAmplifiersParser(":/Tables/cards_treasures_armorAmplifiers.csv");
    qDebug() << "ArmorAmplifiers parsing complete!";

    theBattleAmplifiersParser(":/Tables/cards_treasures_battleAmplifiers.csv");
    qDebug() << "BattleAmplifiers parsing complete!";

    theLevelUpParser(":/Tables/cards_treasures_levelUp.csv");
    qDebug() << "LevelUps parsing complete!";

    theSpecialMechanicTreasureParser(":/Tables/cards_treasures_specialMechanics.csv");
    qDebug() << "SpecialMechanicsTreasures parsing complete!";

    theThingsAmplifiersParser(":/Tables/cards_treasures_thingsAmplifiers.csv");
    qDebug() << "ThingsAmplifiers parsing complete!";

    theWeaponParser(":/Tables/cards_treasures_Weapon.csv");
    qDebug() << "Weapons parsing complete!";
#endif
}

void The_Game::SetUpSignalSlotsConnections()
{
    QObject::connect(ui->btn_switch_back, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(this, &The_Game::DEBUG_SignalToBeShown, this, &The_Game::showFullScreen);//SLOT(showFullScreen())) SLOT(show();
    QObject::connect(ui->btn_switch_back, SIGNAL(clicked(bool)), this, SLOT(dbg_return_to_the_main_window()));

    //Setting the in-Game connections with other Widgets
    connect(ui->MainGamer, &GamerWidget::SignalRepresentTheCardInCentre, this, &The_Game::SlotShowTheCardInCentre);
    connect(ui->MainGamer, &GamerWidget::SignalRepresentTheCardInCentre, this, &The_Game::SlotShowTheCardInGameInspector);
    connect(ui->MainGamer, &GamerWidget::SignalHideTheCardInCentre, this, &The_Game::SlotHideTheCardInCentre);

    //trying to adjust the size of...
    connect(ui->MainGamer, &GamerWidget::SignalAdjustSize, this, &The_Game::SlotAdjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace);

    //connect theHand with checking the card slot;
    connect(ui->MainGamer, &GamerWidget::SignalSendTheCardToTheGameCheck, this, &The_Game::SlotCheckThePossibilityForTheCardToBePlayed);
    //pass the answer form The_Game card check back to the Hand
    connect(this, &The_Game::SignalCardIsRejectedToBePlayed, ui->MainGamer, &GamerWidget::SlotCardIsRejectedToBePlayed);

    QObject::connect(this, &The_Game::SignalChartMessageReceived, ui->wdgt_Chart, &MunchkinDialog::SlotShowMessage);
    QObject::connect(ui->wdgt_Chart, &MunchkinDialog::SignalSendMessage, this, &The_Game::SlotProcessChartMessageSending);
    QObject::connect(ui->GameField, &battleField::SignalStartUpAnimationCompleted, this, &The_Game::SlotInitialAnimationCompleted);

    connect(ui->MainGamer, &GamerWidget::SignalTradeButtonWasPressed, this, &The_Game::SlotShowTradeMenu);

    connect(this, &The_Game::SignalShowTradeButton, ui->MainGamer, &GamerWidget::SlotShowTradeButton);
    connect(this, &The_Game::SignalHideTradeButton, ui->MainGamer, &GamerWidget::SlotHideTradeButton);
}

void The_Game::InitializePopUpWidgets()
{
    //create popUpCard Widget
    _popUpCardWidget = new PopUpCard(this);
    //create CardPointerWidget
    _cardPointer = new TriangleCardPointer();

    _rejectionCardMessage = new RejectedCardMessage();
    _handCardPointer = new HandCardPointer();

}

void The_Game::SetUpBackgroundPicture()
{

#ifndef USE_RESOURCES
    QPixmap pxmpBattleField("Pictures/JorneyCover.png");
#else
    QPixmap pxmpBattleField(":/Pictures/JorneyCover.png");
#endif
    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

    QPalette plte_battleField;
    plte_battleField.setBrush(QPalette::Background, QBrush(pxmpBattleField.scaled(HW_Screen_Size.width(),HW_Screen_Size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    setPalette(plte_battleField);
    setAutoFillBackground(true);

}

void The_Game::PassCardsToWidgets()
{
    PassDecksToBattleField();
    passDecksToPlayerWidgets();
    PassDecksToCardsInspectorWidget();
    PassDecksToPopUpCardWidget();
    PassDecksToCardsStacksWidget();
}

void The_Game::SlotShowTradeMenu()
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

    _sellMenu = new SellMenu(AllDecksToBePassed(
                                 _monstersDeck,
                                 _amplifiersDeck,
                                 _cursesDeck,
                                 _professionsDeck,
                                 _racesDeck,
                                 _specialMechanicsDeck,

                                 _armorDeck,
                                 _armorAmplifiersDeck,
                                 _battleAmplifiersDeck,
                                 _levelUpDeck,
                                 _specialMechanicsTreasureDeck,
                                 _thingsAmplifiersDeck,
                                 _weaponsDeck),
                                QSize(HW_Screen_Size.width(),
                                      HW_Screen_Size.height()),
                                _cardsToBeSelledHolder);

    _sellMenu->show();

    connect(_sellMenu, &SellMenu::SignalUserClosedTradeMenu, this, &The_Game::SlotHideTradeMenu);
    connect(_sellMenu, &SellMenu::SignalReportCardsToBeSold, this, &The_Game::SlotProcessCardsSelectedToBeSold);

}

void The_Game::SlotHideTradeMenu()
{
    qDebug() << "NAY-002: Closing Trade Menu in The_Game: ";
    if (_sellMenu != nullptr)
        _sellMenu->deleteLater();
}

void The_Game::SlotProcessCardsSelectedToBeSold(const std::vector<SimpleCard> cards)
{
    //1. Удалить карты с руки
    //2. Проверить и убрать в случае необходимости кнопку "Торговля"
    //3. Добавить уровень//уровни
    qDebug() << "NAY-002: In the SlotProcessCardsSelectedToBeSold() ";
    qDebug() << "NAY-002: CardsToBeSold size " << cards.size();

    //1.1. Для этого сначала получить их позиции
    std::vector<PositionedCard> posCards = GetPositionedCards(cards);
    for (uint32_t var = 0; var < posCards.size(); ++var)
    {
        qDebug() << "NAY-002: PosCard id " << posCards[var].GetCard().second
                 << " pos top left: " << posCards[var].GetPositionTopLeft()
                 << " pos bottom right: " << posCards[var].GetPositionBottomRight();
    }
}

std::vector<PositionedCard> The_Game::GetPositionedCards(const std::vector<SimpleCard> &cards)
{
    return ui->MainGamer->GetPositionedCards(cards);
}

void The_Game::SlotAddPlayedCardToTheBattleField(SimpleCard card)
{

}

bool The_Game::CheckThePlayerIsAbleToSell(Player* player)
{
    qDebug() <<"NAY-002: Entering AbleToSell Checker";
    std::vector<SimpleCard> sumChecker;
    std::vector<SimpleCard> cardsOnHands = player->GetCardsOnHands();
    std::vector<SimpleCard> cardsInGame = player->GetCardsInGame();


    for (uint32_t var = 0; var < cardsOnHands.size(); ++var)
    {
        if (cardsOnHands[var].first)
            sumChecker.push_back(cardsOnHands[var]);
    }
    for (uint32_t var = 0; var < cardsInGame.size(); ++var)
    {
        if (cardsInGame[var].first)
            sumChecker.push_back(cardsInGame[var]);
    }

    uint32_t totalSumOfAllTheCards = 0;

    for (uint32_t var = 0; var < sumChecker.size(); ++var)
    {
        totalSumOfAllTheCards += GetCardPrice(sumChecker[var]);
        if (GetCardPrice(sumChecker[var]))
            _cardsToBeSelledHolder.push_back(sumChecker[var]);
    }
    qDebug() << "NAY-002: Total Price of all the cards the player has: " << totalSumOfAllTheCards;

    if (totalSumOfAllTheCards >= 1000)
    {
        emit SignalShowTradeButton();
        return true;
    }
    return false;
}

uint32_t The_Game::GetCardPrice(SimpleCard card)
{
    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    if (!card.first)
        throw "NAY-002: Error During CheckCardPrice(). Doors have no prices!";

    _armorIterator = _armorDeck.find(static_cast <int> (card.second));
    if (_armorIterator != _armorDeck.end())
        return static_cast<uint32_t>((*_armorIterator).second.price());

    _armorAmplifiersIterator = _armorAmplifiersDeck.find(static_cast <int> (card.second));
    if (_armorAmplifiersIterator != _armorAmplifiersDeck.end())
        return 0;

    _battleAmplifiersIterator = _battleAmplifiersDeck.find(static_cast <int> (card.second));
    if (_battleAmplifiersIterator != _battleAmplifiersDeck.end())
        return 0;


     _levelUpIterator = _levelUpDeck.find(static_cast <int> (card.second));
    if (_levelUpIterator != _levelUpDeck.end())
        return 0;

    _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
    if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end())
        return static_cast<uint32_t>((*_specialMechanicsTreasureIterator).second.price());


    _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
    if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
        return static_cast<uint32_t>((*_thingsAmplifiersIterator).second.price());


    _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
    if (_weaponsIterator != _weaponsDeck.end())
        return static_cast<uint32_t>((*_weaponsIterator).second.price());

    qDebug() << "NAY-002: Error During CheckCardPrice(). Card Not Found!!!";
    return 0;
}

void The_Game::RealGameStart()
{
    qDebug() << "NAY-002 : RealGameStart()!";

    if (_gameSettings.clientName() == _playersOrder[0])
    {
        InitializeMainPlayerMove();
        StartMoveTimer();
        StartPhaseTimer(GetCurrentGamePhase());
    }

    else
    {
        InitializeOpponentMove(_playersOrder[0]);
        StartMoveTimer();

        //In fact, while another player is acting,
        //It is necessary to set correct GamePhase
        StartPhaseTimer(GamePhase::StartOfTheMove);
    }

}

void The_Game::InitializeMainPlayerMove()
{

//    1. Вор может воровать в любой* момент, когда он и его жертва не в бою.
//    это есть в ФАКе http://munchkinizm.narod.ru/FAQ/index.htm#q0710

//    2. Вводить в игру постоянные шмотки ты можешь в любой* момент своего хода,
//       когда ты не в бою, либо при получении этой карты, когда ты не в бою
//       (например после боя, в котором ты был помощником).
//    Все манипуляции с сыгранными шмотками, то есть смена своей экипировки,
//                                           то есть снять (убрать в "рюкзак") одно и надеть
//      (достать из "рюкзака") другое, а так же обмен шмотками с другими игроками, это в любой* момент,
//                                     когда ты не в бою (при обмене второй игрок тоже должен быть не в бою,
//                                                        разумеется).
//      Продавать шмотки за уровень можно в любой* момент своего хода, когда ты не в бою.

//    * любой момент игры - это любой момент, когда это не прерывает какое-либо другое действие.
//                                                                     например нельзя ничего делать
//                                                                     (кроме специально предусмотренных
//                                                                      для таких ситуаций действий),
//        пока игрок разбирается с эффектом проклятия или непотребства, или пока он роется в сбросе,
//        сыграв Штырь Лозоходца, или пока Вор пытается украсть шмотку и т.п.


    //1. Стартовать основной таймер
    //2. Стартовать таймер фазы
    //3. Провероить вор/не вор
    //  3.1 Если вор, включить функцию "своровать"
    //  3.2 Если не вор, далее
    //
    //4. Проверить, может ли игрок торговать
    //5. Если может,
    //5.1  Разрешить торговлю (торговля будет разрешена до начала боя, и после победы - "свой ход")
    //5.2  Разрешить сыграть монстра с руки
    //5.3  Разрешить сыграть монстра из колоды

    SetCurrentGamePhase(GamePhase::StartOfTheMove);

    if (CheckThePlayerIsAbleToSell(_mainPlayer))
        qDebug() << "NAY-001: The player is able to sell!";
}

void The_Game::InitializeOpponentMove(const QString &opponentsName)
{
    SetCurrentGamePhase(GamePhase::OtherPlayerMove);
    qDebug() << "NAY-002: Other PlayerMove!";
}

void The_Game::StartMoveTimer()
{
    _secondsLeftMoveTimer = _gameSettings.totalTimeToMove();
    _secondsMoveTimer->start();
    _moveTimer->setInterval(1000* static_cast<int32_t>(_gameSettings.totalTimeToMove()));
    _moveTimer->start();
}

void The_Game::StartPhaseTimer(GamePhase phase)
{
    switch (phase)
    {

    case GamePhase::StartOfTheMove:
    {
        _secondsLeftPhaseTimer = _gameSettings.timeToThink();
        _phaseTimer->setInterval(static_cast<int32_t>(1000*_gameSettings.timeToThink()));
        _secondsPhaseTimer->start();
        _phaseTimer->start();
    }
        break;

    case GamePhase::Diplomacy:
    {
        _secondsLeftPhaseTimer = _gameSettings.diplomacyTime();
        _phaseTimer->setInterval(static_cast<int32_t>(1000*_gameSettings.diplomacyTime()));
        _secondsPhaseTimer->start();
        _phaseTimer->start();
    }
        break;

    case GamePhase::AfterBattleWin:
    {
        _secondsLeftPhaseTimer = _gameSettings.timeForOpponentsDecision();
        _phaseTimer->setInterval(static_cast<int32_t>(1000*_gameSettings.timeForOpponentsDecision()));
        _secondsPhaseTimer->start();
        _phaseTimer->start();
    }
        break;

    default:
        qDebug() << "StartPhaseTimer() :: Error while setting timer! Incorrect phase.";
       break;
    }
}

void The_Game::InitializeTicksTimers()
{
    _secondsMoveTimer = new QTimer(this);
    _secondsPhaseTimer = new QTimer(this);
    _secondsMoveTimer->setInterval(1000);
    _secondsPhaseTimer->setInterval(1000);
    _secondsMoveTimer->setSingleShot(true);
    _secondsPhaseTimer->setSingleShot(true);

    ui->GameField->SetTimeLeftMoveTimer(_gameSettings.totalTimeToMove());
    ui->GameField->SetTimeLeftPhaseTimer(_gameSettings.timeToThink());


    connect(_secondsMoveTimer, &QTimer::timeout, this, &The_Game::SlotSecondsMoveTimerHandler);
    connect(_secondsPhaseTimer, &QTimer::timeout, this, &The_Game::SlotSecondsPhaseTimerHandler);
}

void The_Game::InitializeMoveTimer()
{
    _moveTimer = new QTimer(this);
    _moveTimer->setSingleShot(true);
    //here to connect the Handler!
    connect(_moveTimer, &QTimer::timeout, this, &The_Game::SlotMoveTimerHandler);

}

void The_Game::InitializePhaseTimer()
{
    _phaseTimer = new QTimer(this);
    _phaseTimer->setSingleShot(true);
    connect(_phaseTimer, &QTimer::timeout, this, &The_Game::SlotPhaseTimerHandler);
}

void The_Game::SlotMoveTimerHandler()
{
    qDebug() << "NAY-002: MoveTimer timeout!";
}

void The_Game::SlotPhaseTimerHandler()
{
    qDebug() << "NAY-002:: PhaseTimer timeout!";
}

void The_Game::SlotSecondsMoveTimerHandler()
{
    --_secondsLeftMoveTimer;
    ui->GameField->SetTimeLeftMoveTimer(_secondsLeftMoveTimer);
    if (_secondsLeftMoveTimer)
        _secondsMoveTimer->start();
}

void The_Game::SlotSecondsPhaseTimerHandler()
{
    --_secondsLeftPhaseTimer;
    ui->GameField->SetTimeLeftPhaseTimer(_secondsLeftPhaseTimer);
    if (_secondsLeftPhaseTimer)
        _secondsPhaseTimer->start();
}

unsigned int The_Game::doorsLeft() const
{
    return _doorsLeft;
}

void The_Game::setDoorsLeft(unsigned int doorsLeft)
{
    _doorsLeft = doorsLeft;
}

unsigned int The_Game::treasuresLeft() const
{
    return _treasuresLeft;
}

void The_Game::setTreasuresLeft(unsigned int treasuresLeft)
{
    _treasuresLeft = treasuresLeft;
}
