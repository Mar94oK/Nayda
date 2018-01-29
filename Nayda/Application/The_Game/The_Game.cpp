#include "Application/The_Game/The_Game.h"
#include "ui_The_Game.h"
#include <ctime>
#include <QTime>
#include "popupcard.h"

The_Game::The_Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::The_Game)
{
    ui->setupUi(this);


    //Algorithm:
    //1. Receive the size of the screen;
    //2. Define sizes of an objects;
    //3. Receive information about number of players from Before_the_Game
    //                            and another game concepts;


    //setup size before rescaling.
    //resize will be allowed only for PC version and only for some preset definition

#ifdef PC_VERSION
    //some code

    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Heigh = HW_Screen_Size.height();

#ifdef DEBUG_MESSAGES
    qDebug() << "Available dimensions. Screen w = " << HW_Screen_Size_Width << " Screen h = " << HW_Screen_Size_Heigh;
#endif


#endif

#ifdef MOBILE_VERSION
    //some code
#endif



    //Settings-up the Randomization. Disable in the DEBUG
    // Create seed for the random
    // That is needed only once on application startup
    //QTime time = QTime::currentTime();
    //qsrand((uint)time.msec());




    //Setting-up button's connections.

    //QObject::connect( ui->btnHide, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(ui->btn_switch_back, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(this, SIGNAL(dbg_to_be_shown(bool)), this, SLOT(showFullScreen()));//SLOT(showFullScreen())) SLOT(show();
    QObject::connect(ui->btn_switch_back, SIGNAL(clicked(bool)), this, SLOT(dbg_return_to_the_main_window()));


    //Setting the in-Game connections with other Widgets

    connect(ui->MainGamer, &GamerWidget::_representTheCardInCentre, this, &The_Game::showTheCardInCentre);
    connect(ui->MainGamer, &GamerWidget::_hideTheCardInCentre, this, &The_Game::hideTheCardInCentre);

//    connect(ui->MainGamer, &GamerWidget::_representTheCardNearItsPosition, this, &The_Game::showTheCardNearItsPosition);
//    connect(ui->MainGamer, &GamerWidget::_hideTheCardNearItsPosition, this, &The_Game::hideTheCardInCentre);



    //setting-up main Game Ico

    //all of such kind is equal;
    //1. create pixmap;
    //2. rescale pixmap
    //3. create palette
    //4. set brush of palette as previously created pixmap
    //5. set everything for button: fillbackground; palette; flat; fixed size;
    //6. move to the expected position and leave it there
    //7. define whether it could be movable???

    //Setting up coefficients
    const float koeff_GameField_size = 0.5f;

    const float koeff_GamerWidget_size_Height = (1 - koeff_GameField_size)/2;
    const float koeff_GamerWidget_size_Width = koeff_GameField_size/3;

    const float koeff_GameTimers_size_Height = koeff_GamerWidget_size_Height; // should be the same
    const float koeff_GameTimers_size_Width = koeff_GameField_size/3;
    const float koeff_GameInfoBox_size_Height = 0.66f; //why it is impossible 2/3???
    const float koeff_GameInfoBox_size_Width = (1 - koeff_GameField_size) / 2;


    //setting up the GUI staff
    //Defining its coefficients with respect to the total size of availible field;




    //ui->GameField->setMinimumWidth(koeff_GameField_size*HW_Screen_Size_Width);
    //ui->GameField->setMinimumHeight(koeff_GameField_size*HW_Screen_Size_Heigh);




    ui->MainGamer->setMinimumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
    ui->MainGamer->setMaximumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
    //with respect to the MainGamer, the height size won't be larger then allowed,
    //but may take all the availible space if the width is concerned; Why not?
    //ui->MainGamer->setMinimumWidth(koeff_GamerWidget_size_Width*HW_Screen_Size_Width);
    ui->MainGamer->setMaximumWidth((koeff_GamerWidget_size_Width+MainGamerWidgetWidthExpansion)*HW_Screen_Size_Width);




    ui->TimersWidget->setMinimumHeight(koeff_GameTimers_size_Height*HW_Screen_Size_Heigh);
    ui->TimersWidget->setMaximumHeight(koeff_GameTimers_size_Height*HW_Screen_Size_Heigh);

    ui->TimersWidget->setMinimumWidth(koeff_GameTimers_size_Width*HW_Screen_Size_Width);
    ui->TimersWidget->setMaximumWidth(koeff_GameTimers_size_Width*HW_Screen_Size_Width);

    ui->GameInfoBox->setMinimumHeight(koeff_GameInfoBox_size_Height*HW_Screen_Size_Heigh);
    ui->GameInfoBox->setMaximumHeight(koeff_GameInfoBox_size_Height*HW_Screen_Size_Heigh);

    ui->GameInfoBox->setMinimumWidth(koeff_GameInfoBox_size_Width*HW_Screen_Size_Width);
    ui->GameInfoBox->setMaximumWidth(koeff_GameInfoBox_size_Width*HW_Screen_Size_Width);


#ifdef DEBUG_MESSAGES
    qDebug() << "GameInfoBox. setMinimumHeight = setMaximumHeight " << koeff_GameInfoBox_size_Height*HW_Screen_Size_Heigh << endl
             <<" GameInfoBox.setMinimumWidth = " << koeff_GameInfoBox_size_Width*HW_Screen_Size_Width;
#endif


    ui->btn_switch_back->setMinimumWidth(koeff_GameInfoBox_size_Width*HW_Screen_Size_Width);
    ui->btn_switch_back->setMaximumWidth(koeff_GameInfoBox_size_Width*HW_Screen_Size_Width);


    //receiving number of players;

#ifdef DEBUG_NO_SERVER
    //do not receive actual parameters from Before_the_Game, but start immidiately

    this->m_number_of_players = 6; //default maximum (extended - special code entered by user will be needed)
    this->m_time_for_move = 30; //seconds
    this->m_time_to_think = 15; //seconds

#endif




    //setting MainGamer
    ui->MainGamer->setIs_MainPlayer(true);

    //hide Secondary Hand Widget;
    ui->MainGamer->_hideHandSecondaryPlayerWidget();


    //creating opponents
    //remember, opponents less by 1 than total amount of players

    //opponets

    _players_opponents.push_back(_opponent0);
    _players_opponents.push_back(_opponent1);
    _players_opponents.push_back(_opponent2);
    _players_opponents.push_back(_opponent3);
    _players_opponents.push_back(_opponent4);


    //widgets for them
    for (unsigned int j = 0; j < m_number_of_players - 1; j++) {
        _widgets4Opponents.push_back(new GamerWidget);
        _widgets4Opponents.back()->redraw_as_a_secondary_player();
        _widgets4Opponents.back()->setIs_MainPlayer(false);

    }



    //first two of them to the top layout
    //fixed numbers, they are allways there
    ui->top_opponents_layout->addWidget(_widgets4Opponents[0]);
    ui->top_opponents_layout->addWidget(_widgets4Opponents[1]);



    //this->opponent[0]->


    //if there is(are) some other players, add them to the right_side layout
    if (m_number_of_players - 3 > 0) {
        for (unsigned int i = 0; i < m_number_of_players - 3; i++) {
            ui->right_side_opponents_layout->addWidget(_widgets4Opponents[2+i]);
        }
    }



    //resizing 'em all
    for (unsigned int j = 0; j < m_number_of_players - 1; j++) {

        _widgets4Opponents[j]->setMinimumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
        _widgets4Opponents[j]->setMaximumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
        _widgets4Opponents[j]->setMaximumWidth((koeff_GamerWidget_size_Width+SecondaryGamerWidgetWidthExpansion)*HW_Screen_Size_Width);

    }

    qDebug() << "Maximum Height of the Gamer_Widget: " << koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh;
    qDebug() << "Maximum Width of the Gamer_Widget: " << koeff_GamerWidget_size_Width*HW_Screen_Size_Width;


#ifdef DEBUG_NO_SERVER

    for (unsigned int var = 0; var < _widgets4Opponents.size(); ++var) {
        connect(_widgets4Opponents[var], &GamerWidget::_representTheCardInCentre, this, &The_Game::showTheCardInCentre);
        connect(_widgets4Opponents[var], &GamerWidget::_hideTheCardInCentre, this, &The_Game::hideTheCardInCentre);
    }


//    for (unsigned int var = 0; var < _widgets4Opponents.size(); ++var) {
//        connect(_widgets4Opponents[var], &GamerWidget::_representTheCardNearItsPosition, this, &The_Game::showTheCardNearItsPosition);
//        connect(_widgets4Opponents[var], &GamerWidget::_hideTheCardNearItsPosition, this, &The_Game::hideTheCardNearItsPosition);
//    }

#endif


    //Game_Card kamikazeKobolds(1,"Pictures/No_Class_dbg.png","Kamikaze Kobolds",cardAddon::ClirickalMistakes);
    //_basisStock.insert({1, kamikazeKobolds});


    //gameCardDoorMonster monster;
    //_monstersDeck.insert({1, monster});

    //filling up the monsters' stock!

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


    //first pass there the Cards (after receiving them from server);
    passDecksToBattleField();
    passDecksToPlayerWidgets();


    formingInitialDecks();
    givingCardsToPlayers();
    showInitialCardsOnHands();


    //disbale CardRepresenter
    //_debugShowAllTheCards();


    //create popUpCard Widget

    _popUpCardWidget = new PopUpCard();


     //create CardPointerWidget

    _cardPointer = new TriangleCardPointer();

    //pass the cards to PopUp Widget
    passDecksToPopUpCardWidget();


    //pass the Cards to CardsStacks Widget
    passDecksToCardsStacksWidget();


    QPixmap pxmpBattleField("Pictures/JorneyCover.png");
    QPalette plte_battleField;
    qDebug () << "Size: " << size();
    plte_battleField.setBrush(QPalette::Background, QBrush(pxmpBattleField.scaled(HW_Screen_Size.width(),HW_Screen_Size.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    setPalette(plte_battleField);
    setAutoFillBackground(true);


#ifdef DEBUG_NO_DIALOG

    //hide the Dialog
    ui->GameInfoBox->hide();

#endif

#ifdef DEBUG_NO_RETURN_TO_MENU

    ui->btn_switch_back->hide();

#endif



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
    theMonster.setPictureAddress(lst.first());
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

gameCardDoorAmplifier The_Game::amplifierStringParser(const QString &amplifier_string)
{
    gameCardDoorAmplifier theAmplifier;
    QStringList lst = amplifier_string.split(";");
    theAmplifier.setCardID((lst.first()).toInt());
    lst.removeFirst();
    theAmplifier.setPictureAddress(lst.first());
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
    theCurse.setPictureAddress(lst.first());
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
    theProfession.setPictureAddress(lst.first());
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
    theSpecialMechanic.setPictureAddress(lst.first());
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

    theArmor.setPictureAddress(lst.first());
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

    theArmorAmplifier.setPictureAddress(lst.first());
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

    theBattleAmplifier.setPictureAddress(lst.first());
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

    theLevelUp.setPictureAddress(lst.first());
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

    theSpecialMechanic.setPictureAddress(lst.first());
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

    theThingAmplifier.setPictureAddress(lst.first());
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

    theWeapon.setPictureAddress(lst.first());
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

void The_Game::passDecksToBattleField()
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


    for (unsigned int var = 0; var < _widgets4Opponents.size(); ++var) {


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

void The_Game::passDecksToPopUpCardWidget()
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

void The_Game::passDecksToCardsStacksWidget()
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

void The_Game::givingCardsToPlayers()
{
#ifdef DEBUG_NO_SERVER

    //define, how many players are presented;
    //this value is received once from server side and can't be changed during the game if only the player is leaving the game;
    unsigned int totalPlayers = m_number_of_players; //6 as default
    unsigned int cardsToGive = 4;

    //then it is necessary to give m_number_of_players*4 cards from doors stack, and
    //the same quantity from the Treasures stack.

    //start with the main player... (giving cards from the top)

    unsigned int initialSizeDoors = _doorsDeck.size();
    unsigned int initialSizeTreasures = _treasuresDeck.size();

    for (unsigned int var = 0; var < cardsToGive; ++var) {

        _main_player.addCardToHands(_doorsDeck.front());
        _doorsDeck.erase(_doorsDeck.begin());
    }

    //giving cards to the other players...

    for (unsigned int var = 0; var < m_number_of_players-1; ++var) {

        for (unsigned int j = 0; j < cardsToGive; ++j ) {

            _players_opponents[var].addCardToHands(_doorsDeck.front());
            _doorsDeck.erase(_doorsDeck.begin());

        }
    }

    ui->CardStacksWidget->updateDoorsLeft(initialSizeDoors - cardsToGive*m_number_of_players);
    qDebug() << "Doors are given to the players!";

    //treasures..

    for (unsigned int var = 0; var < cardsToGive; ++var) {

        _main_player.addCardToHands(_treasuresDeck.front());
        _treasuresDeck.erase(_treasuresDeck.begin());
    }

    //giving cards to the other players...


    for (unsigned int var = 0; var < m_number_of_players-1; ++var) {

        for (unsigned int j = 0; j < cardsToGive; ++j ) {

            _players_opponents[var].addCardToHands(_treasuresDeck.front());
            _treasuresDeck.erase(_treasuresDeck.begin());

        }
    }
    qDebug() << "Treasures are given to the players!";

    ui->CardStacksWidget->updateTreasuresLeft(initialSizeTreasures - cardsToGive*m_number_of_players);




    //



#endif



}

void The_Game::showInitialCardsOnHands()
{
    for (unsigned int var = 0; var < _main_player.cardsOnHandsVector()->size(); ++var) {

        ui->MainGamer->addTheCardToHandsWidget(*((_main_player.cardsOnHandsVector())->begin() + static_cast<int>(var)));

    }

    for (unsigned int var = 0; var < _players_opponents.size(); ++var) {

        unsigned int totalCardsToShow = (_players_opponents[var].cardsOnHandsVector())->size();
        for (unsigned int j = 0; j < totalCardsToShow; ++j) {

            _widgets4Opponents[var]->addTheCardToHandsWidget(*((_players_opponents[var].cardsOnHandsVector())->begin() + static_cast<int>(j)));
        }

    }

}



//this function might only be cold after the cards stacks are initialized.
//If this rule is note completed, the sizes will be empty!
void The_Game::formingInitialDecks()
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


void The_Game::dbg_was_pushed_to_game_mode()
{
    emit dbg_to_be_shown(true);
}

void The_Game::dbg_return_to_the_main_window()
{
    emit dbg_return_to_before_the_game(true);
}

void The_Game::showTheCardInCentre(PositionedCard card)
{
    //pass the card to PopUpWidget
    _popUpCardWidget->setUpPointsForPoly(card.positionTopLeft, card.positionBottomRight);
    _popUpCardWidget->setUpPopUpCard(card.card);
    _popUpCardWidget->show(card.positionTopLeft, card.positionBottomRight);

    _cardPointer->setUpTriangleCardPointer(card.positionTopLeft, card.positionBottomRight);
    _cardPointer->show(card.positionTopLeft, card.positionBottomRight);

}

//void The_Game::showTheCardNearItsPosition(PositionedCard card)
//{
//    _popUpCardWidget->setUpPopUpCard(card.card);
//    _popUpCardWidget->show(card.positionTopLeft, card.positionBottomRight);
//}

void The_Game::hideTheCardInCentre(bool)
{
    _popUpCardWidget->hideAnimation();
    _cardPointer->hideAnimation();
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

//void The_Game::hideTheCardNearItsPosition(bool)
//{
//    _popUpCardWidget->hideAnimation();
//}


