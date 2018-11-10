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
