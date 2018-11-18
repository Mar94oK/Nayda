#ifndef ROOMSELECTIONLOBBY_H
#define ROOMSELECTIONLOBBY_H

#include <QDialog>
#include "MessagesDefinitions.h"

namespace Ui {
class RoomSelectionLobby;
}

struct ButtonsPosition
{
    uint32_t row;
    uint32_t column;

    ButtonsPosition (uint32_t rw, uint32_t cl) :
        row(rw), column(cl)
    { }
};

class RoomSelectionLobby : public QDialog
{
    Q_OBJECT

public:
    explicit RoomSelectionLobby(QWidget *parent = 0);
    ~RoomSelectionLobby();

private:
    Ui::RoomSelectionLobby *ui;

    std::vector <ServerRoomReadyToConnectReportData> _selectableRooms;
    std::vector <QPushButton* > _selectableButtons;

private:

    QString _coverPictureAddress;
    QString _doorsCoverPicureAddress;
    QString _buttonsBaseText = "Комната № ";

private:

    void setUpUiPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);
    void setBackgroudImage(QString pictureAddress);

signals:
    void SignalSendConnectToSelectedRoomRequest(uint32_t roomID);


public slots:

    void SlotAddRoomToSelectableList(ServerRoomReadyToConnectReportData room);
    void SlotRemoveRoomFromSelectableList(ServerRoomReadyToConnectReportData room);
    void SlotSendConnectToSelectedRoomRequest(uint32_t roomID);

private:

    void AddSelectableRoomToGUI(ServerRoomReadyToConnectReportData data);
    ButtonsPosition FindPositionFornewButton();
    QPushButton* FindRoomById(uint32_t id);
    bool RemoveRoomById(uint32_t id);



};

#endif // ROOMSELECTIONLOBBY_H
