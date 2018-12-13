#include "Application/The_Game/The_Game.h"
#include "ui_the_game.h"
#include <ctime>
#include <QTime>
#include <ui_the_game.h>
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
    uint32_t HW_Screen_Size_Width = static_cast<uint32_t>(HW_Screen_Size.width());
    uint32_t HW_Screen_Size_Heigh = static_cast<uint32_t>(HW_Screen_Size.height());

    //Regarding this note
    //https://stackoverflow.com/questions/44875309/why-does-qdesktopwidget-give-me-the-wrong-available-geometry-when-i-use-two-moni
    //It is necessary to adjust size while using Linux internally.
    //make it 0.8 of height for example

#ifdef __linux
    static_cast<uint32_t>(HW_Screen_Size_Heigh *= 0.9);
    static_cast<uint32_t>(HW_Screen_Size_Width *= 0.8);
#endif
#ifdef Q_OS_WIN
    static_cast<uint32_t>(HW_Screen_Size_Heigh *= 0.9);
    static_cast<uint32_t>(HW_Screen_Size_Width *= 0.8);
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
    SetGamePhase(GamePhase::GameInitialization);

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

    theMonster.SetCardType(CardType::DoorMonster);

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

    theAmplifier.SetCardType(CardType::DoorAmplifier);

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

    theCurse.SetCardType(CardType::DoorCurse);

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

    theProfession.SetCardType(CardType::DoorProfession);

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

    theRace.SetCardType(CardType::DoorRace);

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

    theSpecialMechanic.SetCardType(CardType::DoorSpecialMechanic);

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
    theArmor.SetAdditionalBonusforElf(0);
    theArmor.SetAdditionalBonusforOrk(0);
    QStringList newLst = lst.first().split("_");
    if (newLst.first() == "Elf_2") theArmor.SetAdditionalBonusforElf(2);
    else if (newLst.first() == "Ork_2") theArmor.SetAdditionalBonusforOrk(2);
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

    theArmor.SetCardType(CardType::TreasureArmor);

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

    theArmorAmplifier.SetCardType(CardType::TreasureArmorAmplifier);

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
    lst.removeFirst();

    theBattleAmplifier.setPrice(static_cast<uint32_t>(lst.first().toInt()));

    theBattleAmplifier.SetCardType(CardType::TreasureBattleAmplifier);

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

    theLevelUp.SetCardType(CardType::TreasureLevelUp);

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

    theSpecialMechanic.SetCardType(CardType::TreasureSpecialMechanic);

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

    theThingAmplifier.SetCardType(CardType::TreasureThingAmplifier);

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

    theWeapon.SetCardType(CardType::TreasureWeapon);

    return theWeapon;
}

void The_Game::DEBUG_ShowAllTheCards()
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

void The_Game::PassDecksToPlayerWidgets()
{
    AllDecksToBePassed decks(_monstersDeck,
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
                             _weaponsDeck);

    ui->MainGamer->SetDecks(decks);
    ui->MainGamer->PassCardsDecksToHandsAndCardsInGameWidgets(decks);

    for (unsigned int var = 0; var < _widgets4Opponents.size(); ++var)
    {
        _widgets4Opponents[var]->SetDecks(decks);
        (_widgets4Opponents[var])->PassCardsDecksToHandsAndCardsInGameWidgets(decks);
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



void The_Game::AddCardToFoldStack(SimpleCard card)
{
    if (card.first)
        _treasuresFold.push_back(card);
    else
        _doorsFold.push_back(card);
}

void The_Game::ProcessFoldObserver(const std::vector<SimpleCard> foldedCards)
{
    QRect HW_Screen_Size = geometry();

    if (_foldObserver == nullptr)
    {
        _foldObserver = new LastFoldObserver(AllDecksToBePassed(
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
                                              foldedCards);
        emit SignalEnableFoldProcessButton();

        connect(ui->CardStacksWidget, &CardStacks::SignalFoldObserverButtonPressed,
                _foldObserver, &LastFoldObserver::show);

        connect(_foldObserver, &LastFoldObserver::SignalUserIsClosingLastFoldObserver,
                [this]{ _foldObserver->deleteLater();});
    }
    else
    {
        emit SignalDisableFoldProcessButton();

        _foldObserver->blockSignals(true);
        _foldObserver->close();
        _foldObserver->deleteLater();

        _foldObserver = new LastFoldObserver(AllDecksToBePassed(
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
                                              foldedCards);


        connect(ui->CardStacksWidget, &CardStacks::SignalFoldObserverButtonPressed,
                _foldObserver, &LastFoldObserver::show);

        connect(_foldObserver, &LastFoldObserver::SignalUserIsClosingLastFoldObserver,
                [this]{ _foldObserver->deleteLater();});

        emit SignalEnableFoldProcessButton();
    }

    _lastFold.clear();
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
    uint32_t cardsToGive = HardCodedSettingsLimitations::totalCardsToGiveFromTheStart;

    //then it is necessary to give m_number_of_players*4 cards from doors stack, and
    //the same quantity from the Treasures stack.

    //start with the main player... (giving cards from the top)

    uint32_t initialSizeDoors = _doorsDeck.size();
    uint32_t initialSizeTreasures = _treasuresDeck.size();

    qDebug() << "NAY-002: PlayersOrder size: " << _orderOfMove.size();
    if (_orderOfMove.size() != _playersOpponents.size() + 1)
        qDebug() << "NAY-002: ERROR WHILE void The_Game::GivingCardsToPlayers()"
                 << "orderOfMove.size() != _playersOpponents.size() + 1";

    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        for (unsigned int y = 0; y < cardsToGive; ++y)
        {
            _orderOfMove[var]->AddCardToHands(_doorsDeck.front());
            _doorsDeck.erase(_doorsDeck.begin());
        }
    }

    ui->CardStacksWidget->updateDoorsLeft(initialSizeDoors - cardsToGive*(_gameSettings.maximumNumberOfPlayers()));
    qDebug() << "Doors are given to the players!";

    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        for (uint32_t y = 0; y < cardsToGive; ++y)
        {
            _orderOfMove[var]->AddCardToHands(_treasuresDeck.front());
            _treasuresDeck.erase(_treasuresDeck.begin());
        }
    }

    ui->CardStacksWidget->updateTreasuresLeft(initialSizeTreasures - cardsToGive*_gameSettings.maximumNumberOfPlayers());
    qDebug() << "Treasures are given to the players!";

#endif
}

void The_Game::ShowInitialCardsOnHands()
{
    qDebug() << "showInitialCardsOnHands:: Started";
//    for (unsigned int var = 0; var < _mainPlayer->cardsOnHandsVector()->size(); ++var)
//    {
//        ui->MainGamer->addTheCardToHandsWidget(*((_mainPlayer->cardsOnHandsVector())->begin() + static_cast<int>(var)));
//    }

//    qDebug() << "NAY-002: _playersOpponents.size(): " << _playersOpponents.size();

//    for (unsigned int var = 0; var < _playersOpponents.size(); ++var)
//    {
//        unsigned int totalCardsToShow = _playersOpponents[var]->GetCardsOnHands().size();
//        std::vector<SimpleCard> cardsOnHands = _playersOpponents[var]->GetCardsOnHands();
//        for (unsigned int j = 0; j < cardsOnHands.size(); ++j)
//        {
//            _widgets4Opponents[var]->addTheCardToHandsWidget(cardsOnHands[j]);
//        }
//    }
//    qDebug() << "showInitialCardsOnHands:: Completed";


    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        std::vector<SimpleCard> cardsOnHands = _orderOfMove[var]->GetCardsOnHands();
        for (uint32_t y = 0; y < cardsOnHands.size(); ++y)
        {
            qDebug() << "NAY-002: " << "Showing Card with id: " << cardsOnHands[y].second;
            _GamerWidgetsWithIDs[var]->AddTheCardToHandsWidget(cardsOnHands[y]);
        }
    }
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

GameCardBasis The_Game::GetRealCard(SimpleCard card)
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


    if (!card.first)
    { //door
        _monstersIterator = _monstersDeck.find(static_cast <int> (card.second));
        if (_monstersIterator != _monstersDeck.end())
            return (*_monstersIterator).second;

        _amplifiersIterator = _amplifiersDeck.find(static_cast <int> (card.second));
        if (_amplifiersIterator != _amplifiersDeck.end())
            return (*_amplifiersIterator).second;

        _cursesIterator = _cursesDeck.find(static_cast <int> (card.second));
        if (_cursesIterator != _cursesDeck.end())
            return (*_cursesIterator).second;

        _professionsIterator = _professionsDeck.find(static_cast <int> (card.second));
        if (_professionsIterator != _professionsDeck.end())
            return (*_professionsIterator).second;

        _racesIterator = _racesDeck.find(static_cast <int> (card.second));
        if (_racesIterator != _racesDeck.end())
            return (*_racesIterator).second;

        _specialMechanicsIterator = _specialMechanicsDeck.find(static_cast <int> (card.second));
        if (_specialMechanicsIterator != _specialMechanicsDeck.end())
            return (*_specialMechanicsIterator).second;
    }
    else
    { //treasure
        _armorIterator = _armorDeck.find(static_cast <int> (card.second));
        if (_armorIterator != _armorDeck.end())
            return (*_armorIterator).second;

        _armorAmplifiersIterator = _armorAmplifiersDeck.find(static_cast <int> (card.second));
        if (_armorAmplifiersIterator != _armorAmplifiersDeck.end())
            return (*_armorAmplifiersIterator).second;

        _battleAmplifiersIterator = _battleAmplifiersDeck.find(static_cast <int> (card.second));
        if (_battleAmplifiersIterator != _battleAmplifiersDeck.end())
            return (*_battleAmplifiersIterator).second;

        _levelUpIterator = _levelUpDeck.find(static_cast <int> (card.second));
        if (_levelUpIterator != _levelUpDeck.end())
            return (*_levelUpIterator).second;

        _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
        if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end())
            return (*_specialMechanicsTreasureIterator).second;

        _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
        if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
            return (*_thingsAmplifiersIterator).second;

        _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
        if (_weaponsIterator != _weaponsDeck.end())
            return (*_weaponsIterator).second;

    }
    qDebug() << "NAY-002: Error while GameCardBasis The_Game::GetRealCard(SimpleCard card)"
             << "Card Not found! May be unsupported yet?";
    return GameCardBasis();
}



void The_Game::SetCurrentGamePhase(const GamePhase &currentGamePhase)
{
    _currentGamePhase = currentGamePhase;
}

void The_Game::SetGlobalGamePhase(GlobalGamePhase phase)
{
    _globalGamePhase = phase;
}

QPoint The_Game::GetMainGamerWidgetPostion()
{
    return ui->MainGamer->ProvideSelfPosition();
}

QPoint The_Game::GetMainGamerHandPosition()
{
    return ui->MainGamer->ProvideHandPosition();
}

QPoint The_Game::GetCardsStackPosition()
{
    return ui->CardStacksWidget->pos();
}

QPoint The_Game::GetTreasuresFoldPosition()
{
    return ui->CardStacksWidget->ProvideTreasuresFoldPosition();
}

QPoint The_Game::GetDoorsFoldPosition()
{
    return ui->CardStacksWidget->ProvideDoorsFoldPosition();
}

QPoint The_Game::GetTreasuresStackPosition()
{
    return ui->CardStacksWidget->ProvideTreasuresStackPosition();
}

QPoint The_Game::GetDoorsStackPosition()
{
    return ui->CardStacksWidget->ProvideDoorsStackPosition();
}

QPoint The_Game::GetCenterPosition()
{
    return QPoint(static_cast<uint32_t> (size().width() / 2),
                  static_cast<uint32_t> (size().height() / 2));
}

QSize The_Game::GetTreasuresFoldSize()
{
    return ui->CardStacksWidget->ProvideTreasuresFoldSize();
}

QSize The_Game::GetDoorsFoldSize()
{
    return ui->CardStacksWidget->ProvideDoorsFoldSize();
}

void The_Game::SlotAdjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace()
{
    ui->MainGamer->adjustSize();
}

void The_Game::SlotCheckCardIsAbleToBePlayed(PositionedCard card, bool fromHand)
{
    qDebug() << "The Card is checking!!!";


    //Перед запуском парсеров с указателями причин невозможности разыграть карту
    //сначала проверить, что не идёт процесс анимации карт.

    if (_currentGamePhase == GamePhase::CardProcessing)
    {
        qDebug() << "NAY-002: DEBUG:::: The Game is in the GamePhase::CardProcessing when it is not possible to use cards!";
        emit SignalCardIsRejectedToBePlayed(true);
        return;
    }



    //Далее требуется найти текущую карту, и запустить для неё соответствующий парсер
    //В зависимости от того, играется ли карта с руки или из игры
    //парсер должен по-разному оценивать возможности розыграша данной карты в данный момент.
    //Для некоторых карт возможность её сыграть означает смену текущей карты и т.п.
    //В текущей версии для шмоток игрок должен сам оценть, будет ли воздействовать для него эффект карты.
    //Для карт, которые сменят класс/рассу потребуется вводить дополнительную механику

    //Механика будет внедрена позднее, и реализована не черз текущие парсеры.
    //Длительное зажатие карты позволит выбрать дополнительные действия, возможные для этой карты.
    //Должен быть в т.ч. и диалог "Вы уверены?"

    //Но данный парсер оценивает только возможность разыгрывать карты в текущем бою.


    SimpleCard givenCard = card.GetCard();
    GameCardBasis realCard = GetRealCard(givenCard);
    CardType currentType = realCard.GetCardType();
    //Treasures Switch
    if (givenCard.first)
    {
        qDebug() << "NAY-002: SlotCheckCardIsAbleToBePlayed(): Card is terasure! ";
        switch (currentType)
        {

        case CardType::TreasureArmor:
            CardISAbleToPlayChecker_TreasureArmor(static_cast<const gameCardTreasureArmor* >(&realCard), fromHand);
            break;

        default:
            qDebug() << "NAY-002: SlotCheckCardIsAbleToBePlayed(): Unsupported yet! ";
            break;
        }

    }
    //Door Switch
    else
    {
        qDebug() << "NAY-002: SlotCheckCardIsAbleToBePlayed(): Card is door! ";
//        switch (realCard.GetCardType())
//        {
//        case value:

//            break;

//        default:
//            break;
//        }
    }




    if (_globalGamePhase == GlobalGamePhase::OtherPlayerMove)
    {
        qDebug() << "NAY-002: DEBUG:::: The Game is in the GlobalGamePhase::OtherPlayerMove when it is not possible to use cards!";
        emit SignalCardIsRejectedToBePlayed(true);
        return;
    }



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

void The_Game::CardImplementer(const CardPlayAllowanceBase *allowance, const GameCardBasis *card)
{
    if (!allowance->GetAllowance())
    {
        ShowCardIsForbiddenToPlayMessage(allowance->GetReasonOfRestriction());
        return;
    }

    switch (card->GetCardType())
    {
    case CardType::TreasureArmor :
    {
        ApplyNewArmor(static_cast<const gameCardTreasureArmor*> (card));
    }

        break;

    default:
        qDebug() << "NAY-002: The_Game::CardImplementer() Card is not implemented yet!";
        break;
    }
}

void The_Game::ShowCardIsForbiddenToPlayMessage(const QString &message)
{
    qDebug() << "NAY-002: Show Card is forbiden to play message: " << message;
}

void The_Game::ApplyNewArmor(const gameCardTreasureArmor *card)
{
    uint32_t totalBonus = static_cast<uint32_t>(card->GetBonus());

    if (card->GetAdditionalBonusforElf() &&
        ((_mainPlayer->GetRace() == Race::Elf) || (_mainPlayer->GetSecondRace() == Race::Elf)))
        totalBonus += static_cast<uint32_t>(card->GetAdditionalBonusforElf());

    if (card->GetAdditionalBonusforOrk() &&
        ((_mainPlayer->GetRace() == Race::Ork) || (_mainPlayer->GetSecondRace() == Race::Ork)))
        totalBonus += static_cast<uint32_t>(card->GetAdditionalBonusforOrk());

    //кажется, нет смысла проверять, есть ли такой бонус.
    //Парсер написан так, что должен вписывать в эти поля нули.
    //Можно перестраховаться, добавив куда можно, нулевые значения
    //Может возникнуть ошибка при установке бонусов.
    //NAY-002: EXPECTED_IMPROVEMENT
    //NAY-002: EXPECTED_ERROR
//    if (card->bonusToFleeing())


//12.12.2018 продолжить здесь

    //Проверка на наличие специальных фич
    if (card->hasSpecialMechanic()) //FlamingArmor
    {
        qDebug() << "NAY-002: cardID: " << card->GetCardID();

        switch (card->GetCardID())
        {
            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::AwfulSocks):
                _mainPlayer->SetNotAbleToHelp(true);
                break;

            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::FlamingArmor):
                _mainPlayer->SetHasFireArmor(true);
                break;

            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::FreudianSlippers):
                _mainPlayer->SetIsAbleToChangeSexOnline(true);
                break;

            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::HelmOfPeripherialVision):
                _mainPlayer->SetIsProtectedFromTheft(true);
                break;

            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::MagnificentHat):
                _mainPlayer->SetHasCursesMirroring(true);
                break;

            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::SandalsOfProtection):
                _mainPlayer->SetIsProtecetedFromCursesFromDoors(true);
                break;

            case static_cast<uint32_t>(CardsWithPassiveSpecialFunctions_TreasureArmor::TinfoilHat):
                _mainPlayer->SetIsProtectedFromCursesFromPlayers(true);
                break;

            default:
                qDebug() << "NAY-002: ERROR While void The_Game::ApplyNewArmor(const gameCardTreasureArmor *card)"
                            "if (card->hasSpecialMechanic()) : No special mechanic assigned!";
                break;
        }
    }

    //Добавление обычных бонусов:

    _mainPlayer->SetFleeChance(_mainPlayer->GetFleeChance() + card->bonusToFleeing());
    _mainPlayer->SetWarPower(_mainPlayer->GetWarPower() + card->GetBonus());

    if (card->GetAdditionalBonusforElf() &&
            (_mainPlayer->GetRace() == Race::Elf || _mainPlayer->GetSecondRace() == Race::Elf))
        _mainPlayer->SetWarPower(_mainPlayer->GetWarPower() + card->GetAdditionalBonusforElf());

    if (card->GetAdditionalBonusforOrk() &&
            (_mainPlayer->GetRace() == Race::Ork || _mainPlayer->GetSecondRace() == Race::Ork))
        _mainPlayer->SetWarPower(_mainPlayer->GetWarPower() + card->GetAdditionalBonusforOrk());

    //Установка карты в слот
    //слоты такой картой не занимаются
    if (card->GetBodyPart() == Body_Part::Armor)
    {
        if (card->isCombined())
            _mainPlayer->SetCombinedArmor(_mainPlayer->GetCombinedArmor() + 1);
        else
            _mainPlayer->SetArmorSlotFull(true);
    }
    if (card->GetBodyPart() == Body_Part::Feet)
    {
        if (card->isCombined())
            _mainPlayer->SetCombinedArmor(_mainPlayer->GetCombinedFeet() + 1);
        else
            _mainPlayer->SetLegsSlotIsFull(true);
    }
    if (card->GetBodyPart() == Body_Part::Head)
    {
        if (card->isCombined())
            _mainPlayer->SetCombinedHead(_mainPlayer->GetCombinedHead() + 1);
        else
            _mainPlayer->SetHeadSlotIsFull(true);
    }

    //Теперь  можно передать крту анимац

}

TreasureArmorAllowance The_Game::CardISAbleToPlayChecker_TreasureArmor(const gameCardTreasureArmor* card, bool fromHand)
{
    //Все подобные парсеры предполагают, что проверка на глобальные запреты уже пройдена.
    //На 11.12.2018 это только процесс анимирования карт (карт-процессинг CardProcessing)

    //Играть карту "Броня" можно в любой момент игры, кроме собственного боя.
    //Причём она может быть как "активной, так и не активной"

    //MunRules
    //https://hobbyworld.ru/download/rules/m_color_rules.pdf
    //https://hobbyworld.ru/chastie-voprosi-po-manchkin#cardsitems

    //Проверка, что нет боя:
    if (GetCurrentGamePhase() == GamePhase::Battle)
        return TreasureArmorAllowance(false, "Нельзя надевать броню в бою!", false);

    if (GetCurrentGamePhase() == GamePhase::OtherPlayerMove)
        return TreasureArmorAllowance(false, "Сейчас чужой ход. Броню можно вводить в игру только в свой ход.", false);

    //NAY-002: HARDCODED_BEHAVIOUR
    //К сожалению, таблица сокровищ-доспехов не предусматривала поле "большой"
    //Т.к. на ДАННЫЙ МОМЕНТ имеется лишь одна шмотка "Мифрильная броня", имеющая тип "большая"
    //Я не буду дописывать в таблицу целое поле и дополнительно его парсить.
    //Ниже сделаю привязку к конкретному Card-ID

    //Ан-нет, я сделал это ещё тогда. =))))
    if (_mainPlayer->GetThereIsLimitOnBigThings() && _mainPlayer->GetThereIsOneBigThing()
            && (card->size() == Size::Big))
        return TreasureArmorAllowance(false, "К сожалению, у Вас уже есть большие шмотки в игре!", false);

    //Запреты кончились, теперь принятие решения о том, какой параметр ставить для активна/неактивна

    //Наличие карты "Чит" пока не рассматривается

    if (card->isOnlyForDwarf()
            && _mainPlayer->GetRace() != Race::Dwarf
            && _mainPlayer->GetSecondRace() != Race::Dwarf)
    {
        return TreasureArmorAllowance(true, "Увы, карта активна только для дворфа!/n Разве вы дфорф?", false);
    }

    if (card->isOnlyForGnome()
            && _mainPlayer->GetRace() != Race::Gnome
            && _mainPlayer->GetSecondRace() != Race::Gnome)
    {
        return TreasureArmorAllowance(true, "Увы, карта активна только для гнома!/n Разве вы гном?", false);
    }

    if (card->isOnlyForWizard()
            && _mainPlayer->GetProfession() != Profession::Wizard
            && _mainPlayer->GetSecondProfession() != Profession::Wizard)
    {
        return TreasureArmorAllowance(true, "Увы, карта активна только для волшебника!/n"
                                            "Разве к вам в детстве прилетала сова с письмом?/n"
                                            "...Но ведь вы её ждали?/n", false);
    }

    if (card->isOnlyForHuman()
            && _mainPlayer->GetRace() != Race::Human)
    {
        return TreasureArmorAllowance(true, "Увы, карта активна только для человека./n Теперь вы другой.", false);
    }
    
    if (card->isRestrictedToGnome() && 
            ((_mainPlayer->GetRace() == Race::Gnome) || (_mainPlayer->GetSecondRace() == Race::Gnome))
            && !_mainPlayer->GetIsHalfBloodWithoutSecondRace())
        return TreasureArmorAllowance(true, "Увы, этот доспех /n не могут носить гномы.", false);
    
    if (card->isRestrictedToWizard() && 
            ((_mainPlayer->GetProfession() == Profession::Wizard) || (_mainPlayer->GetSecondProfession() == Profession::Wizard))
            && !_mainPlayer->GetIsSuperMunchkinWithoutSecondProfession())
        return TreasureArmorAllowance(true, "Увы, этот доспех /n слишком тяжёл для магов.", false);

    //NAY-002: EXPECTED_ERROR
    //NAY-002: EXPECTED_IMPROVEMENT
    //На будущее надо бы сделать защиту от возможности надеть сразу два "комбинируемых" доспеха.
    //С другой стороны, может юыть, их можно надевать по несколько - капусточка. =)))
    if (_mainPlayer->GetLegsSlotIsFull() && (card->GetBodyPart()  == Body_Part::Feet) && (!card->isCombined()))
        return TreasureArmorAllowance(true, "Вторые штаны не натянуть на уже надетые./n Но при большом желании...", false);

    if (_mainPlayer->GetArmorSlotFull() && (card->GetBodyPart()  == Body_Part::Armor) && (!card->isCombined()))
        return TreasureArmorAllowance(true, "Доспех надевали поверх кольчуги./n Но игра такое, увы, запрещает.", false);

    if (_mainPlayer->GetLegsSlotIsFull() && (card->GetBodyPart()  == Body_Part::Feet) && (!card->isCombined()))
        return TreasureArmorAllowance(true, "Вторые ботинки поверх существующих/n никак не надеть.", false);


    //Запретов больше нет
    return TreasureArmorAllowance(true, "", true);

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
    //showFullScreen();
    show();
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

void The_Game::Animation_StartPassSoldCardsFromHandToTreasureFold_Phase1(GamerWidget *wt, std::vector <PositionedCard> cards)
{
    if (!cards.size())
    {
        qDebug() << "NAY-002: ERROR WHILE Animation_StartPassSoldCardsFromHandToTreasureFold_Phase1()."
                    "Empty Vector!";
        return;
    }

    std::vector<QPushButton*> cardsAsButtons;
    std::vector<QPropertyAnimation*> animations;
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        PositionedCard card = cards[var];

        QPushButton* _movingCard = new QPushButton("Animated Button", this);
        cardsAsButtons.push_back(_movingCard);
        QPoint handPosition = wt->ProvideHandPosition();
        QPoint gamerWidgetPosition = wt->ProvideSelfPosition();


        QPoint relativeCardPostionTopLeft = card.GetPositionTopLeft() + gamerWidgetPosition + handPosition;
        QPoint relativeCardPostionBottomRight = card.GetPositionBottomRight() + gamerWidgetPosition + handPosition;

        _movingCard->move(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y());
        int sizeX = relativeCardPostionBottomRight.x() - relativeCardPostionTopLeft.x() ;
        int sizeY = relativeCardPostionBottomRight.y() - relativeCardPostionTopLeft.y();

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
        animations.push_back(animation);
        animation->setDuration(static_cast<uint32_t>(_msTimeForTradeAnimationPhase1));
        animation->setStartValue(QRect(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y(), sizeX, sizeY));
        animation->setEndValue(QRect(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2));
        animation->setEasingCurve(QEasingCurve::OutCubic);

        //setWindowFlags(Qt::CustomizeWindowHint);

        animation->start(QAbstractAnimation::DeleteWhenStopped);

//        connect(animation, &QPropertyAnimation::finished,
//                _movingCard, &QPushButton::deleteLater);

        //Соединить этот сигнал со слотом, который отображает анимацию второй фазы сброса
        //проданных карт.
    }
    connect(animations[0], &QPropertyAnimation::finished,
            [this, cardsAsButtons, cards]
            {Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2(cardsAsButtons, cards);});
}

void The_Game::Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2(std::vector<QPushButton*> movedCards, const std::vector<PositionedCard>& cards)
{
    //Разместить по позициям.
    //финальная позиция, где они были в прошлый раз.
    //animation->setEndValue(QRect(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2));
    if (!movedCards.size())
    {
        qDebug() << "NAY-002: ERROR WHILE Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2()."
                    "Empty Vector!";
        return;
    }

    uint32_t sizeHeight = static_cast<uint32_t>(movedCards[0]->height());
    uint32_t totalWidthNecessary =static_cast<uint32_t>(movedCards.size() * movedCards[0]->width());
    QPoint CardMostToTheLeftPosition = GetCenterPosition()
            - QPoint(static_cast<uint32_t>(totalWidthNecessary/2), movedCards[0]->pos().y());

    std::vector<QPropertyAnimation*> animations;
    for (uint32_t var = 0; var < movedCards.size(); ++var)
    {  
        QPropertyAnimation *animation = new QPropertyAnimation(movedCards[var], "geometry");
        animations.push_back(animation);
        animation->setDuration(static_cast<uint32_t>(_msTimeForTradeAnimationPhase2));
        animation->setStartValue(QRect(movedCards[var]->pos().x(), movedCards[var]->pos().y(),
                                       movedCards[var]->size().width(), movedCards[var]->size().height()));
        animation->setEndValue(QRect(CardMostToTheLeftPosition.x() +var*movedCards[var]->size().width(), movedCards[var]->pos().y(),
                                     movedCards[var]->size().width(), movedCards[var]->size().height()));
        animation->setEasingCurve(QEasingCurve::OutCubic);

        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    //Соединить этот сигнал со слотом, который отображает анимацию третьей фазы сброса
    //проданных карт.
    connect(animations[0], &QPropertyAnimation::finished,
            [this, movedCards, cards] {Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3(movedCards, cards);});

}

void The_Game::Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3(std::vector<QPushButton *> movedCards, const std::vector<PositionedCard> &cards)
{
    if (!movedCards.size())
    {
        qDebug() << "NAY-002: ERROR WHILE Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2()."
                    "Empty Vector!";
        return;
    }

    std::vector<SimpleCard> cardsToBeProcessed;
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        cardsToBeProcessed.push_back(cards[var].GetCard());
    }

    QPoint EndPosition = GetTreasuresFoldPosition() + GetCardsStackPosition();
    QSize EndSize = GetTreasuresFoldSize();
    std::vector<QPropertyAnimation*> animations;

    for (uint32_t var = 0; var < movedCards.size(); ++var)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(movedCards[var], "geometry");
        animations.push_back(animation);
        animation->setDuration(static_cast<uint32_t>(_msTimeForTradeAnimationPhase3));
        animation->setStartValue(QRect(movedCards[var]->pos().x(), movedCards[var]->pos().y(),
                                       movedCards[var]->size().width(), movedCards[var]->size().height()));
        animation->setEndValue(QRect(EndPosition.x(), EndPosition.y(),
                                     EndSize.width(), EndSize.height()));
        animation->setEasingCurve(QEasingCurve::OutCubic);

        animation->start(QAbstractAnimation::DeleteWhenStopped);

        //Соединить этот сигнал со слотом, который добавляет и отображает последнюю сброшенную карту в TreasuresFold.
        //До этого момента игра находится в фазе CardProcessing.
        connect(animation, &QPropertyAnimation::finished,
                movedCards[var], &QPushButton::deleteLater);
        connect(animation, &QPropertyAnimation::finished,
                [this, var, cards]{ emit SignalPassTheCardToTheFoldStack(cards[var].GetCard());});
        if (var == (movedCards.size() - 1))
        {
            connect(animation, &QPropertyAnimation::finished,
                    [this, cardsToBeProcessed]{ProcessFoldObserver(cardsToBeProcessed);});
            connect(animation, &QPropertyAnimation::finished,
                    [this]{CheckThePlayerIsAbleToSell(_mainPlayer);});
            connect(animation, &QPropertyAnimation::finished,
                    [this]{RestoreGamePhase();});
        }
    }    

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

void The_Game::SlotClientIsLeavingTheRoom(const QString &name)
{
    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
    {
        if (_playersOrder[var] == name)
        {
            qDebug() << "NAY-002: Opponent with name " << name << " is leaving.";
            _playersOrder.erase(_playersOrder.begin() + var);
            _playersOrder.shrink_to_fit();
            return;
        }
    }
    qDebug() << "NAY-002: Error during SlotClientIsLeavingTheRoom(). Client not found!";
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

void The_Game::SlotSetUpGameSettings(const GameSettings &settings, bool resetClientsName)
{
   if (!resetClientsName)
   {
       QString _nameWas = _gameSettings.clientName();
       _gameSettings.applyNewSettings(settings);
       _gameSettings.setClientName(_nameWas);
       ui->GameField->ApplyNewSettings(settings);
   }
   else
   {
       _gameSettings.applyNewSettings(settings);
       ui->GameField->ApplyNewSettings(settings);
   }

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

void The_Game::SetUpPlayersAndWidgets(uint32_t windowHeight, uint32_t windowWidth, const std::vector<QString> &playersOrder)
{
    uint32_t totalOpponents = _gameSettings.maximumNumberOfPlayers();
    qDebug() << "Total players from settings: " << totalOpponents;
    qDebug() << "Total players given by SetUp Opponents: " << playersOrder.size();

    _mainPlayer = new Player(_gameSettings.clientName());
    //Из-за того, что я сделал давным давно основного игрока также не динамически создаваемым,
    //получилась разница в сущностях. Неудобно разнобоко назначать одно и то же.
    //С другой стороны было очень удобно при создании и отладке.
    //Так что сохраню эту концепцию.
    ui->MainGamer->SetGamerName(_gameSettings.clientName());
    _roomMasterName = _playersOrder[0];
    SetIsRoomMaster(CheckIsMainPlayerTheRoomMaster(_playersOrder[0]));
    qDebug() << "NAY-001: Master's name: " << playersOrder[0];
    qDebug() << "NAY-002: Clients name: " << _gameSettings.clientName();
    //Set Players name:

    if (totalOpponents != playersOrder.size())
        qDebug() << "ERROR while The_Game::SetUpOpponents(): Total opponents from settings"
                    "and given by server differs!";

    //Один из них может быть мастером!
    for (uint32_t var = 0; var < playersOrder.size(); ++var)
    {
        if (_gameSettings.clientName() != playersOrder[var])
        {
            Player* currentPlayer = new Player (playersOrder[var]);
            currentPlayer->SetPlayersName(playersOrder[var]);
            _playersOpponents.push_back(currentPlayer);
            qDebug() << "NAY-002: _playersOpponents Size: " << _playersOpponents.size();
        }
    }

    //Set-Up order Of move
    std::vector<Player*> orderOfMove;
    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
    {
        if (_mainPlayer->GetPlayersName() == _playersOrder[var])
        {
            _mainGamerOrderOfMove = var;
            orderOfMove.push_back(_mainPlayer);
        }
        for (uint32_t y = 0; y < _playersOpponents.size(); ++y)
        {
            if (_playersOpponents[y]->GetPlayersName() == _playersOrder[var])
            {
                orderOfMove.push_back(_playersOpponents[y]);
                //NAY-002: MARK_EXPECTED_ERROR
                //To Test under 3 or more players.
                break;
            }
        }
    }

    //save the order;
    _orderOfMove = orderOfMove;

    qDebug() << "NAY-002: " << "Order of move: ";
    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        qDebug() << _orderOfMove[var]->GetPlayersName();
    }

    //widgets for them
    for (uint32_t var = 0; var < playersOrder.size(); var++)
    {

       if (_gameSettings.clientName() != playersOrder[var])
       {
           _widgets4Opponents.push_back(new GamerWidget());
           _GamerWidgetsWithIDs.insert(std::make_pair(var, _widgets4Opponents.back()));
           _widgets4Opponents.back()->RedrawAsASecondaryPlayer();
           _widgets4Opponents.back()->setIs_MainPlayer(false);
           _widgets4Opponents.back()->SetGamerName(playersOrder[var]);

           if (playersOrder[var] == _roomMasterName)
               _widgets4Opponents.back()->SetIsRoomMaster();
       }
       else
       {
           _GamerWidgetsWithIDs.insert(std::make_pair(var, ui->MainGamer));
           ui->MainGamer->SetGamerName(playersOrder[var]);
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


    PassCardsToWidgets();

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
    connect(ui->MainGamer, &GamerWidget::SignalSendTheCardToTheGameCheck, this, &The_Game::SlotCheckCardIsAbleToBePlayed);
    //pass the answer form The_Game card check back to the Hand
    connect(this, &The_Game::SignalCardIsRejectedToBePlayed, ui->MainGamer, &GamerWidget::SlotCardIsRejectedToBePlayed);

    QObject::connect(this, &The_Game::SignalChartMessageReceived, ui->wdgt_Chart, &MunchkinDialog::SlotShowMessage);
    QObject::connect(ui->wdgt_Chart, &MunchkinDialog::SignalSendMessage, this, &The_Game::SlotProcessChartMessageSending);
    QObject::connect(ui->GameField, &battleField::SignalStartUpAnimationCompleted, this, &The_Game::SlotInitialAnimationCompleted);

    connect(ui->MainGamer, &GamerWidget::SignalTradeButtonWasPressed, this, &The_Game::SlotShowTradeMenu);

    connect(this, &The_Game::SignalShowTradeButton, ui->MainGamer, &GamerWidget::SlotShowTradeButton);
    connect(this, &The_Game::SignalHideTradeButton, ui->MainGamer, &GamerWidget::SlotHideTradeButton);

    connect(this, &The_Game::SignalPassTheCardToTheFoldStack,
            ui->CardStacksWidget, &CardStacks::SlotPassTheCardToFoldStack);

    connect(this, &The_Game::SignalEnableFoldProcessButton,
            ui->CardStacksWidget, &CardStacks::SlotShowFoldObserver);
    connect(this, &The_Game::SignalDisableFoldProcessButton,
            ui->CardStacksWidget, &CardStacks::SlotHideFoldObserver);

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
    PassDecksToPlayerWidgets();
    PassDecksToCardsInspectorWidget();
    PassDecksToPopUpCardWidget();
    PassDecksToCardsStacksWidget();
}

void The_Game::RemoveCardFromCardsAreAbleToBeSold(SimpleCard card)
{
    for (int var = 0; var < _cardsAreReadyToBeSoldHolder.size(); ++var)
    {
        if (_cardsAreReadyToBeSoldHolder[var] == card)
        {
            _cardsAreReadyToBeSoldHolder.erase(_cardsAreReadyToBeSoldHolder.begin() + var);
            return;
        }
    }
    qDebug() << "EEROR WHILE RemoveCardFromCardsAreAbleToBeSold! Card with id: " << card.second
             << " Not found!";
}

void The_Game::RemoveTheCardFromHand(GamerWidget *wt, SimpleCard card)
{
    wt->RemoveCardFromHand(card);
}

void The_Game::SlotShowTradeMenu()
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    emit SignalHideTradeButton();
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
                                _gameSettings.GetHardCodedSettingsAllowedToOverSellAtLevelNine(),
                                _mainPlayer->GetPlayerLevel(),
                                _gameSettings.GetHardCodedSettingsAllowLevelOverSell(),
                                _cardsAreReadyToBeSoldHolder);

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
    //1. Сохранить карты, чтобы обработать добавление в стек после анимации
    //2. Удалить карты с руки
    //3. Проверить и убрать в случае необходимости кнопку "Торговля"
    //4. Добавить уровень//уровни
    qDebug() << "NAY-002: In the SlotProcessCardsSelectedToBeSold() ";
    qDebug() << "NAY-002: CardsToBeSold size " << cards.size();   
    uint32_t totalMoneySpent = 0;
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        AddCardToFoldStack(cards[var]);
        totalMoneySpent += GetCardPrice(cards[var]);
    }
    _lastFold = cards;
    qDebug() << "NAY-002: Total Money Spent: " << totalMoneySpent;
    _mainPlayer->SetPlayerLevel(_mainPlayer->GetPlayerLevel() + GetLevelPurchased(totalMoneySpent));
    _mainPlayer->SetWarPower(_mainPlayer->GetWarPower() + GetLevelPurchased(totalMoneySpent));

    qDebug() << "NAY-002: Emitting Signal MainGamer Has Sold Cards: "
             << " For Room with id: " << _roomID;

    emit SignalMainGamerHasSoldCards(TheGameMainGamerHasSoldCards(
                                         _mainGamerOrderOfMove,
                                         cards,
                                         GetLevelPurchased(totalMoneySpent),
                                         true,
                                         _roomID));


    ui->MainGamer->SlotChangeTheGamerLevel(static_cast<int32_t>(GetLevelPurchased(totalMoneySpent)));

    //1.1. Для этого сначала получить их позиции
    std::vector<PositionedCard> posCards = GetPositionedCards(ui->MainGamer, cards);
    qDebug() << "NAY-002: posCards size " << posCards.size();

    //Убрать проданные карты с руки. (Карты хранятся во временном векторе posCards)
    //Была либо фаза торговли, либо фаза "ход другого игрока"
    SaveGamePhase();
    SetGamePhase(GamePhase::CardProcessing);

    emit SignalHideTradeButton();
    for (uint32_t var = 0; var < posCards.size(); ++var)
    {
        RemoveCardFromCardsAreAbleToBeSold(posCards[var].GetCard());
        RemoveTheCardFromHand(ui->MainGamer, posCards[var].GetCard());
    }
    _mainPlayer->RemoveGivenCardsFromHand(cards);

    //start animation here
    Animation_StartPassSoldCardsFromHandToTreasureFold_Phase1(ui->MainGamer, posCards);
}

std::vector<PositionedCard> The_Game::GetPositionedCards(GamerWidget* wt, const std::vector<SimpleCard> &cards)
{
    return wt->GetPositionedCards(cards);
}

void The_Game::SlotAddPlayedCardToTheBattleField(SimpleCard card)
{

}

void The_Game::SlotShowAllSoldCardsInCentre(const std::vector<SimpleCard> cards, uint32_t msTime)
{
    QPoint centerPosition = GetCenterPosition();
    QPushButton* allCards = new QPushButton("Animated Button", this);
    //allCards->setMaximumWidth(cards.size()*);

}

bool The_Game::CheckThePlayerIsAbleToSell(Player* player)
{
    qDebug() <<"NAY-002: Entering AbleToSell Checker";
    if (_globalGamePhase == GlobalGamePhase::OtherPlayerMove)
        return false;

    if (!_gameSettings.GetHardCodedSettingsAllowedToSellAtLevelNine()
            && (player->GetPlayerLevel() == 9))
        return false;

    std::vector<SimpleCard> sumChecker;
    std::vector<SimpleCard> cardsOnHands = player->GetCardsOnHands();
    std::vector<SimpleCard> cardsInGame = player->GetCardsInGame();

    qDebug() <<"NAY-002: AbleToSell Checker cardsOnHands: size: " << player->GetCardsOnHands().size();

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
            _cardsAreReadyToBeSoldHolder.push_back(sumChecker[var]);
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
        return static_cast<uint32_t>((*_battleAmplifiersIterator).second.price());


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

uint32_t The_Game::GetLevelPurchased(uint32_t totalMoneySpent)
{
    return totalMoneySpent / 1000;
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

void The_Game::SlotProcessOpponentHasSoldCards(TheGameMainGamerHasSoldCards data)
{
    //1. Вычислить оппонента
    //2. Добавить ему уровень/боевую силу
    //3. Отобразить анимацию продажи карт
    qDebug() << "NAY-002: SlotProcessOpponentHasSoldCards(TheGameMainGamerHasSoldCards data) ";

    uint32_t opponentId = data.gamerID; //explicitly relates to _playersOrder;
    qDebug() << "NAY-002: opponentID: " << opponentId;
    Player* currentPlayer = _orderOfMove[data.gamerID];

    GamerWidget* currentWidget = _GamerWidgetsWithIDs[data.gamerID];

    QPoint currentPosition = currentWidget->ProvideHandPosition();

    //Т.к. карты известны, можно установить новый уровень/юоевую силу и начать продажу
    currentPlayer->SetPlayerLevel(currentPlayer->GetPlayerLevel() + data.levelDelta);
    currentPlayer->SetWarPower(currentPlayer->GetWarPower() + data.levelDelta);

    currentWidget->SlotChangeTheGamerLevel(data.levelDelta);
    currentWidget->SlotChangeTheGamerBattlePower(data.levelDelta);

    //1.1. Для этого сначала получить их позиции
    std::vector<PositionedCard> posCards = GetPositionedCards(currentWidget, data.soldCards);
    qDebug() << "NAY-002: posCards size " << posCards.size();

    //Убрать проданные карты с руки. (Карты хранятся во временном векторе posCards)
    //Была либо фаза торговли, либо фаза "ход другого игрока"
    SaveGamePhase();
    SetGamePhase(GamePhase::CardProcessing);
    emit SignalHideTradeButton();
    for (uint32_t var = 0; var < posCards.size(); ++var)
    {
        RemoveCardFromCardsAreAbleToBeSold(posCards[var].GetCard());
        RemoveTheCardFromHand(currentWidget, posCards[var].GetCard());
    }
    currentPlayer->RemoveGivenCardsFromHand(data.soldCards);

    //start animation here
    Animation_StartPassSoldCardsFromHandToTreasureFold_Phase1(currentWidget, posCards);

    //RestoreGamePhase();


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

    SetGlobalGamePhase(GlobalGamePhase::OwnMove);
    SetCurrentGamePhase(GamePhase::StartOfTheMove);

    if (CheckThePlayerIsAbleToSell(_mainPlayer))
        qDebug() << "NAY-001: The player is able to sell!";
}

void The_Game::InitializeOpponentMove(const QString &opponentsName)
{
    SetGlobalGamePhase(GlobalGamePhase::OtherPlayerMove);
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
