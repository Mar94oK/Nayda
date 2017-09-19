#include "Application/The_Game/The_Game.h"
#include "ui_The_Game.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QDebug>



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



    //Setting-up button's connections.

    //QObject::connect( ui->btnHide, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(ui->btn_switch_back, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(this, SIGNAL(dbg_to_be_shown(bool)), this, SLOT(showFullScreen()));//SLOT(showFullScreen())) SLOT(show();
    QObject::connect(ui->btn_switch_back, SIGNAL(clicked(bool)), this, SLOT(dbg_return_to_the_main_window()));


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




    ui->GameField->setMinimumWidth(koeff_GameField_size*HW_Screen_Size_Width);
    ui->GameField->setMinimumHeight(koeff_GameField_size*HW_Screen_Size_Heigh);

    ui->MainGamer->setMinimumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
    ui->MainGamer->setMaximumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
    //with respect to the MainGamer, the height size won't be larger then allowed,
    //but may take all the availible space if the width is concerned; Why not?
    //ui->MainGamer->setMinimumWidth(koeff_GamerWidget_size_Width*HW_Screen_Size_Width);
    ui->MainGamer->setMaximumWidth(koeff_GamerWidget_size_Width*HW_Screen_Size_Width);

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


    //creating opponents
    //remember, opponents less by 1 than total amount of players
    for (int j = 0; j < m_number_of_players - 1; j++) {
        this->opponent[j] = new GamerWidget;
        opponent[j]->redraw_as_a_secondary_player();
        opponent[j]->setIs_MainPlayer(false);

    }



    //first two of them to the top layout
    //fixed numbers, they are allways there
    ui->top_opponents_layout->addWidget(this->opponent[0]);
    ui->top_opponents_layout->addWidget(this->opponent[1]);



    //this->opponent[0]->


    //if there is(are) some other players, add them to the right_side layout
    if (m_number_of_players - 3 > 0) {
        for (int i = 0; i < m_number_of_players - 3; i++) {
            ui->right_side_opponents_layout->addWidget(this->opponent[2+i]);
        }
    }



    //resizing 'em all
    for (int j = 0; j < m_number_of_players - 1; j++) {

        this->opponent[j]->setMinimumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
        this->opponent[j]->setMaximumHeight(koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh);
        this->opponent[j]->setMaximumWidth(koeff_GamerWidget_size_Width*HW_Screen_Size_Width);

    }

    qDebug() << "Maximum Height of the Gamer_Widget: " << koeff_GamerWidget_size_Height*HW_Screen_Size_Heigh;
    qDebug() << "Maximum Width of the Gamer_Widget: " << koeff_GamerWidget_size_Width*HW_Screen_Size_Width;



    //Game_Card kamikazeKobolds(1,"Pictures/No_Class_dbg.png","Kamikaze Kobolds",cardAddon::ClirickalMistakes);
    //_basisStock.insert({1, kamikazeKobolds});


    //gameCardDoorMonster monster;
    //_monstersDeck.insert({1, monster});

    //filling up the monsters' stock!

    theMonstersParser("Tables/cards_doors_monsters.csv");
    qDebug() << "Monsters parsing complete!";

    theAmplifiersParser("Tables/cards_doors_amplifiers.csv");
    qDebug() << "Amplifiers parsing complete!";

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

    if (lst.first() == "noone") { lst.removeFirst(); }
        else {
        if (lst.first() == "Woman") theMonster.setSpecialMechanicAgainstWoman(true);
        if (lst.first() == "Cleric") theMonster.setSpecialMechanicAgainstCleric(true);
        if (lst.first() == "all") theMonster.setSpecialMechanicAgainstAll(true);
        if (lst.first() == "Thief") theMonster.setSpecialMechanicAginstThief(true);
        if (lst.first() == "Elf") theMonster.setSpecialMechanicAgainstElf(true);
        if (lst.first() == "Halfling") theMonster.setSpecialMechanicAgainstHalfling(true);
        if (lst.first() == "Wizard") theMonster.setSpecialMechanicAgainstWizard(true);

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
            qDebug() << lst.at(var);
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
    qDebug() << "Amplifiers parsing starts!" << endl;

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



void The_Game::theMonstersParser(const QString &filename)
{
    QFile file(filename);
    qDebug() << "Monsters parsing starts!" << endl;

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


