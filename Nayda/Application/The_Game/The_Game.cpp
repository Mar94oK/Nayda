#include "Application/The_Game/The_Game.h"
#include "ui_the_game.h"
#include <ctime>
#include <QTime>
#include <ui_the_game.h>
#include "popupcard.h"
#include "munchkinglobaldefines.h"
#include <QSharedPointer>




The_Game::The_Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::The_Game)
{
    DECLARE_NAMED_LOGGER(The_Game);

    ui->setupUi(this);

    InitializePopUpWidgets();
    SetUpBackgroundPicture();

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();

    _hwScreenSizeWidth = static_cast<uint32_t>(HW_Screen_Size.width());
    _hwScreenSizeHeigh = static_cast<uint32_t>(HW_Screen_Size.height());

    //Regarding this note
    //https://stackoverflow.com/questions/44875309/why-does-qdesktopwidget-give-me-the-wrong-available-geometry-when-i-use-two-moni
    //It is necessary to adjust size while using Linux internally.
    //make it 0.8 of height for example

#ifdef __linux
    static_cast<uint32_t>(_hwScreenSizeHeigh *= 0.9);
    static_cast<uint32_t>(_hwScreenSizeWidth *= 0.8);
#endif
#ifdef Q_OS_WIN
    static_cast<uint32_t>(_hwScreenSizeHeigh *= 0.9);
    static_cast<uint32_t>(_hwScreenSizeWidth *= 0.8);
#endif

    //1. SetUp Initial Signals-Slots connections
    SetUpSignalSlotsConnections();

    //2. GUI Adjustment
    SetUpWidgetsProperties(_hwScreenSizeHeigh, _hwScreenSizeWidth);
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
    InitializeApplyCardToCardsInGameTimer(_msHoldBetweenApplyCardToCardsInGameAnimations);

    InitializeFoldObserver();

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
    logger.Algorithm() << "Amplifiers parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "Curses parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "Professions parsing starts!";

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
       logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "Races parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "SpecialMechanics parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "Armors parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    if (lst.first() == "yes\n")
    {
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
    logger.Algorithm() << "ArmorAmplifiers parsing starts!";

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
       logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "BattleAmplifiers parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "LevelUp parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "TreasureSpecialMechanics parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "Things Amplifiers parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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
    logger.Algorithm() << "Weapons parsing starts!";

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
        logger.Error() << "Cannot open this file!";
    }
}

gameCardTreasureWeapon The_Game::WeaponStringParser(const QString &weapons_string)
{
    gameCardTreasureWeapon theWeapon;
    QStringList lst = weapons_string.split(";");

    theWeapon.SetCardID((lst.first()).toInt());
    lst.removeFirst();

#ifndef USE_RESOURCES
    theWeapon.setPictureAddress(lst.first());
#else
    theWeapon.SetPictureAddress(":/" + lst.first());
#endif

    lst.removeFirst();

    theWeapon.SetCardName(lst.first());
    lst.removeFirst();

    if (lst.first() == "Basic") theWeapon.SetAddOn(cardAddon::Basic);
    else if (lst.first() == "WildAxe") theWeapon.SetAddOn(cardAddon::WildAxe);
    else if (lst.first() == "ClericalErrors") theWeapon.SetAddOn(cardAddon::ClericalErrors);
    lst.removeFirst();

    theWeapon.SetType(treasureType::Weapon);
    lst.removeFirst();

    theWeapon.SetNecessaryHands(lst.first().toInt());
    lst.removeFirst();

    theWeapon.SetSize(Size::Small);
    if (lst.first() == "big") {
        theWeapon.SetSize(Size::Big);
    }
    lst.removeFirst();

    theWeapon.SetBonus(lst.first().toInt());
    lst.removeFirst();

    isOnlyFor_Weapon restrictions = TheWeaponIsForParser(lst.first());
    theWeapon.SetIsOnlyForBard(restrictions.isOnlyForBard);
    theWeapon.SetIsOnlyForCleric(restrictions.isOnlyForCleric);
    theWeapon.SetIsOnlyForDwarf(restrictions.isOnlyForDwarf);
    theWeapon.SetIsOnlyForElf(restrictions.isOnlyForElf);
    theWeapon.SetIsOnlyForGnome(restrictions.isOnlyForGnome);
    theWeapon.SetIsOnlyForHalfling(restrictions.isOnlyForHalfling);
    theWeapon.SetIsOnlyForHuman(restrictions.isOnlyForHuman);
    theWeapon.SetIsOnlyForMan(restrictions.isOnlyForMan);
    theWeapon.SetIsOnlyForOrk(restrictions.isOnlyForOrk);
    theWeapon.SetIsOnlyForThief(restrictions.isOnlyForThief);
    theWeapon.SetIsOnlyForWarrior(restrictions.isOnlyForWarrior);
    theWeapon.SetIsOnlyForWizard(restrictions.isOnlyForWizard);
    theWeapon.SetIsOnlyForWoman(restrictions.isOnlyForWoman);

    lst.removeFirst();

    theWeapon.SetHasSpecialMechanic(false);
    if (lst.first() == "yes") {
        theWeapon.SetHasSpecialMechanic(true);;
    }
    lst.removeFirst();

    theWeapon.SetPrice(lst.first().toInt());
    lst.removeFirst();

    theWeapon.SetBonusToFlee(lst.first().toInt());
    lst.removeFirst();

    theWeapon.SetAdditionalBonusAgainstUndead(lst.first().toInt());
    lst.removeFirst();

    theWeapon.SetAutomaticLooseToCalmadzila(false);
    if (lst.first().toInt()) {
         theWeapon.SetAutomaticLooseToCalmadzila(true);
    }
    lst.removeFirst();

    theWeapon.SetAdditionalBonusAgainst_J(lst.first().toInt());
    lst.removeFirst();

    theWeapon.SetAddingClericalAbility(false);
    if (lst.first().toInt()) {
         theWeapon.SetAddingClericalAbility(true);
    }
    lst.removeFirst();

    theWeapon.SetAddingThiefAbility(false);
    if (lst.first().toInt()) {
         theWeapon.SetAddingThiefAbility(true);
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

void The_Game::InitializeFoldObserver()
{
    QRect HW_Screen_Size = geometry();
    std::vector<SimpleCard> foldedCards;
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

    _foldObserver->SetState(FoldObsreverState::Disabled);
    emit SignalDisableFoldProcessButton();

    connect(ui->CardStacksWidget, &CardStacks::SignalFoldObserverButtonPressed,
            _foldObserver, &LastFoldObserver::show);
}

void The_Game::ProcessFoldObserver(const std::vector<SimpleCard> foldedCards)
{
    QRect HW_Screen_Size = geometry();

    if (_foldObserver->GetState() == FoldObsreverState::Disabled)
    {
        //кнопка блокирована
        //удалить старые карты
        //добавить новые карты
        _foldObserver->ClearFoldObserver();
        _foldObserver->SetNewCards(foldedCards);
        _foldObserver->SetState(FoldObsreverState::Enabled);
        emit SignalEnableFoldProcessButton();
    }
    else
    {
        //NAY-002: EXPECTED_IMPROVEMENT
        //Потом не прятать кнопку, а только отключать
        //на время процессинга
        emit SignalDisableFoldProcessButton();
        _foldObserver->ClearFoldObserver();
        _foldObserver->SetNewCards(foldedCards);
        _foldObserver->SetState(FoldObsreverState::Enabled);
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

    logger.Debug() << "NAY-002: PlayersOrder size: " << _orderOfMove.size();
    if (_orderOfMove.size() != _playersOpponents.size() + 1)
        logger.Error() << "NAY-002: ERROR WHILE void The_Game::GivingCardsToPlayers()"
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
    logger.Algorithm() << "Doors are given to the players!";

    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        for (uint32_t y = 0; y < cardsToGive; ++y)
        {
#ifndef DEBUG_CARDS_TO_BE_GIVEN_TO_MASTER
            _orderOfMove[var]->AddCardToHands(_treasuresDeck.front());
            _treasuresDeck.erase(_treasuresDeck.begin());
#else
            if (var == 0)
            {
                //в отладочном векторе не должно быть меньше карт, чем в cardsToGive;
                try
                {
                    if (_debugCardsToBeGivenToMainPlayer.size() < cardsToGive)
                        throw "Error!";
                }
                catch (...)
                {
                    logger.Error() << "NAY-002: _debugCardsToBeGivenToMainPlayer.size() < cardsToGive!!!!";
                }

                _orderOfMove[var]->AddCardToHands(_debugCardsToBeGivenToMainPlayer[y]);
                for (uint32_t x = 0; x < _treasuresDeck.size(); ++x)
                {
                    if (_treasuresDeck[x] == _debugCardsToBeGivenToMainPlayer[y])
                        _treasuresDeck.erase(_treasuresDeck.begin() + static_cast<int32_t>(x));
                }
                _treasuresDeck.shrink_to_fit();
            }
            else
            {
                _orderOfMove[var]->AddCardToHands(_treasuresDeck.front());
                _treasuresDeck.erase(_treasuresDeck.begin());
            }
#endif
        }
    }

    ui->CardStacksWidget->updateTreasuresLeft(initialSizeTreasures - cardsToGive*_gameSettings.maximumNumberOfPlayers());
    logger.Algorithm() << "Treasures are given to the players!";

#endif
}

void The_Game::ShowInitialCardsOnHands()
{
    logger.Algorithm() << "showInitialCardsOnHands:: Started";

    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        std::vector<SimpleCard> cardsOnHands = _orderOfMove[var]->GetCardsOnHands();
        for (uint32_t y = 0; y < cardsOnHands.size(); ++y)
        {
            //logger.Debug() << "NAY-002: " << "Showing Card with id: " << cardsOnHands[y].second;
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

   //NAY-001: EXPECTED_ERROR
   //These sizes ARE USED AS DEFINES ON SERVER SIDE.
   //HERE TO CHECK AND THROW AN EXCEPTION IF THEY ARE NOT CORRECT
   //I do not want to place all the code on the server's side - with cards and so on;
   //This data should be given by master to the server while passing settings
   //(Not visible to user)

   if (!totalTreasures)  logger.Error() << "Error during Treasures Stack Initialization. Stack is Empty! ";
   logger.Debug() << "Size of Treasures Stack Report: " << totalTreasures;
   if (!totalDoors)  logger.Error() << "Error during Doors Stack Initialization. Stack is Empty! ";
   logger.Debug() << "Size of Doors Stack Report: " << totalDoors;

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

    logger.Algorithm() << "Treasures Stack is Filled Now!";

    for (unsigned int var = 0; var < totalDoors; ++var) {

        unsigned int valuesLeft = valuesDoors.size();
        unsigned int currentPosition = randUnsignedInt(0, valuesLeft-1);
        _doorsDeck.push_back({false,valuesDoors[currentPosition]});
        valuesDoors.erase(valuesDoors.begin() + static_cast<int>(currentPosition)); //remove additional
        valuesDoors.shrink_to_fit();
    }

    logger.Algorithm() << "Doors Stack is Filled Now!";

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
    logger.Algorithm() << "Monsters parsing starts!";

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
        logger.Error() << "Cannot open this file!";
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

const GameCardBasis* The_Game::GetRealCard(SimpleCard card)
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
            return &(*_monstersIterator).second;

        _amplifiersIterator = _amplifiersDeck.find(static_cast <int> (card.second));
        if (_amplifiersIterator != _amplifiersDeck.end())
            return &(*_amplifiersIterator).second;

        _cursesIterator = _cursesDeck.find(static_cast <int> (card.second));
        if (_cursesIterator != _cursesDeck.end())
            return &(*_cursesIterator).second;

        _professionsIterator = _professionsDeck.find(static_cast <int> (card.second));
        if (_professionsIterator != _professionsDeck.end())
            return &(*_professionsIterator).second;

        _racesIterator = _racesDeck.find(static_cast <int> (card.second));
        if (_racesIterator != _racesDeck.end())
            return &(*_racesIterator).second;

        _specialMechanicsIterator = _specialMechanicsDeck.find(static_cast <int> (card.second));
        if (_specialMechanicsIterator != _specialMechanicsDeck.end())
            return &(*_specialMechanicsIterator).second;
    }
    else
    { //treasure
        _armorIterator = _armorDeck.find(static_cast <int> (card.second));
        if (_armorIterator != _armorDeck.end())
            return &(*_armorIterator).second;

        _armorAmplifiersIterator = _armorAmplifiersDeck.find(static_cast <int> (card.second));
        if (_armorAmplifiersIterator != _armorAmplifiersDeck.end())
            return &(*_armorAmplifiersIterator).second;

        _battleAmplifiersIterator = _battleAmplifiersDeck.find(static_cast <int> (card.second));
        if (_battleAmplifiersIterator != _battleAmplifiersDeck.end())
            return &(*_battleAmplifiersIterator).second;

        _levelUpIterator = _levelUpDeck.find(static_cast <int> (card.second));
        if (_levelUpIterator != _levelUpDeck.end())
            return &(*_levelUpIterator).second;

        _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck.find(static_cast <int> (card.second));
        if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck.end())
            return &(*_specialMechanicsTreasureIterator).second;

        _thingsAmplifiersIterator = _thingsAmplifiersDeck.find(static_cast <int> (card.second));
        if (_thingsAmplifiersIterator != _thingsAmplifiersDeck.end())
            return &(*_thingsAmplifiersIterator).second;

        _weaponsIterator = _weaponsDeck.find(static_cast <int> (card.second));
        if (_weaponsIterator != _weaponsDeck.end())
            return &(*_weaponsIterator).second;

    }
    logger.Error() << "NAY-002: Error while GameCardBasis The_Game::GetRealCard(SimpleCard card)"
                   << "Card Not found! May be unsupported yet?";

    return nullptr;
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

QPoint The_Game::GetAvatarPositon(const GamerWidget * const wt)
{
    return wt->ProvideCardsInGamePosition();
}

QPoint The_Game::GetCardsInGamePosition(const GamerWidget * const wt)
{
    return wt->ProvideCardsInGamePosition();
}

QPoint The_Game::GetNewCardAddedToCardsInGamePosition(const GamerWidget * const wt)
{
    return wt->ProvidePositionOfTheLastCardAddedToCardsInGame();
}

QPoint The_Game::GetPlayerWidgetSelfPosition(const GamerWidget * const wt)
{
    return wt->pos();
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

QSize The_Game::GetAvatarSize(const GamerWidget * const wt)
{
    return wt->ProvideAvatarSize();
}

void The_Game::InitializeApplyCardToCardsInGameTimer(uint32_t msTime)
{
    _animationApplyCardToCardsInGameTimer = new QTimer(this);
    _animationApplyCardToCardsInGameTimer->setSingleShot(true);
    _animationApplyCardToCardsInGameTimer->setInterval(msTime);
}

void The_Game::ApplyCardImplementerMessage(const QString &message, bool cardWillBePlayed)
{

    //NAY-002: EXPECTED_IMPROVEMENT
    //Требуется переработать отображение этого сообщения в момент боя и тп., чтобы оно красиво
    //и корректно выводилось, будучи при этом информативным.

    QLabel* cardImplementerMessage = new QLabel(this);

    QFont        cardImplementerMessageLabelFont ("times", 27);
    QFontMetrics cardImplementerMessageLabelFontInterval (cardImplementerMessageLabelFont);
    cardImplementerMessage->setFont(cardImplementerMessageLabelFont);
    cardImplementerMessage->setAlignment(Qt::AlignHCenter);
    cardImplementerMessage->setText(message);
    cardImplementerMessage->adjustSize();

    const uint32_t aboveInterval = 15;

    uint32_t verticalDelta = cardImplementerMessageLabelFontInterval.height();
    uint32_t horizontalDelta = cardImplementerMessage->size().width() / 2;
//            + cardSize.height() / 2 + aboveInterval;

    QPoint center = GetCenterPosition();
    //сообщение должно находиться выше карты, которую разыгрывает игрок,
    //в том случае, если карта разыгрывается.
    //в противном случае расположить сообщение можно и в центре
    if (cardWillBePlayed)
    {
        QSize cardSize = GetCardSize();
        verticalDelta += cardSize.height();
        cardImplementerMessage->move(center.x() - horizontalDelta, center.y() - verticalDelta - aboveInterval);
    }
    else
    {
        cardImplementerMessage->move(center.x() - horizontalDelta, center.y() - verticalDelta - aboveInterval);
    }

    cardImplementerMessage->show();

    QTimer::singleShot(_msTimeForCardImplementerMessage,
                       Qt::TimerType::CoarseTimer,
                       cardImplementerMessage,
                       [cardImplementerMessage]{cardImplementerMessage->deleteLater();});

}

QSize The_Game::GetCardSize()
{
    return ui->MainGamer->GetCardOnHandSize();
}

void The_Game::SetApplyers()
{
    //_Applyers.insert(std::make_pair<CardType::TreasureArmor, &The_Game::ApplyNewArmor >);
}


void The_Game::SlotAdjustSizeOfTheGamerWidgetToMakeCardsToBeInPlace()
{
    ui->MainGamer->adjustSize();
}

void The_Game::SlotCheckCardIsAbleToBePlayed(PositionedCard card, bool fromHand)
{
    logger.Algorithm() << "The Card is checking!!!";


    //Перед запуском парсеров с указателями причин невозможности разыграть карту
    //сначала проверить, что не идёт процесс анимации карт.


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

    //SaveGamePhase();
    //SetGamePhase(GamePhase::CardAnimation);

    MainCardImplementer(ui->MainGamer, card, CardImplementationDirection::HandToCardsInGame);

    //Пусть "Применитель карт" выполняет функционал передачи прав на карту
    //Однако, пусть он явно указывает, какую карту и куда передать


}

void The_Game::MainCardImplementer(GamerWidget *wt, PositionedCard card, CardImplementationDirection direction, CardCheckerPolicy checkerPolicy)
{
    //Сначала требуется понять, вычислять ли наличие разрешения
    //В случае запроса от сервера разрешение не требуется - можно сразу применять карту.
    logger.Algorithm() << "Entering MainCardImplementer!";

    const GameCardBasis* basisCard = GetRealCard(card.GetCard());
    if (checkerPolicy == CardCheckerPolicy::CheckBeforeImplementation)
    {
        //Перед всеми остальными действиями сначала проверить глобальные запреты.
        if (_currentGamePhase == GamePhase::OtherPlayerMove)
        {
            //Later while implementing Curses rechek this rule!
            logger.Debug() << "NAY-002: DEBUG:: Other Player's Move! DEBUG!!! Not allowed to play cards!";
            emit SignalCardIsRejectedToBePlayed(true);
            return;
        }
        if (_currentGamePhase == GamePhase::CardAnimation)
        {
            logger.Debug() << "NAY-002: DEBUG:: The Game is in the GamePhase::CardAnimation when it is not possible to use cards!";
            emit SignalCardIsRejectedToBePlayed(true);
            return;
        }

        logger.Algorithm() << "MainCardImplementer:: Trying to get Allowance!";
        std::shared_ptr<CardPlayAllowanceBase> allowance = GetAllowance(basisCard, wt->GetPointerToPlayer(), direction);
        //Проверить, разрешено ли применить карту
        //Если да - применить её (причём, в зависимости от направления могут быть разные типы применения!)
        //В будущем - т.е. "Дипломатия" будет проверять, выполнены ли условия по передаче карты и т.п.
        //В настоящий момент (21.12.2018) выполняет только применение карты в игру
        //Вывести причину, если нельзя
        //ADD_LATER
        logger.Algorithm() << "MainCardImplementer:: Checking allowance received.";
        if (!allowance->GetAllowance())
        {
            ProcessCardMightNotBeImplemented(allowance);
        }
        else
        {
            switch (basisCard->GetCardType())
            {
                case CardType::TreasureArmor:
                {
                    std::shared_ptr<TreasureArmorAllowance> armorAllowance = std::static_pointer_cast<TreasureArmorAllowance>(allowance);
                    qDebug() << "NAY-002: Starting TreasureArmor Implementation: armorAllowance: Reason of restriction: " << armorAllowance->GetReasonOfRestriction();
                    ProcessCardAllowedToBeImplemented(allowance, basisCard, wt, card, direction);
                    emit SignalCardIsRejectedToBePlayed(false);
                    //Отсюда отправить сообщение на сервер о применении карты
                    //в случае если это не сервер прислал сообщение о необходимости применения карты
                    emit SignalMainGamerHasImplementedCard(TheGameMainGamerHasImplementedCard(
                                                               _mainGamerOrderOfMove,
                                                               card.GetCard(),
                                                               _roomID,
                                                               false,
                                                               CardImplementationDirection::HandToCardsInGame));
                }
                    break;
                case CardType::TreasureLevelUp:
                {
                    std::shared_ptr<TreasureLevelUpAllowance> levelUpAllowance = std::static_pointer_cast<TreasureLevelUpAllowance>(allowance);
                    qDebug() << "NAY-002: Starting TreasureLevelUp Implementation: levelUpAllowance: Reason of restriction: " << levelUpAllowance->GetReasonOfRestriction();
                    ProcessCardAllowedToBeImplemented(allowance, basisCard, wt, card, direction);
                    emit SignalCardIsRejectedToBePlayed(false);
                    //Отсюда отправить сообщение на сервер о применении карты
                    //в случае если это не сервер прислал сообщение о необходимости применения карты
                    //TODO:
                    //Сюда добавить сигнал для сервера!
                    emit SignalMainGamerHasImplementedCard(TheGameMainGamerHasImplementedCard(
                                                               _mainGamerOrderOfMove,
                                                               card.GetCard(),
                                                               _roomID,
                                                               false,
                                                               CardImplementationDirection::HandToCardsInGame));

                }
                    break;

            case CardType::TreasureWeapon:
            {
                std::shared_ptr<TreasureWeaponAllowance> weaponAllowance = std::static_pointer_cast<TreasureWeaponAllowance>(allowance);
                logger.Algorithm() << "NAY-002: Starting TreasureLevelUp Implementation: weaponAllowance: Reason of restriction: " << weaponAllowance->GetReasonOfRestriction();
                ProcessCardAllowedToBeImplemented(allowance, basisCard, wt, card, direction);
                emit SignalCardIsRejectedToBePlayed(false);
                //Отсюда отправить сообщение на сервер о применении карты
                //в случае если это не сервер прислал сообщение о необходимости применения карты
                //TODO:
                //Сюда добавить сигнал для сервера!
                emit SignalMainGamerHasImplementedCard(TheGameMainGamerHasImplementedCard(
                                                           _mainGamerOrderOfMove,
                                                           card.GetCard(),
                                                           _roomID,
                                                           false,
                                                           CardImplementationDirection::HandToCardsInGame));

            }
                break;

            default:
                {
                    qDebug() << "NAY-002: New ARCHITECTURE Starting: CardType: " << basisCard->GetCardType() << " not handled yet!";
                    emit SignalCardIsRejectedToBePlayed(true);
                    return;
                }
            }
        }

    }
    else if (checkerPolicy == CardCheckerPolicy::ImplementByServerCommand)
    {
        //Не проверять глобальных запретов.
        //По сути это только анимация - не спровоцированные игроком действия.
        //Он сам должен удалить карты из того места, откуда они должны быть удалены.
        std::shared_ptr<CardPlayAllowanceBase> allowance = GetAllowance(basisCard, wt->GetPointerToPlayer(), direction);

        if (!allowance->GetAllowance())
        {
            qDebug() << "NAY-002: ERROR! Card SHOULD BE Implemented - server ONLY reports the card to be implemented";
            return;
        }
        switch (basisCard->GetCardType())
        {
            case CardType::TreasureArmor:
            {
                ProcessCardAllowedToBeImplemented(allowance, basisCard, wt, card, direction);
            }
            break;

            case CardType::TreasureLevelUp:
            {
                ProcessCardAllowedToBeImplemented(allowance, basisCard, wt, card, direction);
            }
            break;
            default:
            {
                qDebug() << "NAY-002: New ARCHITECTURE Starting: CardType: " << basisCard->GetCardType() << " not handled yet!";
                ApplyCardImplementerMessage("This type of card is not supported yet!", false);
                return;
            }
        }

    }

}

std::shared_ptr<CardPlayAllowanceBase> The_Game::GetAllowance(const GameCardBasis *card, Player *player, CardImplementationDirection direction)
{
    if (card->GetCardType() == CardType::TreasureArmor)
    {
        const gameCardTreasureArmor* cardPtr = static_cast<const gameCardTreasureArmor* >(card);
        return GetAllowanceTreasureArmor(cardPtr, player, true);
    }
    else if (card->GetCardType() == CardType::TreasureLevelUp)
    {
        const gameCardTreasureLevelUp* cardPtr = static_cast<const gameCardTreasureLevelUp* >(card);
        return  GetAllowanceTreasureLevelUp(cardPtr, player, true);
    }
    else if (card->GetCardType() == CardType::TreasureWeapon)
    {
        const gameCardTreasureWeapon* cardPtr = static_cast<const gameCardTreasureWeapon* >(card);
        return GetAllowanceTreasureWeapon(cardPtr, player, true);
    }
    logger.Error() << "NAY-002: ERROR WHILE The_Game::GetAllowance. Not implemented type: "
             << card->GetCardType();

    return nullptr;

}

void The_Game::ProcessCardMightNotBeImplemented(std::shared_ptr<CardPlayAllowanceBase> allowance)
{
    emit SignalCardIsRejectedToBePlayed(true);
    ApplyCardImplementerMessage(allowance->GetReasonOfRestriction(), false);
}

void The_Game::ProcessCardAllowedToBeImplemented(std::shared_ptr<CardPlayAllowanceBase> allowance, const GameCardBasis *card, GamerWidget *wt, PositionedCard posCard, CardImplementationDirection direction)
{
    logger.Algorithm() << "NAY-002: ProcessCardAllowedToBeImplemented() ImplementationDirection: " << direction;

    switch (direction)
    {
        case CardImplementationDirection::HandToCardsInGame:
        {
            ImplementCardFromHandsToCardsInGame(allowance, card, wt, posCard);
        }
            break;
        default:
        {
            qDebug() << "NAY-002: ProcessCardAllowedToBeImplemented ImplementationDirection: " << direction << "Is not supported yet!";
            emit SignalCardIsRejectedToBePlayed(true);
            ApplyCardImplementerMessage(QString("This direction is not supported yet!"), false);
        }
            break;
    }
}

void The_Game::ImplementCardFromHandsToCardsInGame(std::shared_ptr<CardPlayAllowanceBase> allowance, const GameCardBasis *card, GamerWidget *wt, PositionedCard posCard)
{
    qDebug() << "NAY-002: ImplementCardFromHandsToCardsInGame() starting";

    switch (card->GetCardType())
    {
        case CardType::TreasureArmor:
        {
            ImplementTreasureArmorToCardsInGame(allowance, card, wt, posCard);
        }
        break;

        case CardType::TreasureLevelUp:
        {
            ImplementTreasureLevelUpCard(allowance, card, wt, posCard);
        }
        break;

        case CardType::TreasureWeapon:
        {
            ImplementTreasureWeapon(allowance, card, wt, posCard);
        }
        break;


        default:
        {
            logger.Error() << "NAY-002: ERROR WHILE ImplementCardFromHandsToCardsInGame(). Card is not supported yet!";
        }
           break;
    }
}

std::shared_ptr<TreasureArmorAllowance> The_Game::GetAllowanceTreasureArmor(const gameCardTreasureArmor *card, Player *player, bool fromHand)
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
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(false, "Нельзя надевать броню в бою!", false));

    if (GetCurrentGamePhase() == GamePhase::OtherPlayerMove)
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(false, "Сейчас чужой ход. Броню можно вводить в игру только в свой ход.", false));

    //NAY-002: HARDCODED_BEHAVIOUR
    //К сожалению, таблица сокровищ-доспехов не предусматривала поле "большой"
    //Т.к. на ДАННЫЙ МОМЕНТ имеется лишь одна шмотка "Мифрильная броня", имеющая тип "большая"
    //Я не буду дописывать в таблицу целое поле и дополнительно его парсить.
    //Ниже сделаю привязку к конкретному Card-ID

    //Ан-нет, я сделал это ещё тогда. =))))
    if (player->GetThereIsLimitOnBigThings() && player->GetThereIsOneBigThing()
            && (card->size() == Size::Big))
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(false, "К сожалению, у Вас уже есть большие шмотки в игре!", false));

    //Запреты кончились, теперь принятие решения о том, какой параметр ставить для активна/неактивна

    //Наличие карты "Чит" пока не рассматривается

    if (card->isOnlyForDwarf()
            && player->GetRace() != Race::Dwarf
            && player->GetSecondRace() != Race::Dwarf)
    {
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Увы, карта активна только для дворфа!\n Разве вы дфорф?", false));
    }

    if (card->isOnlyForGnome()
            && player->GetRace() != Race::Gnome
            && player->GetSecondRace() != Race::Gnome)
    {
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Увы, карта активна только для гнома!\n Разве вы гном?", false));
    }

    if (card->isOnlyForWizard()
            && player->GetProfession() != Profession::Wizard
            && player->GetSecondProfession() != Profession::Wizard)
    {
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Увы, карта активна только для волшебника!\n"
                                            "Разве к вам в детстве прилетала сова с письмом?\n"
                                            "...Но ведь вы её ждали?\n", false));
    }

    if (card->isOnlyForHuman()
            && player->GetRace() != Race::Human)
    {
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Увы, карта активна только для человека./n Теперь вы другой.", false));
    }

    if (card->isRestrictedToGnome() &&
            ((player->GetRace() == Race::Gnome) || (player->GetSecondRace() == Race::Gnome))
            && !player->GetIsHalfBloodWithoutSecondRace())
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Увы, этот доспех \n не могут носить гномы.", false));

    if (card->isRestrictedToWizard() &&
            ((player->GetProfession() == Profession::Wizard) || (player->GetSecondProfession() == Profession::Wizard))
            && !player->GetIsSuperMunchkinWithoutSecondProfession())
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Увы, этот доспех \n слишком тяжёл для магов.", false));

    //NAY-002: EXPECTED_ERROR
    //NAY-002: EXPECTED_IMPROVEMENT
    //На будущее надо бы сделать защиту от возможности надеть сразу два "комбинируемых" доспеха.
    //С другой стороны, может юыть, их можно надевать по несколько - капусточка. =)))
    if (player->GetLegsSlotIsFull() && (card->GetBodyPart()  == Body_Part::Feet) && (!card->isCombined()))
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Вторые ботинки поверх существующих\n никак не надеть.\n Но при большом желании...", false));

    if (player->GetArmorSlotFull() && (card->GetBodyPart()  == Body_Part::Armor) && (!card->isCombined()))
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Доспех надевали поверх кольчуги.\n Но игра такое, увы, запрещает.", false));

    if (player->GetHeadSlotIsFull() && (card->GetBodyPart()  == Body_Part::Head) && (!card->isCombined()))
        return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "Две головы лучше, чем \n две шапки на одной.", false));


    //Запретов больше нет
    return std::make_shared<TreasureArmorAllowance>(TreasureArmorAllowance(true, "", true));
}

void The_Game::ImplementTreasureArmorToCardsInGame(std::shared_ptr<CardPlayAllowanceBase> allowance, const GameCardBasis *card, GamerWidget *wt, PositionedCard posCard)
{
    std::shared_ptr<TreasureArmorAllowance> armorAllowance = std::static_pointer_cast<TreasureArmorAllowance>(allowance);

    SaveGamePhase();
    SetGamePhase(GamePhase::CardAnimation);

    Animation_PassPlayedCardToCardsInGame_Phase1(wt, posCard, armorAllowance->GetIsActive());

    const gameCardTreasureArmor* cardPointer = static_cast<const gameCardTreasureArmor* >(card);
    gameCardTreasureArmor realCard(cardPointer);
    wt->SlotAddCardToCardsInGame(std::make_pair(armorAllowance->GetIsActive(), SimpleCard(true, realCard.GetCardID())));

    //Удалить карту с руки здесь же
    RemoveTheCardFromHand(wt, posCard.GetCard());
    MoveCardFromCardInHandToCardInGame(wt->GetPointerToPlayer(), std::make_pair(armorAllowance->GetIsActive(), SimpleCard(true, realCard.GetCardID())));

    if (!armorAllowance->GetIsActive())
        ApplyCardImplementerMessage(armorAllowance->GetReasonOfRestriction(), true);
    else
        ApplyNewArmor(wt, realCard);
}

std::shared_ptr<TreasureLevelUpAllowance> The_Game::GetAllowanceTreasureLevelUp(const gameCardTreasureLevelUp *card, Player *player, bool fromHand)
{

    //Карты получения уровней могут иметь специальные особенности применения.
    //Некоторые из них можно использловать только после боя ("Поглумись над трупами"),
    //Некоторые можно использовать только при определённых условиях ("Пришей Наёмничка");

    if (card->hasSpecialMechanic())
    {
        //Проверить, применима ли в этот момент
        return std::make_shared<TreasureLevelUpAllowance>(TreasureLevelUpAllowance(false, "У карты есть специальная механика. Ещё не имплементирована.", false));
    }
    else
    {
        //Карта применима в любой момент.
        return std::make_shared<TreasureLevelUpAllowance>(TreasureLevelUpAllowance(true, "", true));
    }
}

void The_Game::ImplementTreasureLevelUpCard(std::shared_ptr<CardPlayAllowanceBase> allowance, const GameCardBasis *card, GamerWidget *wt, PositionedCard posCard)
{
    std::shared_ptr<TreasureLevelUpAllowance> levelUpAllowance = std::static_pointer_cast<TreasureLevelUpAllowance>(allowance);
    SaveGamePhase();
    SetGamePhase(GamePhase::CardAnimation);
    qDebug() << "NAY-002: Animation_Phase1 played!";

//    Добавить в сброс
    AddCardToFoldStack(posCard.GetCard());
    //Анимация добавит. Это, конечно, костыль, зато выглядит симпатичнее
    //В последствии переработать логику во всех местах:
    //Во все ответственные кард-холдеры карта добавляется сразу, а анимация отображается
    //Independantly. Make sure I will make special class CardHolder, responsible for the cards
    //Positioning, Location, etc.
    //Not to use heavy functions while playing the card itself.


    //Добавить в отображатель последнего сброса
    _lastFold = {posCard.GetCard()};

    //Установить новый уровень и Боевую Силу
    wt->GetPointerToPlayer()->SetPlayerLevel(wt->GetPointerToPlayer()->GetPlayerLevel() + 1);
    wt->GetPointerToPlayer()->SetBattlePower(wt->GetPointerToPlayer()->GetBattlePower() + 1);

    //Отобразить изменения
    wt->SlotChangeTheGamerLevel(1);

    //Удалить карту с руки
    RemoveTheCardFromHand(wt, posCard.GetCard());
    wt->GetPointerToPlayer()->RemoveGivenCardFromHand(posCard.GetCard());

    //Отобразить анимацию попадания карты в сброс напрямую с руки
    //(пригодится в дальнейшем)
    Animation_PassCardFromHandToTreasureFold_Phase1(wt, posCard);

}

std::shared_ptr<TreasureWeaponAllowance> The_Game::GetAllowanceTreasureWeapon(const gameCardTreasureWeapon *card, Player *player, bool fromHand)
{
    //Все подобные парсеры предполагают, что проверка на глобальные запреты уже пройдена.
    //На 11.12.2018 это только процесс анимирования карт (карт-процессинг CardProcessing)

    //Играть карту "Оружие" можно в любой момент игры, кроме собственного боя.
    //Причём она может быть как "активной, так и не активной"

    //MunRules
    //https://hobbyworld.ru/download/rules/m_color_rules.pdf
    //https://hobbyworld.ru/chastie-voprosi-po-manchkin#cardsitems

    //Запреты на применение оружие такие же, как и для брони,
    //но к ним добавляются ограничения, связанные с количеством "рук".

    //1) большая шмотка
    //2) "только для"
    //3) "запрещено для"
    //4) число рук

    //logger.Debug() << "NAY-002:: Debugging Weapon Implementation: Getting Weapon Allowance.";

    //Проверка, что нет боя:
    if (GetCurrentGamePhase() == GamePhase::Battle)
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(false, "Странное дело, но в бою нельзя брать в руки дополнительное оружие. "
                                                                                        "Готовьтесь заранее!", false));

    //NAY-002: REWORK. Оружие, как и броню, можно выкладывать в чужой ход!
    if (GetCurrentGamePhase() == GamePhase::OtherPlayerMove)
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(false, "Сейчас чужой ход. Броню можно вводить в игру только в свой ход.", false));

    if (player->GetThereIsLimitOnBigThings() && player->GetThereIsOneBigThing()
            && ((card->GetSize() == Size::Big) && !CardIsSiegeEngine(card)))
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(false, "К сожалению, у Вас уже есть большие шмотки в игре!", false));

    if (card->isOnlyForElf()
            && player->GetRace() != Race::Elf
            && player->GetSecondRace() != Race::Elf)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для эльфа!\n Разве вы эльф?", false));
    }

    if (card->isOnlyForDwarf()
            && player->GetRace() != Race::Dwarf
            && player->GetSecondRace() != Race::Dwarf)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для дворфа!\n Разве вы дфорф?", false));
    }

    if (card->isOnlyForHuman()
            && player->GetRace() != Race::Human)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для человека./n Теперь вы другой.", false));
    }

    if (card->isOnlyForOrk()
            && player->GetRace() != Race::Ork
            && player->GetSecondRace() != Race::Ork)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для орка./n Вы не орк.", false));
    }

    if (card->isOnlyForHalfling()
            && player->GetRace() != Race::Halfling
            && player->GetSecondRace() != Race::Halfling)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Фродо Бэггинс любил эту карту./n А вы не халфлинг.", false));
    }

    if (card->isOnlyForGnome()
            && player->GetRace() != Race::Gnome
            && player->GetSecondRace() != Race::Gnome)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для гнома!\n Разве вы гном?", false));
    }

    if (card->isOnlyForWizard()
            && player->GetProfession() != Profession::Wizard
            && player->GetSecondProfession() != Profession::Wizard)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для волшебника!\n"
                                            "Разве к вам в детстве прилетала сова с письмом?\n"
                                            "...Но ведь вы её ждали?\n", false));
    }

    if (card->isOnlyForWarrior()
            && player->GetProfession() != Profession::Warrior
            && player->GetSecondProfession() != Profession::Warrior)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для воина!\n"
                                            "А ты и меч-бастард в руках не удержишь!", false));
    }

    if (card->isOnlyForThief()
            && player->GetProfession() != Profession::Thief
            && player->GetSecondProfession() != Profession::Thief)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для вора!\n"
                                            "А вы ещё ничего не украли!", false));
    }

    if (card->isOnlyForBard()
            && player->GetProfession() != Profession::Bard
            && player->GetSecondProfession() != Profession::Bard)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для барда!\n"
                                            "Ах, какая невезуха! Нет ни голоса, ни слуха! ", false));
    }

    if (card->isOnlyForCleric()
            && player->GetProfession() != Profession::Cleric
            && player->GetSecondProfession() != Profession::Cleric)
    {
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для клерика!\n"
                                            "Вы не клерик!", false));
    }

    if (card->isOnlyForMan() && player->GetPlayerSex() != PlayerSex::Man)
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для мужчин!\n"
                                            "Мои извинения, леди!", false));

    if (card->isOnlyForWoman() && player->GetPlayerSex() != PlayerSex::Woman)
        return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Увы, карта активна только для женщин!\n", false));

    //Проверить колличество свободных рук!
    {
        logger.Debug() << "NAY-002: Necessary Hands for card: " << card->GetNecessaryHands();
        logger.Debug() << "NAY-002: Free hands the player has: " << player->GetFreeHands();
        if (card->GetNecessaryHands() > static_cast<int32_t>(player->GetFreeHands()))
            return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "Не хватает рук, чтобы удержать!\n", false));

    }

    //Запретов больше нет!
    return std::make_shared<TreasureWeaponAllowance>(TreasureWeaponAllowance(true, "", true));
}

void The_Game::ImplementTreasureWeapon(std::shared_ptr<CardPlayAllowanceBase> allowance, const GameCardBasis *card, GamerWidget *wt, PositionedCard posCard)
{
    std::shared_ptr<TreasureWeaponAllowance> weaponAllowance = std::static_pointer_cast<TreasureWeaponAllowance>(allowance);

    SaveGamePhase();
    SetGamePhase(GamePhase::CardAnimation);

    Animation_PassPlayedCardToCardsInGame_Phase1(wt, posCard, weaponAllowance->GetIsActive());

    const gameCardTreasureWeapon* cardPointer = static_cast<const gameCardTreasureWeapon* >(card);
    gameCardTreasureWeapon realCard(cardPointer);
    wt->SlotAddCardToCardsInGame(std::make_pair(weaponAllowance->GetIsActive(), SimpleCard(true, realCard.GetCardID())));

    //Удалить карту с руки здесь же
    RemoveTheCardFromHand(wt, posCard.GetCard());
    //Осадная машина ПО УМОЛЧАНИЮ добавляется НЕАКТИВНОЙ - даже если её МОЖНО использовать!
    //EXPECTED_ERROR
    //Всё равно требуется проверить работу с осадкой. Хоть сейчас она и продаётся корректно, и устанавливается ПЕРЕД БОЕМ
    //Корректно
    MoveCardFromCardInHandToCardInGame(wt->GetPointerToPlayer(),
                                       std::make_pair(weaponAllowance->GetIsActive() && !CardIsSiegeEngine(cardPointer),
                                       SimpleCard(true, realCard.GetCardID())));

    if (!weaponAllowance->GetIsActive())
        ApplyCardImplementerMessage(weaponAllowance->GetReasonOfRestriction(), true);
    else
        ApplyNewWeapon(wt, realCard);
}

std::shared_ptr<TreasureArmorAmplifiersAllowance> The_Game::GetAllowanceTreasureArmorAmplifiers(const gameCardTreasureArmorAmplifier *card, Player *player, bool fromHand)
{

    //Согласно назначению этих вещей проверить следует следующее:
    //1. Есть ли у игрока вещи, к которым можно применять усилители
    //И, кажется, всё.
    //Начинать с обычных "фазовых" проверок

    Q_UNUSED(fromHand);

    //Проверка, что нет боя:
    if (GetCurrentGamePhase() == GamePhase::Battle)
        return std::make_shared<TreasureArmorAmplifiersAllowance>
                (TreasureArmorAmplifiersAllowance(false,
                                                  "В бою нельзя применять улучшения!"
                                                  "Готовьтесь заранее!", {}));

    //NAY-002: REWORK. Вещи можно улучшать в чужой ход!
    if (GetCurrentGamePhase() == GamePhase::OtherPlayerMove)
        return std::make_shared<TreasureArmorAmplifiersAllowance>
                (TreasureArmorAmplifiersAllowance(false,
                                                  "Сейчас чужой ход. Улучшайте вещи"
                                                  " только в свой ход.", {}));

    //Далее проверка по вещам.
    //Три из них применяются ТОЛЬКО к шмоткам с БОЕВЫМ бонусом
    //Одна - к БОЛЬШИМ шмоткам. Причём я решил запретить её применение к Осадной машине
    //Применение этих шмоток к картам других игроков ЗАПРЕЩЕНО

    if (ArmorAmplifierIsConvinientHandles(card->cardID()))
    {
        //Проверить, что есть большие шмотки, и при этом НЕ ОСАДНАЯ МАШИНА
        //Но она, кстати, по моему алгоритму, не добавляет себя как большая.
        if (player->GetThereIsOneBigThing()) // должен устанавливаться даже в том случае, если игрок- дворф!!!!
        {
            //Составить вектор с АйДи больших карт
            //В руках могут быть только сокровища, по этому придётся проверять среди всех сокровищ, которые
            //Могут быть большими - а это ТОЛЬКО ОРУЖИЕ И БРОНЯ

            std::vector<ActiveIncativeCard> result = GetBigThingsInGame(player);
            if (result.empty())
                return std::make_shared<TreasureArmorAmplifiersAllowance>
                        (TreasureArmorAmplifiersAllowance(false,
                                                          "У вас нет вещей, к которым"
                                                          " можно приделать"
                                                          " удобные ручки!", {}));
            else
                return std::make_shared<TreasureArmorAmplifiersAllowance>
                        (TreasureArmorAmplifiersAllowance(true, "", result));
        }
    }
    else
    {
        //Получить карты, имеющие бонус (можно и неактивные)
        std::vector<ActiveIncativeCard> result = GetThingsWithBonusesInGame(player);
        //Продолжить здесь 06.03
        if (result.empty())
            return std::make_shared<TreasureArmorAmplifiersAllowance>
                    (TreasureArmorAmplifiersAllowance(false,
                                                      "У вас нет вещей, дающих бонус,"
                                                      " которые можно улучшить"
                                                      " этой картой", {}));
        else
            return std::make_shared<TreasureArmorAmplifiersAllowance>
                    (TreasureArmorAmplifiersAllowance(true, "", result));
    }

    logger.Error() << "GetAllowanceTreasureArmorAmplifiers:: ERROR. Should never be here!";

    return std::make_shared<TreasureArmorAmplifiersAllowance>
            (TreasureArmorAmplifiersAllowance(false, "Ошибка!", {}));

}

std::vector<ActiveIncativeCard> The_Game::GetBigThingsInGame(const Player *player)
{
    //В игре нет ДВУХ ухватистых ручек, так что проверять здесь сразу на "уже улучшенность"
    //Нет смысла

    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;
    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;

    std::vector<ActiveIncativeCard> result;

    for (std::vector<SimpleCard>::iterator it = player->GetActiveCardsInGame().begin();
         it != player->GetActiveCardsInGame().end(); ++it)
    {
        _weaponsIterator = _weaponsDeck.find(static_cast <int> (it->second));
        if (_weaponsIterator != _weaponsDeck.end())
            result.push_back(std::make_pair(true, SimpleCard(true, it->second)));

        _armorIterator = _armorDeck.find(static_cast <int> (it->second));
        if (_armorIterator != _armorDeck.end())
            result.push_back(std::make_pair(true, SimpleCard(true, it->second)));
    }

    for (std::vector<SimpleCard>::iterator it = player->GetDisabledCardsInGame().begin();
         it != player->GetDisabledCardsInGame().end(); ++it)
    {
        _weaponsIterator = _weaponsDeck.find(static_cast <int> (it->second));
        if (_weaponsIterator != _weaponsDeck.end())
            result.push_back(std::make_pair(false, SimpleCard(true, it->second)));

        _armorIterator = _armorDeck.find(static_cast <int> (it->second));
        if (_armorIterator != _armorDeck.end())
            result.push_back(std::make_pair(false, SimpleCard(true, it->second)));

    }

    return result;
}

std::vector<ActiveIncativeCard> The_Game::GetThingsWithBonusesInGame(const Player *player)
{
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;
    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;

    std::vector<ActiveIncativeCard> result;

    for (std::vector<SimpleCard>::iterator it = player->GetActiveCardsInGame().begin();
         it != player->GetActiveCardsInGame().end(); ++it)
    {
        _weaponsIterator = _weaponsDeck.find(static_cast <int> (it->second));
        if (_weaponsIterator != _weaponsDeck.end())
            if (_weaponsIterator->second.GetBonus())
                result.push_back(std::make_pair(true, SimpleCard(true, it->second)));

        _armorIterator = _armorDeck.find(static_cast <int> (it->second));
        if (_armorIterator != _armorDeck.end())
            if (_armorIterator->second.GetBonus())
                result.push_back(std::make_pair(true, SimpleCard(true, it->second)));
    }

    for (std::vector<SimpleCard>::iterator it = player->GetDisabledCardsInGame().begin();
         it != player->GetDisabledCardsInGame().end(); ++it)
    {
        _weaponsIterator = _weaponsDeck.find(static_cast <int> (it->second));
        if (_weaponsIterator != _weaponsDeck.end())
            if (_weaponsIterator->second.GetBonus())
                result.push_back(std::make_pair(false, SimpleCard(true, it->second)));

        _armorIterator = _armorDeck.find(static_cast <int> (it->second));
        if (_armorIterator != _armorDeck.end())
            if (_armorIterator->second.GetBonus())
                result.push_back(std::make_pair(false, SimpleCard(true, it->second)));

    }

    return result;
}

bool The_Game::CardIsBigThing(SimpleCard card)
{
    return true;
}

bool The_Game::CardIsWeapon(SimpleCard card)
{
    return true;
}

void The_Game::ShowCardIsForbiddenToPlayMessage(const QString &message)
{
    qDebug() << "NAY-002: Show Card is forbiden to play message: " << message;
}

void The_Game::ApplyNewArmor(GamerWidget* wt, const gameCardTreasureArmor &card, CardApplyMode apply)
{    
    //Получить указатель на игрока
    //Т.к. эти функции в т.ч. должны менять и глобальные отображения
    //они должны иметь доступ к указателю в т.ч. и на виджет, чтобы
    //ничего из себя наружу не возвращать, т.к. по своей сути они
    //выполняют законченное действие
    Player* player = wt->GetPointerToPlayer();

    bool addEffect = true;

    if (apply == CardApplyMode::Remove)
       addEffect = false;


    uint32_t totalBonus = static_cast<uint32_t>(card.GetBonus());

    if (card.GetAdditionalBonusforElf() &&
        ((player->GetRace() == Race::Elf) || (player->GetSecondRace() == Race::Elf)))
        totalBonus += static_cast<uint32_t>(card.GetAdditionalBonusforElf());

    if (card.GetAdditionalBonusforOrk() &&
        ((player->GetRace() == Race::Ork) || (player->GetSecondRace() == Race::Ork)))
        totalBonus += static_cast<uint32_t>(card.GetAdditionalBonusforOrk());

    //кажется, нет смысла проверять, есть ли такой бонус.
    //Парсер написан так, что должен вписывать в эти поля нули.
    //Можно перестраховаться, добавив куда можно, нулевые значения
    //Может возникнуть ошибка при установке бонусов.
    //NAY-002: EXPECTED_IMPROVEMENT
    //NAY-002: EXPECTED_ERROR

    if (card.hasSpecialMechanic()) //FlamingArmor
    {
        qDebug() << "NAY-002: cardID: " << card.GetCardID();

        switch (card.GetCardID())
        {
            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::AwfulSocks):
                player->SetNotAbleToHelp(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::FlamingArmor):
                player->SetHasFireArmor(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::FreudianSlippers):
                player->SetIsAbleToChangeSexOnline(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::HelmOfPeripherialVision):
                player->SetIsProtectedFromTheft(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::MagnificentHat):
                player->SetHasCursesMirroring(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::SandalsOfProtection):
                player->SetIsProtecetedFromCursesFromDoors(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureArmor::TinfoilHat):
                player->SetIsProtectedFromCursesFromPlayers(true && addEffect);
                break;

            default:
                qDebug() << "NAY-002: ERROR While void The_Game::ApplyNewArmor(const gameCardTreasureArmor *card)"
                            "if (card->hasSpecialMechanic()) : No special mechanic assigned!";
                break;
        }
    }

    //Добавление обычных бонусов:

    if (addEffect)
    {
        player->SetFleeChance(_mainPlayer->GetFleeChance() + card.bonusToFleeing());
        player->SetBattlePower(static_cast<int32_t>(_mainPlayer->GetBattlePower() + static_cast<int32_t>(totalBonus)));
    }
    else
    {
        player->SetFleeChance(_mainPlayer->GetFleeChance() - card.bonusToFleeing());
        player->SetBattlePower(static_cast<int32_t>(_mainPlayer->GetBattlePower() - static_cast<int32_t>(totalBonus)));
   }


    //Установка карты в слот
    //слоты такой картой не занимаются
    if (card.GetBodyPart() == Body_Part::Armor)
    {
        if (card.isCombined())
            player->SetCombinedArmor(_mainPlayer->GetCombinedArmor() + (addEffect ? 1 : -1));
        else
            player->SetArmorSlotFull(true && addEffect);
    }
    if (card.GetBodyPart() == Body_Part::Feet)
    {
        if (card.isCombined())
            player->SetCombinedArmor(_mainPlayer->GetCombinedFeet() + (addEffect ? 1 : -1));
        else
            player->SetLegsSlotIsFull(true && addEffect);
    }
    if (card.GetBodyPart() == Body_Part::Head)
    {
        if (card.isCombined())
            player->SetCombinedHead(_mainPlayer->GetCombinedHead() + (addEffect ? 1 : -1));
        else
            player->SetHeadSlotIsFull(true && addEffect);
    }

    //Теперь  можно передать карту анимации
    //Анимация должна отдать карту в cardsInGameObserver
    //Анимацией занимается другая функция

    wt->SlotChangeTheGamerBattlePower(static_cast<int32_t>(addEffect ? totalBonus : -totalBonus));
}

void The_Game::ApplyNewWeapon(GamerWidget *wt, const gameCardTreasureWeapon &card, CardApplyMode apply)
{
    Player* player = wt->GetPointerToPlayer();

    bool addEffect = true;

    if (apply == CardApplyMode::Remove)
       addEffect = false;

    //добавить основной бонус
    uint32_t totalBonus = static_cast<uint32_t>(card.GetBonus());

    //Дополнительные бонусы оружие даёт только против типов противников.
    //Соответсвенно такие бонусы должны быть записаны в свойства игрока.

    player->SetAdditionalBonusAgainst_J(card.GetAdditionalBonusAgainst_J());
    player->SetAdditionalBonusAgainstUndead(card.GetAdditionalBonusAgainstUndead());

    player->SetAutomaticLooseToCalmadzilla(card.GetAutomaticLooseToCalmadzila());


    //Процедура, приведённая ниже, добавит или уберёт эффект
    if (card.GetHasSpecialMechanic()) //Добавить сюда описание специальных функций, которые появляются у игрока.
    {
//        logger.Debug() << "NAY-002: cardID: " << card.GetCardID();

        switch (card.GetCardID())
        {
            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureWeapon::BoomDagger):
                player->SetHasBoomDagger(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureWeapon::StabAMatic):
                player->SetHasStabAMatic(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureWeapon::RatOnAStick):
                player->SetHasRatOnAStick(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureWeapon::SiegeEngine):
                player->SetHasSiegeEngine(true && addEffect);
                break;

            case static_cast<uint32_t>(CardsWithSpecialFunctions_TreasureWeapon::TubaOfCharm):
                player->SetHasTubaOfCharm(true && addEffect);
                break;

            default:
                logger.Error() << "NAY-002: ERROR While void "
                                  "The_Game::ApplyNewWeapon: "
                                  "No special mechanic assigned!";
                break;
        }
    }

    //Добавление (удаление) обычных бонусов, КРОМЕ ОСАДНОЙ машины:
    //RULE_NOTE-001
    if (addEffect)
    {
        //Бонус к смывке. Проверить, работает ли.
        //Добавлять только в том случае, если это не осадка.
        //Она влияет на бонус только если активна. Её активация - вопрос, который выносится на начало каждого боя.
        //По умолчанию она должна рассматриваться НЕактивной.
        //RULE_NOTE-001
        logger.Essential() << "NAY-002: AddNewWeapon is adding FleeChance Bonus! Check the procedure!";
        logger.Essential() << "NAY-002: Flee chance was: " << player->GetFleeChance();
        logger.Essential() << "NAY-002: Flee chance is expected to be added: " << card.GetBonusToFlee();
        if (!CardIsSiegeEngine(&card))
            player->SetFleeChance(_mainPlayer->GetFleeChance() - card.GetBonusToFlee());
        logger.Essential() << "NAY-002: Flee chance resulted: " << player->GetFleeChance();

        if (!CardIsSiegeEngine(&card))
            player->SetBattlePower(static_cast<int32_t>(_mainPlayer->GetBattlePower() + static_cast<int32_t>(totalBonus)));
    }
    else
    {
        player->SetFleeChance(_mainPlayer->GetFleeChance() + card.GetBonusToFlee());
        player->SetBattlePower(static_cast<int32_t>(_mainPlayer->GetBattlePower() - static_cast<int32_t>(totalBonus)));
    }


    //Процедура изменения колличества свободных рук ()
    //Разрешениев этот момент уже получено.
    //Разрешение надо выдавать в том числе и тогда, когда нет свободных рук,
    //Но применяется "двурукий меч" - он в любом случае добавит ещё одну руку
    if (addEffect)
    {
        //Меч должен добавить одну руку!
        logger.Essential() << "NAY-002: Free Hands Before Applying Weapon: " << player->GetFreeHands();
        //В функции - сумма. Если передать туда отрицательное число, то число свободных рук уменьшится
        //Двурукий меч, наоборот, добавит единичку
        if (!CardIsSiegeEngine(&card))
            player->ChangeFreeHands((-1) * card.GetNecessaryHands());
        logger.Essential() << "NAY-002: Free Hands After Applying Weapon Effect: " << player->GetFreeHands();
    }
    else
    {
        logger.Essential() << "NAY-002: Free Hands Before Applying Weapon: " << player->GetFreeHands();
        if (!CardIsSiegeEngine(&card))
            player->ChangeFreeHands(card.GetNecessaryHands());
        logger.Essential() << "NAY-002: Free Hands After Applying Weapon Effect: " << player->GetFreeHands();
    }

    //ADD_LATER
    //При потере двурукого меча число рук может уменьшиться ниже требуемого значения
    //Здесь это требуется проверить, и автоматически деактивировать карту(ы) оружия,
    //Для которых теперь не хватает рук.
    //bool CheckHandsSufficience();

    //Теперь  можно передать карту анимации
    //Анимация должна отдать карту в cardsInGameObserver
    //Анимацией занимается другая функция

    //Должен удалить эффект осадки в случае если Применитель вызван с фалгом "удалить"
    if (!CardIsSiegeEngine(&card) && addEffect)
        wt->SlotChangeTheGamerBattlePower(static_cast<int32_t>(addEffect ? totalBonus : -totalBonus));
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
    connect(animation, &QPropertyAnimation::destroyed,
            []{qDebug() << "NAY-002: DEBUGPassTheCardToTheBattleField() destroyed";});
    //_movingCard->deleteLater();
}

void The_Game::Animation_StartPassSoldCardsFromHandOrInGameToTreasureFold_Phase1(GamerWidget *wt, std::vector<std::pair<PositionedCard, bool> > cards)
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
        PositionedCard card = cards[var].first;

        QPushButton* _movingCard = new QPushButton("Animated Button", this);
        cardsAsButtons.push_back(_movingCard);


        QPoint relativeCardPostionTopLeft;
        QPoint relativeCardPostionBottomRight;
        QPoint gamerWidgetPosition = wt->ProvideSelfPosition();
        int sizeX;
        int sizeY;
        if (cards[var].second)
        {
            QPoint handPosition = wt->ProvideHandPosition();
            relativeCardPostionTopLeft = card.GetPositionTopLeft() + gamerWidgetPosition + handPosition;
            relativeCardPostionBottomRight = card.GetPositionBottomRight() + gamerWidgetPosition + handPosition;
            sizeX = relativeCardPostionBottomRight.x() - relativeCardPostionTopLeft.x() ;
            sizeY = relativeCardPostionBottomRight.y() - relativeCardPostionTopLeft.y();
        }
        else
        {
            QPoint cardsInGamePosition = wt->ProvideCardsInGamePosition();
            relativeCardPostionTopLeft = gamerWidgetPosition + cardsInGamePosition;
            relativeCardPostionBottomRight = gamerWidgetPosition + cardsInGamePosition;

            QSize size= wt->ProvideCardOnHandSize();

            if (var % 2)
            {
                relativeCardPostionTopLeft.setX(relativeCardPostionTopLeft.x() + var*size.width());
                relativeCardPostionBottomRight.setX(relativeCardPostionBottomRight.x() + var*size.width());
            }
            else
            {
                relativeCardPostionTopLeft.setX(relativeCardPostionTopLeft.x() - var*size.width());
                relativeCardPostionBottomRight.setX(relativeCardPostionBottomRight.x() - var*size.width());
            }

            sizeX = size.width();
            sizeY = size.height();
        }

        _movingCard->move(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y());

        //qDebug() << "Size of the Card during moving: X: " << sizeX;
        //qDebug() << "Size of the Card during moving: Y: " << sizeY;

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
        _movingCard->show();

        QPropertyAnimation *animation = new QPropertyAnimation(_movingCard, "geometry");
        animations.push_back(animation);
        animation->setDuration(static_cast<uint32_t>(_msTimeForTradeAnimationPhase1));
        animation->setStartValue(QRect(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y(), sizeX, sizeY));
        animation->setEndValue(QRect(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2));
        animation->setEasingCurve(QEasingCurve::OutCubic);

        connect(animation, &QPropertyAnimation::destroyed,
                [animations]{qDebug() << "NAY-002: Animation_StartPassSoldCardsFromHandToTreasureFold_Phase1() destroyed. ID: " << animations.size();});
    }

    std::vector<PositionedCard> castedBackCards;
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        castedBackCards.push_back(cards[var].first);
    }

    connect(animations[0], &QPropertyAnimation::finished,
            [this, animations, cardsAsButtons, castedBackCards]
            {Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2(animations, cardsAsButtons, castedBackCards);});

    for (uint32_t var = 0; var < animations.size(); ++var)
    {
        animations[var]->start(QAbstractAnimation::KeepWhenStopped);
    }
}

void The_Game::Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2(std::vector<QPropertyAnimation*>animations, std::vector<QPushButton*> movedCards, const std::vector<PositionedCard>& cards)
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
    if (animations.size() != movedCards.size())
    {
        qDebug() << "NAY-002: ERROR WHILE Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2()."
                    "animations.size() != movedCards.size()";
        return;
    }

    uint32_t sizeHeight = static_cast<uint32_t>(movedCards[0]->height());
    uint32_t totalWidthNecessary =static_cast<uint32_t>(movedCards.size() * movedCards[0]->width());
    QPoint CardMostToTheLeftPosition = GetCenterPosition()
            - QPoint(static_cast<uint32_t>(totalWidthNecessary/2), movedCards[0]->pos().y());

    for (uint32_t var = 0; var < movedCards.size(); ++var)
    {  
        animations[var]->setDuration(static_cast<uint32_t>(_msTimeForTradeAnimationPhase2));
        animations[var]->setStartValue(QRect(movedCards[var]->pos().x(), movedCards[var]->pos().y(),
                                       movedCards[var]->size().width(), movedCards[var]->size().height()));
        animations[var]->setEndValue(QRect(CardMostToTheLeftPosition.x() +var*movedCards[var]->size().width(), movedCards[var]->pos().y(),
                                     movedCards[var]->size().width(), movedCards[var]->size().height()));
        animations[var]->setEasingCurve(QEasingCurve::OutCubic);

        connect(animations[var], &QPropertyAnimation::destroyed,
                [animations]{qDebug() << "NAY-002: Animation_StartPassSoldCardsFromHandToTreasureFold_Phase2() destroyed. ID: " << animations.size();});

    }

    //Соединить этот сигнал со слотом, который отображает анимацию третьей фазы сброса
    //проданных карт.
    connect(animations[0], &QPropertyAnimation::finished,
            [this,animations, movedCards, cards] {Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3(animations,movedCards, cards);});

    for (uint32_t var = 0; var < animations.size(); ++var)
    {
        animations[var]->start(QAbstractAnimation::KeepWhenStopped);
    }

}

void The_Game::Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3(std::vector<QPropertyAnimation*>animations, std::vector<QPushButton *> movedCards, const std::vector<PositionedCard> &cards)
{
    if (!movedCards.size())
    {
        qDebug() << "NAY-002: ERROR WHILE Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3()."
                    "Empty Vector!";
        return;
    }

    if (animations.size() != movedCards.size())
    {
        qDebug() << "NAY-002: ERROR WHILE Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3()."
                    "animations.size() != movedCards.size()";
        return;
    }

    std::vector<SimpleCard> cardsToBeProcessed;
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        cardsToBeProcessed.push_back(cards[var].GetCard());
    }

    QPoint EndPosition = GetTreasuresFoldPosition() + GetCardsStackPosition();
    QSize EndSize = GetTreasuresFoldSize();

    for (uint32_t var = 0; var < movedCards.size(); ++var)
    {
        animations[var]->setDuration(static_cast<uint32_t>(_msTimeForTradeAnimationPhase3));
        animations[var]->setStartValue(QRect(movedCards[var]->pos().x(), movedCards[var]->pos().y(),
                                       movedCards[var]->size().width(), movedCards[var]->size().height()));
        animations[var]->setEndValue(QRect(EndPosition.x(), EndPosition.y(),
                                     EndSize.width(), EndSize.height()));
        animations[var]->setEasingCurve(QEasingCurve::OutCubic);

        connect(animations[var], &QPropertyAnimation::destroyed,
                [animations]{qDebug() << "NAY-002: Animation_StartPassSoldCardsFromHandToTreasureFold_Phase3() destroyed. ID: " << animations.size();});

        //Соединить этот сигнал со слотом, который добавляет и отображает последнюю сброшенную карту в TreasuresFold.
        //До этого момента игра находится в фазе CardProcessing.
        connect(animations[var], &QPropertyAnimation::finished,
                movedCards[var], &QPushButton::deleteLater);
   }

    qDebug() << "NAY-002: Animations of Trade before starting: ";

    connect(animations[0], &QPropertyAnimation::finished,
            [this, cardsToBeProcessed]{ProcessFoldObserver(cardsToBeProcessed);});
    connect(animations[0], &QPropertyAnimation::finished,
            [this]{CheckThePlayerIsAbleToSell(_mainPlayer);});
    connect(animations[0], &QPropertyAnimation::finished,
            [this]{RestoreGamePhase();});
    std::vector<SimpleCard> castedToSimpleCards = PositionedCard::RevertToSimpleCardsVector(cards);
    connect(animations[0], &QPropertyAnimation::finished,
            [this, castedToSimpleCards]{ui->CardStacksWidget->SlotPassTheCardsToFoldStack(castedToSimpleCards);});

    for (uint32_t var = 0; var < animations.size(); ++var)
    {
        animations[var]->start(QAbstractAnimation::DeleteWhenStopped);
    }

}

QPushButton *The_Game::CreateButtonForAnimation(SimpleCard card, QPoint cardPostionTopLeft, QPoint cardPostionBottomRight, bool active)
{
    QPushButton* movingCard = new QPushButton("Animated Button", this);
    movingCard->move(cardPostionTopLeft.x(), cardPostionTopLeft.y());
    int sizeX = cardPostionBottomRight.x() - cardPostionTopLeft.x() ;
    int sizeY = cardPostionBottomRight.y() - cardPostionTopLeft.y();

    qDebug() << "Size of the Card during moving: X: " << sizeX;
    qDebug() << "Size of the Card during moving: Y: " << sizeY;

    QString picture = findTheCardPicture(card);

    QImage image(picture);

    QPixmap pxmp_movingCard;
    if (!active && _gameSettings.GetHardCodedSettings_ShowNotActiveCardAsGreyScale())
    {
        pxmp_movingCard = QPixmap::fromImage(image.convertToFormat(QImage::Format_Grayscale8));
    }
    else
        pxmp_movingCard = QPixmap::fromImage(image);

    QPalette plte_movingCard;
    plte_movingCard.setBrush(movingCard->backgroundRole(),
    QBrush(pxmp_movingCard.scaled(sizeX*2, sizeY*2, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    movingCard->setMaximumWidth(sizeX*2);
    movingCard->setMaximumHeight(sizeY*2);
    movingCard->setMinimumWidth(sizeX);
    movingCard->setMinimumHeight(sizeY);

    //http://www.prog.org.ru/topic_7215_0.html
    movingCard->setFlat(true);
    movingCard->setAutoFillBackground(true);
    movingCard->setPalette(plte_movingCard);
    movingCard->setText("");

    return movingCard;
}

void The_Game::Animation_PassPlayedCardToCardsInGame_Phase1(GamerWidget *wt, const PositionedCard &card, bool active)
{
    QPoint handPosition = wt->ProvideHandPosition();
    QPoint gamerWidgetPosition = wt->ProvideSelfPosition();

    QPoint relativeCardPostionTopLeft = card.GetPositionTopLeft() + gamerWidgetPosition + handPosition;
    QPoint relativeCardPostionBottomRight = card.GetPositionBottomRight() + gamerWidgetPosition + handPosition;

    int sizeX = relativeCardPostionBottomRight.x() - relativeCardPostionTopLeft.x() ;
    int sizeY = relativeCardPostionBottomRight.y() - relativeCardPostionTopLeft.y();

    QPushButton* movingCard = CreateButtonForAnimation(card.GetCard(),
                                                       relativeCardPostionTopLeft,
                                                       relativeCardPostionBottomRight,
                                                       active);
    movingCard->show();

    QPropertyAnimation *animation = new QPropertyAnimation(movingCard, "geometry");
    animation->setDuration(static_cast<int32_t>(_msTimeForApplyCardToCardsInGamePhase1));
    animation->setStartValue(QRect(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y(), sizeX, sizeY)); //initial card position
    QRect finalPosition(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2);
    animation->setEndValue(QRect(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2)); //centre
    animation->setEasingCurve(QEasingCurve::OutCubic);

    connect(animation, &QPropertyAnimation::destroyed,
            []{qDebug() << "NAY-002: Animation_PassPlayedCardToCardsInGame_Phase1 destroyed";});

    connect(animation, &QPropertyAnimation::finished,
            [this, wt, animation, movingCard]
    {(QTimer::singleShot(AnimationPhasesLimitations::msTimeToHoldCardWhileAddingCardToCardsInGame,
                         animation,
                         [this, wt, animation, movingCard]{Animation_PassPlayedCardToCardsInGame_Phase2(wt, animation, movingCard);}));});


    animation->start(QAbstractAnimation::KeepWhenStopped);
}

void The_Game::Animation_PassPlayedCardToCardsInGame_Phase2(GamerWidget *wt, QPropertyAnimation *animation, QPushButton* card)
{
    qDebug() << "NAY-002: Entering application Phase 2: ";

    QPoint EndPosition = GetPlayerWidgetSelfPosition(wt)
            + GetCardsInGamePosition(wt)
            + GetNewCardAddedToCardsInGamePosition(wt);

    QSize EndSize;
    if (!CardsInGameWidgetPerfomanceValues::threeLayoutForCardsAreEnabled)
    {
        EndSize.setWidth(_hwScreenSizeWidth*GeometricLimitations::handCardSizeWidht*GeometricLimitations::handCardMainGamerSizeRatio);
        EndSize.setHeight(_hwScreenSizeHeigh*GeometricLimitations::handCardSizeHeight*GeometricLimitations::handCardMainGamerSizeRatio);
    }
    else
    {
        EndSize.setWidth(_hwScreenSizeWidth*GeometricLimitations::handCardSizeWidht);
        EndSize.setHeight(_hwScreenSizeHeigh*GeometricLimitations::handCardSizeHeight);
    }

    if (animation == nullptr)
    {
        qDebug() << "EROR WHILE Animation_PassPlayedCardToCardsInGame_Phase2. NULLPTR!";
        return;
    }

    animation->setDuration(static_cast<int32_t>(_msTimeForApplyCardToCardsInGamePhase2));

    animation->setEndValue(QRect(EndPosition.x(), EndPosition.y(),
                                 EndSize.width(), EndSize.height()));
    animation->setEasingCurve(QEasingCurve::OutCubic);

    connect(animation, &QPropertyAnimation::destroyed,
            []{qDebug() << "NAY-002: Animation_PassPlayedCardToCardsInGame_Phase2 destroyed";});

    connect(animation, &QPropertyAnimation::finished,
            [this]{RestoreGamePhase();});

    qDebug() << "NAY-002: Connection: card->deleteLater()";
    connect(animation, &QPropertyAnimation::finished,
            card, &QPushButton::deleteLater);

    connect(animation, &QPropertyAnimation::finished,
            wt, &GamerWidget::SlotShowLastCardInGameAdded);

    connect(card, &QPushButton::destroyed,
            [] {qDebug() << "NAY-002: _movingCard->Destroyed";});

    QTimer::singleShot(1000, animation, [animation]{animation->start(QAbstractAnimation::DeleteWhenStopped);});

}

void The_Game::Animation_PassCardFromHandToTreasureFold_Phase1(GamerWidget *wt, PositionedCard card)
{
    QPushButton* _movingCard = new QPushButton("Animated Button", this);

    QPoint relativeCardPostionTopLeft;
    QPoint relativeCardPostionBottomRight;
    QPoint gamerWidgetPosition = wt->ProvideSelfPosition();
    int sizeX;
    int sizeY;
    if (card.GetCard().second)
    {
        relativeCardPostionTopLeft = card.GetPositionTopLeft() + gamerWidgetPosition + wt->ProvideHandPosition();
        relativeCardPostionBottomRight = card.GetPositionBottomRight() + gamerWidgetPosition + wt->ProvideHandPosition();
        sizeX = relativeCardPostionBottomRight.x() - relativeCardPostionTopLeft.x() ;
        sizeY = relativeCardPostionBottomRight.y() - relativeCardPostionTopLeft.y();
    }
    else
    {
        QPoint cardsInGamePosition = wt->ProvideCardsInGamePosition();
        relativeCardPostionTopLeft = gamerWidgetPosition + cardsInGamePosition;
        relativeCardPostionBottomRight = gamerWidgetPosition + cardsInGamePosition;

        QSize size= wt->ProvideCardOnHandSize();

        relativeCardPostionTopLeft.setX(relativeCardPostionTopLeft.x() + size.width());
        relativeCardPostionBottomRight.setX(relativeCardPostionBottomRight.x() + size.width());

        sizeX = size.width();
        sizeY = size.height();
    }

    _movingCard->move(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y());
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
    _movingCard->show();

    QPropertyAnimation *animation = new QPropertyAnimation(_movingCard, "geometry");
    animation->setDuration(static_cast<int32_t>(_msTimeForTradeAnimationPhase1));
    animation->setStartValue(QRect(relativeCardPostionTopLeft.x(), relativeCardPostionTopLeft.y(), sizeX, sizeY));
    animation->setEndValue(QRect(width()/2 - sizeX, height()/2 - sizeY, sizeX*2, sizeY*2));
    animation->setEasingCurve(QEasingCurve::OutCubic);

    connect(animation, &QPropertyAnimation::destroyed,
            []{qDebug() << "NAY-002: Animation_PassCardFromHandToTreasureFold_Phase1() destroyed. ID: ";});


    std::vector<PositionedCard> castedBackCards;

    connect(animation, &QPropertyAnimation::finished,
            [this, animation, _movingCard, wt, card]
    {(QTimer::singleShot(AnimationPhasesLimitations::msTimeToHoldCardWhileAddingCardToCardsInGame,
                         animation,
                         [this, animation, _movingCard, wt, card]{Animation_PassCardFromHandToTreasureFold_Phase2(wt, animation, _movingCard, card);}));});

    animation->start(QAbstractAnimation::KeepWhenStopped);
}

void The_Game::Animation_PassCardFromHandToTreasureFold_Phase2(GamerWidget *wt,
                                                               QPropertyAnimation *animation,
                                                               QPushButton *button, PositionedCard card)
{
    QPoint EndPosition = GetTreasuresFoldPosition() + GetCardsStackPosition();
    QSize EndSize = GetTreasuresFoldSize();

    animation->setDuration(static_cast<int32_t>(_msTimeForApplyCardToCardsInGamePhase2));

    animation->setEndValue(QRect(EndPosition.x(), EndPosition.y(),
                                 EndSize.width(), EndSize.height()));
    animation->setEasingCurve(QEasingCurve::OutCubic);

    connect(animation, &QPropertyAnimation::destroyed,
            []{qDebug() << "NAY-002: Animation_PassCardFromHandToTreasureFold_Phase2 destroyed";});

    qDebug() << "NAY-002: Connection: card->deleteLater()";
    connect(animation, &QPropertyAnimation::finished,
            button, &QPushButton::deleteLater);

    connect(animation, &QPropertyAnimation::finished,
            [this]{RestoreGamePhase();});

    connect(animation, &QPropertyAnimation::finished,
            [this, card]{ui->CardStacksWidget->SlotPassTheCardsToFoldStack({card.GetCard()});});

    connect(animation, &QPropertyAnimation::finished,
        [this, card]{ProcessFoldObserver({card.GetCard()});});

    QTimer::singleShot(1000, animation, [animation]{animation->start(QAbstractAnimation::DeleteWhenStopped);});

}

void The_Game::DEBUG_SlotAnimation_PassPlayedCardToCardsInGame_Phase2(GamerWidget *wt, QPropertyAnimation *animation, QPushButton *card)
{
    qDebug() << "NAY-002: PHASE_2 Started once";
    Animation_PassPlayedCardToCardsInGame_Phase2(wt, animation, card);
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
                currentPictureAddress = (*_weaponsIterator).second.GetPictureAddress();
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

    //NAY-001: EXPECTED_ERROR
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

    logger.Algorithm() << "NAY-001: Doors Stack is Filled Now!";

}

void The_Game::SetUpPlayersAndWidgets(uint32_t windowHeight, uint32_t windowWidth, const std::vector<QString> &playersOrder)
{
    uint32_t totalOpponents = _gameSettings.maximumNumberOfPlayers();
    logger.Debug() << "Total players from settings: " << totalOpponents;
    logger.Debug() << "Total players given by SetUp Opponents: " << playersOrder.size();

    _mainPlayer = new Player(_gameSettings.clientName());
    //Из-за того, что я сделал давным давно основного игрока также не динамически создаваемым,
    //получилась разница в сущностях. Неудобно разнобоко назначать одно и то же.
    //С другой стороны было очень удобно при создании и отладке.
    //Так что сохраню эту концепцию.
    ui->MainGamer->SetGamerName(_gameSettings.clientName());
    ui->MainGamer->SetPointerToPlayer(_mainPlayer);
    _roomMasterName = _playersOrder[0];
    SetIsRoomMaster(CheckIsMainPlayerTheRoomMaster(_playersOrder[0]));
    logger.Debug() << "NAY-002: Master's name: " << playersOrder[0];
    logger.Debug() << "NAY-002: Clients name: " << _gameSettings.clientName();
    //Set Players name:

    if (totalOpponents != playersOrder.size())
        logger.Error() << "ERROR while The_Game::SetUpOpponents(): Total opponents from settings"
                          "and given by server differs!";

    //Один из них может быть мастером!
    for (uint32_t var = 0; var < playersOrder.size(); ++var)
    {
        if (_gameSettings.clientName() != playersOrder[var])
        {
            Player* currentPlayer = new Player (playersOrder[var]);
            currentPlayer->SetPlayersName(playersOrder[var]);
            _playersOpponents.push_back(currentPlayer);
            logger.Debug() << "NAY-002: _playersOpponents Size: " << _playersOpponents.size();
        }
    }

    //Set-Up order Of move
    std::vector<Player*> orderOfMove;
    for (uint32_t var = 0; var < _playersOrder.size(); ++var)
    {
        if (_mainPlayer->GetPlayerName() == _playersOrder[var])
        {
            _mainGamerOrderOfMove = var;
            orderOfMove.push_back(_mainPlayer);
        }
        for (uint32_t y = 0; y < _playersOpponents.size(); ++y)
        {
            if (_playersOpponents[y]->GetPlayerName() == _playersOrder[var])
            {
                orderOfMove.push_back(_playersOpponents[y]);
                //NAY-002: EXPECTED_ERROR
                //To Test under 3 or more players.
                break;
            }
        }
    }

    //save the order;
    _orderOfMove = orderOfMove;

    logger.Debug() << "NAY-002: " << "Order of move: ";
    for (uint32_t var = 0; var < _orderOfMove.size(); ++var)
    {
        logger.Debug() << var << " " << _orderOfMove[var]->GetPlayerName();
    }

    uint32_t orderOfOpponent = 1;
    for (uint32_t var = 0; var < playersOrder.size(); var++)
    {

       if (_gameSettings.clientName() != playersOrder[var])
       {
           _widgets4Opponents.push_back(new GamerWidget());
           _GamerWidgetsWithIDs.insert(std::make_pair(var, _widgets4Opponents.back()));
           _widgets4Opponents.back()->RedrawAsASecondaryPlayer(orderOfOpponent);
           ++orderOfOpponent;
           _widgets4Opponents.back()->setIs_MainPlayer(false);
           _widgets4Opponents.back()->SetGamerName(playersOrder[var]);
           //NAY-002" EXPECTED ERROR
           //Проверить, что указатели точно устанавливаются.
           for (uint32_t y = 0; y < _playersOpponents.size(); ++y)
           {
                if (_playersOpponents[y]->GetPlayerName() == playersOrder[var])
                    _widgets4Opponents.back()->SetPointerToPlayer(_playersOpponents[y]);
           }

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
        connect(_widgets4Opponents[var], &GamerWidget::SignalRepresentTheCardInCentre, this, &The_Game::SlotShowTheCardInGameInspector);
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

    //ui->MainGamer->setMaximumWidth((koeff_GamerWidget_size_Width+MainGamerWidgetWidthExpansion)*windowWidth);

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
    logger.Algorithm() << "Monsters parsing complete!";

    theAmplifiersParser("Tables/cards_doors_amplifiers.csv");
    logger.Algorithm() << "Amplifiers parsing complete!";

    theCursesParser("Tables/cards_doors_curses.csv");
    logger.Algorithm() << "Curses parsing complete!";

    theProfessionsParser("Tables/cards_doors_professions.csv");
    logger.Algorithm() << "Professions parsing complete!";

    theRacesParser("Tables/cards_doors_races.csv");
    logger.Algorithm() << "Races parsing complete!";

    theSpecialMechanicsParser("Tables/cards_doors_specialmechanics.csv");
    logger.Algorithm() << "Special mechanics parsing complete!";

    theArmorsParser("Tables/cards_treasures_armor.csv");
    logger.Algorithm() << "Armor parsing complete!";

    theArmorAmplifiersParser("Tables/cards_treasures_armorAmplifiers.csv");
    logger.Algorithm() << "ArmorAmplifiers parsing complete!";

    theBattleAmplifiersParser("Tables/cards_treasures_battleAmplifiers.csv");
    logger.Algorithm() << "BattleAmplifiers parsing complete!";

    theLevelUpParser("Tables/cards_treasures_levelUp.csv");
    logger.Algorithm() << "LevelUps parsing complete!";

    theSpecialMechanicTreasureParser("Tables/cards_treasures_specialMechanics.csv");
    logger.Algorithm() << "SpecialMechanicsTreasures parsing complete!";

    theThingsAmplifiersParser("Tables/cards_treasures_thingsAmplifiers.csv");
    logger.Algorithm() << "ThingsAmplifiers parsing complete!";

    theWeaponParser("Tables/cards_treasures_Weapon.csv");
    logger.Algorithm() << "Weapons parsing complete!";

#else
    theMonstersParser(":/Tables/cards_doors_monsters.csv");
    logger.Algorithm() << "Monsters parsing complete!";

    theAmplifiersParser(":/Tables/cards_doors_amplifiers.csv");
    logger.Algorithm() << "Amplifiers parsing complete!";

    theCursesParser(":/Tables/cards_doors_curses.csv");
    logger.Algorithm() << "Curses parsing complete!";

    theProfessionsParser(":/Tables/cards_doors_professions.csv");
    logger.Algorithm() << "Professions parsing complete!";

    theRacesParser(":/Tables/cards_doors_races.csv");
    logger.Algorithm() << "Races parsing complete!";

    theSpecialMechanicsParser(":/Tables/cards_doors_specialmechanics.csv");
    logger.Algorithm() << "Special mechanics parsing complete!";

    theArmorsParser(":/Tables/cards_treasures_armor.csv");
    logger.Algorithm() << "Armor parsing complete!";

    theArmorAmplifiersParser(":/Tables/cards_treasures_armorAmplifiers.csv");
    logger.Algorithm() << "ArmorAmplifiers parsing complete!";

    theBattleAmplifiersParser(":/Tables/cards_treasures_battleAmplifiers.csv");
    logger.Algorithm() << "BattleAmplifiers parsing complete!";

    theLevelUpParser(":/Tables/cards_treasures_levelUp.csv");
    logger.Algorithm() << "LevelUps parsing complete!";

    theSpecialMechanicTreasureParser(":/Tables/cards_treasures_specialMechanics.csv");
    logger.Algorithm() << "SpecialMechanicsTreasures parsing complete!";

    theThingsAmplifiersParser(":/Tables/cards_treasures_thingsAmplifiers.csv");
    logger.Algorithm() << "ThingsAmplifiers parsing complete!";

    theWeaponParser(":/Tables/cards_treasures_Weapon.csv");
    logger.Algorithm() << "Weapons parsing complete!";
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
    //pass the answer form The_Game card check back to the Hand of THE MAIN GAMER ONLY!!!
    //It has now (26.12.2018) no effect on Opponents
    //Since there will be a very special function when another player
    //Can choose cards from the other's player hands.
    connect(this, &The_Game::SignalCardIsRejectedToBePlayed, ui->MainGamer, &GamerWidget::SlotCardIsRejectedToBePlayed);

    QObject::connect(this, &The_Game::SignalChartMessageReceived, ui->wdgt_Chart, &MunchkinDialog::SlotShowMessage);
    QObject::connect(ui->wdgt_Chart, &MunchkinDialog::SignalSendMessage, this, &The_Game::SlotProcessChartMessageSending);
    QObject::connect(ui->GameField, &battleField::SignalStartUpAnimationCompleted, this, &The_Game::SlotInitialAnimationCompleted);

    connect(ui->MainGamer, &GamerWidget::SignalTradeButtonWasPressed, this, &The_Game::SlotShowTradeMenu);

    connect(this, &The_Game::SignalShowTradeButton, ui->MainGamer, &GamerWidget::SlotShowTradeButton);
    connect(this, &The_Game::SignalHideTradeButton, ui->MainGamer, &GamerWidget::SlotHideTradeButton);

//    connect(this, &The_Game::SignalPassTheCardToTheFoldStack,
//            ui->CardStacksWidget, &CardStacks::SlotPassTheCardToFoldStack);

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
    for (uint32_t var = 0; var < _cardsAreReadyToBeSoldHolder.size(); ++var)
    {
        if (_cardsAreReadyToBeSoldHolder[var] == card)
        {
            _cardsAreReadyToBeSoldHolder.erase(_cardsAreReadyToBeSoldHolder.begin() + static_cast<int32_t>(var));
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

void The_Game::RemoveCardEffect(GamerWidget *wt, SimpleCard card)
{
    //Только для отладки
    const GameCardBasis* realCard = GetRealCard(card);
    switch (realCard->GetCardType())
    {
        case CardType::TreasureArmor:
        {
            gameCardTreasureArmor armor(static_cast<const gameCardTreasureArmor*>(realCard));
            ApplyNewArmor(wt, armor, CardApplyMode::Remove);
        }
        break;
        case CardType::TreasureWeapon:
        {
            gameCardTreasureWeapon weapon(static_cast<const gameCardTreasureWeapon*>(realCard));
            //EXPECTED_ERROR
            //Очевидно, что потребуется АККУРАТНО вызывать этот удалитель
            //во время принудительного СБРОСА (аннигиляции или "Потеряй большую шмотку" и им подобных)
            //карты SiegeEngine Во время боя, если она была АКТИВНА!
            //Впрочем, удалитель ффекта будет вызван ТОЛЬКО если карта БЫЛА активна.
            //А значит УДАЛЯТЬ эффект даже для ОСАДКИ при вызове Функции-Применителя
            //ТРЕБУЕТСЯ ВСЕГДА!

            ApplyNewWeapon(wt, weapon, CardApplyMode::Remove);
        }
        break;

        default:
            logger.Essential() << "Type: " << realCard->GetCardType()
                    << "Is not supported yet by CardsInGame RemoveProcess!";
        break;
    }
}

void The_Game::RemoveCardsFromCardsInGame(GamerWidget *wt, std::vector<SimpleCard> cards)
{   
    //перед тем, как карта будет удалена из вектора-хранилища, проверить, имела ли она эффект.
    //Если да, восстановить её тип и для него вызвать "удалитель" (применитель с соответствующим флагом)
    //Чтобы не писать в каждом месте огромный свич, можно передать массив указателей на однотипные
    //функции void func();
    //пусть это будет мап, которому ключём служит тип карты
    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        if (wt->GetPointerToPlayer()->CardIsActive(cards[var]))
        {
            logger.Algorithm() << "Card Is Active! Effect SHOULD BE REMOVED!";
            RemoveCardEffect(wt, cards[var]);
        }
        else
            qDebug() << "Card Is not Active. It has had no effect.";
    }
    wt->RemoveCardsFromCardsInGame(cards);
    wt->GetPointerToPlayer()->RemoveGivenCardsFromCardsInGame(cards);
}

void The_Game::SlotShowTradeMenu()
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    //emit SignalHideTradeButton();
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
    _mainPlayer->SetBattlePower(_mainPlayer->GetBattlePower()
                                + static_cast<int32_t>(GetLevelPurchased(totalMoneySpent)));

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
    CardsFromHandAndInGame separatedCards = CardsSeparator(ui->MainGamer, cards);

    std::vector<PositionedCard> posCardsOnHands = GetPositionedCardsFromHand(ui->MainGamer, separatedCards.cardsOnHands);
    std::vector<PositionedCard> posCardsInGame = GetPositionedCardsFromCardsInGame(ui->MainGamer, separatedCards.cardsInGame);

    qDebug() << "NAY-002: posCardsOnHands size " << posCardsOnHands.size();
    qDebug() << "NAY-002: posCardsInGame size " << posCardsInGame.size();

    //Убрать проданные карты с руки и/или из игры. (Карты хранятся во временном векторе posCards)
    //Была либо фаза торговли, либо фаза "ход другого игрока"
    SaveGamePhase();
    SetGamePhase(GamePhase::CardAnimation);

    emit SignalHideTradeButton();

    //Проданные карты с руки
    for (uint32_t var = 0; var < posCardsOnHands.size(); ++var)
    {
        RemoveCardFromCardsAreAbleToBeSold(posCardsOnHands[var].GetCard());
        RemoveTheCardFromHand(ui->MainGamer, posCardsOnHands[var].GetCard());
    }
    _mainPlayer->RemoveGivenCardsFromHand(PositionedCard::RevertToSimpleCardsVector(posCardsOnHands));

    //Проданные карты из Игры
    for (uint32_t var = 0; var < posCardsInGame.size(); ++var)
    {
        RemoveCardFromCardsAreAbleToBeSold(posCardsInGame[var].GetCard());
    }
    RemoveCardsFromCardsInGame(ui->MainGamer, PositionedCard::RevertToSimpleCardsVector(posCardsInGame));

    std::vector<std::pair<PositionedCard, bool> > allCardsToBeDisplayed;
    for (uint32_t var = 0; var < posCardsInGame.size(); ++var)
    {
        allCardsToBeDisplayed.push_back(std::make_pair(posCardsInGame[var], false));
    }
    for (uint32_t var = 0; var < posCardsOnHands.size(); ++var)
    {
        allCardsToBeDisplayed.push_back(std::make_pair(posCardsOnHands[var], true));
    }

    //start animation here
    if (!allCardsToBeDisplayed.empty())
        Animation_StartPassSoldCardsFromHandOrInGameToTreasureFold_Phase1(ui->MainGamer, allCardsToBeDisplayed);
}

std::vector<PositionedCard> The_Game::GetPositionedCardsFromHand(GamerWidget* wt, const std::vector<SimpleCard> &cards)
{
    return wt->GetPositionedCardsFromCardsOnHand(cards);
}

PositionedCard The_Game::GetPositionedCardFromHand(GamerWidget *wt, SimpleCard card)
{
    return wt->GetPositionedCardFromCardsOnHand(card);
}

std::vector<PositionedCard> The_Game::GetPositionedCardsFromCardsInGame(GamerWidget *wt, const std::vector<SimpleCard> &cards)
{
    return  wt->GetPositionedCardsFromCardsInGame(cards);
}

CardsFromHandAndInGame The_Game::CardsSeparator(GamerWidget *wt, const std::vector<SimpleCard> &cards)
{
    Player* playerPtr = wt->GetPointerToPlayer();
    std::vector<SimpleCard> cardsInGame;
    std::vector<SimpleCard> cardsOnHands;

    for (uint32_t var = 0; var < cards.size(); ++var)
    {
        if (playerPtr->CheckCardIsFromCardsInGame(cards[var]))
            cardsInGame.push_back(cards[var]);
        if (playerPtr->CheckCardIsFromCardsOnHand(cards[var]))
            cardsOnHands.push_back(cards[var]);
    }
    cardsInGame.shrink_to_fit();

    return CardsFromHandAndInGame(cardsOnHands, cardsInGame);
}

void The_Game::MoveCardFromCardInHandToCardInGame(Player *player, CardInGame card)
{
    player->RemoveCardFromHands(card.second);
    player->AddCardToCardsInGame(card);
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
    logger.Algorithm() <<"NAY-002: Entering AbleToSell Checker";

    //Fisrt of all, clear the vector!
    ClearCardsAreReadyToBeSoldHolder();

    if (_globalGamePhase == GlobalGamePhase::OtherPlayerMove)
        return false;

    if (!_gameSettings.GetHardCodedSettingsAllowedToSellAtLevelNine()
            && (player->GetPlayerLevel() == 9))
        return false;

    std::vector<SimpleCard> sumChecker;
    std::vector<SimpleCard> cardsOnHands = player->GetCardsOnHands();
    std::vector<SimpleCard> cardsInGame = player->GetCardsInGame();

    //logger.Debug() <<"NAY-002: AbleToSell Checker cardsOnHands: size: " << player->GetCardsOnHands().size();

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
    logger.Debug() << "NAY-002: Total Price of all the cards the player has: " << totalSumOfAllTheCards;

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
        return static_cast<uint32_t>((*_weaponsIterator).second.GetPrice());

    qDebug() << "NAY-002: Error During CheckCardPrice(). Card Not Found!!!";
    return 0;
}

uint32_t The_Game::GetLevelPurchased(uint32_t totalMoneySpent)
{
    return totalMoneySpent / 1000;
}

void The_Game::RealGameStart()
{
    logger.Essential() << "NAY-002 : RealGameStart()!";

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
    currentPlayer->SetBattlePower(currentPlayer->GetBattlePower() + data.levelDelta);

    currentWidget->SlotChangeTheGamerLevel(data.levelDelta);
    currentWidget->SlotChangeTheGamerBattlePower(data.levelDelta);

    //1.1. Для этого сначала получить их позиции
    CardsFromHandAndInGame separatedCards = CardsSeparator(currentWidget, data.soldCards);

    std::vector<PositionedCard> posCardsOnHands = GetPositionedCardsFromHand(currentWidget, separatedCards.cardsOnHands);
    std::vector<PositionedCard> posCardsInGame = GetPositionedCardsFromCardsInGame(currentWidget, separatedCards.cardsInGame);

    qDebug() << "NAY-002: posCardsOnHands size " << posCardsOnHands.size();
    qDebug() << "NAY-002: posCardsInGame size " << posCardsInGame.size();


    //Убрать проданные карты с руки и/или из игры. (Карты хранятся во временном векторе posCards)
    //Была либо фаза торговли, либо фаза "ход другого игрока"
    SaveGamePhase();
    SetGamePhase(GamePhase::CardAnimation);

    emit SignalHideTradeButton();

    //Проданные карты с руки
    for (uint32_t var = 0; var < posCardsOnHands.size(); ++var)
    {
        RemoveCardFromCardsAreAbleToBeSold(posCardsOnHands[var].GetCard());
        RemoveTheCardFromHand(currentWidget, posCardsOnHands[var].GetCard());
    }
    currentPlayer->RemoveGivenCardsFromHand(PositionedCard::RevertToSimpleCardsVector(posCardsOnHands));

    //Проданные карты из Игры
    for (uint32_t var = 0; var < posCardsInGame.size(); ++var)
    {
        RemoveCardFromCardsAreAbleToBeSold(posCardsInGame[var].GetCard());
    }
    RemoveCardsFromCardsInGame(currentWidget, PositionedCard::RevertToSimpleCardsVector(posCardsInGame));

    std::vector<std::pair<PositionedCard, bool> > allCardsToBeDisplayed;
    for (uint32_t var = 0; var < posCardsInGame.size(); ++var)
    {
        allCardsToBeDisplayed.push_back(std::make_pair(posCardsInGame[var], false));
    }
    for (uint32_t var = 0; var < posCardsOnHands.size(); ++var)
    {
        allCardsToBeDisplayed.push_back(std::make_pair(posCardsOnHands[var], true));
    }
     //= posCardsInGame + posCardsOnHands
    //start animation here
    if (!allCardsToBeDisplayed.empty())
        Animation_StartPassSoldCardsFromHandOrInGameToTreasureFold_Phase1(currentWidget, allCardsToBeDisplayed);

}

void The_Game::SlotProcessOpponentHasImplementedCard(TheGameMainGamerHasImplementedCard data)
{
    qDebug() << "NAY-002: void The_Game::SlotProcessOpponentHasImplementedCard(TheGameMainGamerHasImplementedCard data)";
    qDebug() << "Process implementation of the card by another player";

    qDebug() << "NAY-002: gamerID: " << data.gamerID;
    qDebug() << "NAY-002: roomID: " << data.roomID;
    qDebug() << "NAY-002: CardImplementationDirection: " << data.direction;
    qDebug() << "NAY-002: SimpleCard: " << data.playedCard;
    qDebug() << "NAY-002: battleStarts: " << data.battleStarts;

    //1) Найти виджет, относительно которого будет применяться карта.
    //2) И Игрока, относительно которого надо удлаять карты
    GamerWidget* currentWidget = _GamerWidgetsWithIDs[data.gamerID];
    Player* currentPlayer = currentWidget->GetPointerToPlayer();

    //Фаза установится по прохождении анимации
//    SaveGamePhase();
//    SetGamePhase(GamePhase::CardProcessing);

    //Надо ли выключать окно торговли?
    //    emit SignalHideTradeButton();

    //2) Найти позицию карты
    PositionedCard cardToBePlayed;
    switch (data.direction)
    {
    case CardImplementationDirection::HandToCardsInGame:
    {
        cardToBePlayed = GetPositionedCardFromHand(currentWidget, data.playedCard);
    }
        break;
    default:
    {
        qDebug() << "NAY-002: SlotProcessOpponentHasImplementedCard() ERROR: This direction is not supported yet! Direction: " << data.direction;
        return;
    }
        break;
    }

    //Удалить с руки или из других мест, откуда она была применена
    //Удалены они будут в применителе, после того, как будут добавлены "в игру"
    switch (data.direction)
    {
        case CardImplementationDirection::HandToCardsInGame:
        {
            //Удалить эту карту с руки у игрока
            //RemoveTheCardFromHand(currentWidget, data.playedCard);
            //Это действие выполнит "применитель"
            //currentPlayer->RemoveGivenCardFromHand(data.playedCard);
        }
        break;
        default:
        {
            qDebug() << "NAY-002: SlotProcessOpponentHasImplementedCard() ERROR: This direction is not supported yet! Direction: " << data.direction;
            return;
        }
    }

    //3) Удалить карту с руки (из того места, где она должна быть удалена)
    //Убрать проданные карты с руки и/или из игры. (Карты хранятся во временном векторе posCards)
    //Была либо фаза торговли, либо фаза "ход другого игрока"

    //Применить карту.
    //Лишние сигналы не должны сработать
    MainCardImplementer(currentWidget, cardToBePlayed, data.direction, CardCheckerPolicy::ImplementByServerCommand);

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
        logger.Debug() << "NAY-001: The player is able to sell!";
}

void The_Game::InitializeOpponentMove(const QString &opponentsName)
{
    SetGlobalGamePhase(GlobalGamePhase::OtherPlayerMove);
    SetCurrentGamePhase(GamePhase::OtherPlayerMove);

    logger.Algorithm() << "NAY-002: Other PlayerMove!";
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
   logger.Algorithm() << "NAY-002: MoveTimer timeout!";
}

void The_Game::SlotPhaseTimerHandler()
{
    logger.Algorithm() << "NAY-002:: PhaseTimer timeout!";
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

QDebug operator<<(QDebug debug, const GamePhase &dt)
{
    switch (dt)
    {
    case GamePhase::AfterBattleLoose:
        debug << "AfterBattleLoose";
        break;
    case GamePhase::AfterBattleWin:
        debug << "AfterBattleWin";
        break;
    case GamePhase::AfterOpenDoorNoMonster:
        debug << "AfterOpenDoorNoMonster";
        break;
    case GamePhase::Battle:
        debug << "Battle";
        break;
    case GamePhase::CardAnimation:
        debug << "CardProcessing";
        break;
    case GamePhase::Diplomacy:
        debug << "Diplomacy";
        break;
    case GamePhase::GameInitialization:
        debug << "GameInitialization";
        break;
    case GamePhase::HandAlignment:
        debug << "HandAlignment";
        break;
    case GamePhase::OtherPlayerMove:
        debug << "OtherPlayerMove";
        break;
    case GamePhase::StartOfTheMove:
        debug << "StartOfTheMove";
        break;
    case GamePhase::Theft:
        debug << "Theft";
        break;
    case GamePhase::WaitingForAnOpponentToMove:
        debug << "WaitingForAnOpponentToMove";
        break;
    }
    return debug;
}

QDebug operator<<(QDebug debug, const GlobalGamePhase &dt)
{
    switch (dt)
    {
    case GlobalGamePhase::OwnMove:
        debug << "OwnMove";
        break;
    case GlobalGamePhase::OtherPlayerMove:
        debug << "OtherPlayerMove";
        break;
    }

    return debug;
}
