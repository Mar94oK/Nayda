#include "Application/Before_The_Game/Before_The_Game.h"
//#include "ui_main_application.h"
#include "ui_Before_The_Game.h"
#include <QDesktopWidget>




Before_The_Game::Before_The_Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Before_The_Game)
{
    ui->setupUi(this);


    //Here interconnections between Buttons and Hide/Show slots are situated;
    //Might be useful to move them later to the system_manager
    QObject::connect( ui->btnHide, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect (ui->btnHide, SIGNAL(clicked(bool)), this, SLOT(dbg_switch_to_game_mode_button_pressed()));
    QObject::connect(ui->Create_Lobby, SIGNAL(clicked(bool)),ui->Strt_New_Room, SLOT(show()));


    //QObject::connect(ui->Strt_New_Room, SIGNAL(), this, SLOT(dbg_start_the_game_with_default_settings()));

    connect(ui->Strt_New_Room, &start_new_room::dbg_btn_play_with_defaults_pressed,this, &Before_The_Game::dbg_start_the_game_with_default_settings);
    connect(ui->Strt_New_Room, &start_new_room::dbg_btn_play_with_defaults_pressed, this, &Before_The_Game::hide);


    //configure_with_default_settings;
    number_of_players = 3;
    time_for_move = 30;
    time_to_think = 30;


    //configure_initial_widgets
    //find the HW size of the window
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Heigh = HW_Screen_Size.height();

    //Setting up coefficients
    const float koeff_Create_Room_size = 0.7f;
    const float koeff_Dialog_size = 0.1f;




    #ifdef DEBUG_MESSAGES
    qDebug() << "Available dimensions. Screen w = " << HW_Screen_Size_Width << " Screen h = " << HW_Screen_Size_Heigh;
    #endif



    ui->About_Authors->setMaximumWidth(koeff_Dialog_size*HW_Screen_Size_Width);

    ui->Create_Lobby->setMaximumWidth(koeff_Dialog_size*HW_Screen_Size_Width);

    ui->Settings->setMaximumWidth(koeff_Dialog_size*HW_Screen_Size_Width);

    ui->Find_Lobby->setMaximumWidth(koeff_Dialog_size*HW_Screen_Size_Width);

    ui->btnHide->setMaximumWidth(koeff_Dialog_size*HW_Screen_Size_Width);






    ui->Strt_New_Room->setMinimumHeight(koeff_Create_Room_size*HW_Screen_Size_Heigh);
    ui->Strt_New_Room->setMinimumWidth(koeff_Create_Room_size*HW_Screen_Size_Width);
    ui->Strt_New_Room->setMaximumHeight(koeff_Create_Room_size*HW_Screen_Size_Heigh);
    ui->Strt_New_Room->setMaximumWidth(koeff_Create_Room_size*HW_Screen_Size_Width);


    ui->Strt_New_Room->hide();
    //ui->Strt_New_Room->show();

}






Before_The_Game::~Before_The_Game()
{
    delete ui;
}

void Before_The_Game::dbg_switch_to_game_mode_button_pressed()
{
    emit dbg_switch_to_game_mode(true);
    emit dbg_the_game_begins(true);
    emit update_game_options_card_stack_type(this->card_stack_mode);
    qDebug() << "Start with debug button. ONLY VIEW!!!!";
    //emit update_game
}

void Before_The_Game::dbg_start_the_game_with_default_settings()
{
    emit dbg_switch_to_game_mode(true);
    emit dbg_the_game_begins(true);
    emit update_game_options_card_stack_type(this->card_stack_mode);
    qDebug() << "Start with debug button. DEFAULT SETTING ARE PROVIDED!!!!";
}

