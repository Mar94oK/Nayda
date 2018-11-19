#include "roomselectionlobby.h"
#include "ui_roomselectionlobby.h"
#include <QDebug>
#include <QStandardPaths>
#include <QPushButton>
#include <QPixmap>
#include <QBrush>

RoomSelectionLobby::RoomSelectionLobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomSelectionLobby)
{
    ui->setupUi(this);
    setUpUiPicturesAddresses();
    setBackgroudImage(_coverPictureAddress);
    SetUpConnections();
}

RoomSelectionLobby::~RoomSelectionLobby()
{
    delete ui;
}

void RoomSelectionLobby::setUpUiPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Pictures/roomSelectionLobby";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Nayda/Pictures/roomSelectionLobby";
#endif

    QString picturesLocationBasis = homeDirectory + uiPlayMenuFilesLocation + "/";

    _coverPictureAddress = picturesLocationBasis + "CastleForRoomsSelection.jpg";
}

void RoomSelectionLobby::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
{
    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());
    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*widthCoeff,
                                            geometry().width()*widthCoeff*heightWidthRelatio,
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    btn->setMinimumWidth(geometry().width()*widthCoeff);
    btn->setMinimumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}

void RoomSelectionLobby::setBackgroudImage(QString pictureAddress)
{
    QBrush br(Qt::TexturePattern);
    br.setTextureImage(QImage(pictureAddress));
    QPalette plt = palette();
    plt.setBrush(QPalette::Background, br);
    setPalette(plt);
}

void RoomSelectionLobby::SlotAddRoomToSelectableList(ServerRoomReadyToConnectData room)
{
    _selectableRooms.push_back(room);
    AddSelectableRoomToGUI(room);
}

void RoomSelectionLobby::SlotRemoveRoomFromSelectableList(ServerRoomReadyToConnectData room)
{
    if (FindRoomById(room.roomID) != nullptr)
    {
        ui->layoutRooms->removeWidget(FindRoomById(room.roomID));
        RemoveRoomById(room.roomID);
    }
}

void RoomSelectionLobby::SlotSendConnectToSelectedRoomRequest(uint32_t roomID)
{
    emit SignalSendConnectToSelectedRoomRequest(roomID);
}

void RoomSelectionLobby::SlotUpdateQuerySize(uint32_t querySize)
{
    ui->lbl_QueueOrder->setText(_querySizeBaseText + QString::number(querySize));
}

void RoomSelectionLobby::SlotUpdateQueryOrder(uint32_t queryOrder)
{
    ui->lbl_QueueOrder->setText(_queryOrderBaseText + QString::number(queryOrder));
}

void RoomSelectionLobby::AddSelectableRoomToGUI(ServerRoomReadyToConnectData data)
{
    QPushButton* btn = new QPushButton();
    ui->layoutRooms->addWidget(btn, FindPositionFornewButton().row,
                               FindPositionFornewButton().column);

    btn->setText("Комнта: " + data.roomName + "\n"
                 +"Количество игроков:  " + data.players + "\n"
                 +"Номер комнаты: " + QString::number(data.roomID) + "\n"
                 +"Максимальное число игроков: " + QString::number(data.maximumNumberOfPlayers));


    QObject::connect(btn, &QPushButton::clicked, [this, data] { SlotSendConnectToSelectedRoomRequest(data.roomID); });

    _selectableButtons.push_back(btn);
}

ButtonsPosition RoomSelectionLobby::FindPositionFornewButton()
{
    uint32_t currentRow = _selectableRooms.size() / 4; //full Rows
    uint32_t nextColumn = _selectableRooms.size() % 4;

    return ButtonsPosition(currentRow, nextColumn);

}

QPushButton *RoomSelectionLobby::FindRoomById(uint32_t id)
{
    for (uint32_t var = 0; var < _selectableRooms.size(); ++var)
    {
        if (_selectableRooms[var].roomID == id)
            return _selectableButtons[var];
    }
    qDebug() << "NAY-001 : Error while FindRoomById()! ";
    return nullptr;

}

bool RoomSelectionLobby::RemoveRoomById(uint32_t id)
{
    for (uint32_t var = 0; var < _selectableRooms.size(); ++var)
    {
        if (_selectableRooms[var].roomID == id)
        {
            _selectableButtons.erase(_selectableButtons.begin() + var); //Will there be a destructor called?
            _selectableRooms.erase(_selectableRooms.begin() + var);
            return true;
        }
    }
    qDebug() << "NAY-001 : Error while RemoveRoomById()! ";
    return false;

}

void RoomSelectionLobby::closeEvent(QCloseEvent *event)
{
    emit SignalUserIsClosingRoomSelectionLobby();
}

void RoomSelectionLobby::SetUpConnections()
{
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::clicked, this, &RoomSelectionLobby::SignalUserIsClosingRoomSelectionLobby);

}
