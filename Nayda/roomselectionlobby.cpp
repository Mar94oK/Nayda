#include "roomselectionlobby.h"
#include "ui_roomselectionlobby.h"

RoomSelectionLobby::RoomSelectionLobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomSelectionLobby)
{
    ui->setupUi(this);
}

RoomSelectionLobby::~RoomSelectionLobby()
{
    delete ui;
}
