#include "roomcreationwaitinglobby.h"
#include "ui_roomcreationwaitinglobby.h"
#include "munchkinglobaldefines.h"
#include <QDesktopWidget>


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

void RoomCreationWaitingLobby::closeEvent(QCloseEvent *event)
{
    emit SignalUserIsClosingRoomCreationLobby();
}

void RoomCreationWaitingLobby::setUpUiGeometricRelations()
{
    QRect HwScreenSize = QApplication::desktop()->screenGeometry();
    int HwScreenSizeWidth = HwScreenSize.width();
    int HwScreenSizeHeight = HwScreenSize.height();

    setGeometry(0,0,
                static_cast<uint32_t> (HwScreenSizeWidth * GeometricLimitations::beforeTheGameWindowsSize),
                static_cast<uint32_t> (HwScreenSizeHeight * GeometricLimitations::beforeTheGameWindowsSize));

    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    QApplication::desktop()->availableGeometry()));
}

void RoomCreationWaitingLobby::applyNewSettings(GameSettings settings)
{
    _gameSettings.applyNewSettings(settings);
}

void RoomCreationWaitingLobby::setUpCreatorsName(const QString &name)
{
    ui->btn_Creator->setText(name);
}

void RoomCreationWaitingLobby::SetUpInitalState(GameSettings settings)
{
    _gameSettings.applyNewSettings(settings);
    setUpCreatorsName(settings.clientName());
    ui->wdgt_GameSettings->ApplyNewSettings(settings);
    ui->wdgt_GameSettings->setUpInitialState();
    //ui->wdgt_GameSettings
}
