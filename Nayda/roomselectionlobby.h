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

    std::vector <ServerRoomReadyToConnectData> _selectableRooms;
    std::vector <QPushButton* > _selectableButtons;

private:

    QString _coverPictureAddress;
    QString _doorsCoverPicureAddress;
    QString _buttonsBaseText = "Комната № ";
    QString _querySizeBaseText = "Манчкинов, готовых отправиться во мрак подземелий: ";
    QString _queryOrderBaseText = "Номер в очереди: ";

private:

    void setUpUiPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);
    void setBackgroudImage(QString pictureAddress);

signals:
    void SignalSendConnectToSelectedRoomRequest(uint32_t roomID);
    void SignalUserIsClosingRoomSelectionLobby();


public slots:

    void SlotAddRoomToSelectableList(ServerRoomReadyToConnectData room);
    void SlotRemoveRoomFromSelectableList(ServerRoomReadyToConnectData room);
    void SlotSendConnectToSelectedRoomRequest(uint32_t roomID);
    void SlotUpdateQuerySize(uint32_t querySize);
    void SlotUpdateQueryOrder(uint32_t queryOrder);

private:

    void AddSelectableRoomToGUI(ServerRoomReadyToConnectData data);
    ButtonsPosition FindPositionFornewButton();
    QPushButton* FindRoomById(uint32_t id);
    bool RemoveRoomById(uint32_t id);

private:

    void closeEvent(QCloseEvent *event);

    void SetUpConnections();

private:

    uint32_t _queryPosition;
    uint32_t _querySize;



};

#endif // ROOMSELECTIONLOBBY_H
