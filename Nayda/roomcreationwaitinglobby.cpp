#include "roomcreationwaitinglobby.h"
#include "ui_roomcreationwaitinglobby.h"

RoomCreationWaitingLobby::RoomCreationWaitingLobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomCreationWaitingLobby)
{
    ui->setupUi(this);
}

RoomCreationWaitingLobby::~RoomCreationWaitingLobby()
{
    delete ui;
}
