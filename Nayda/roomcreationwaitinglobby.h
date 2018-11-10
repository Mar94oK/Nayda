#ifndef ROOMCREATIONWAITINGLOBBY_H
#define ROOMCREATIONWAITINGLOBBY_H

#include <QWidget>

namespace Ui {
class RoomCreationWaitingLobby;
}

class RoomCreationWaitingLobby : public QWidget
{
    Q_OBJECT

public:
    explicit RoomCreationWaitingLobby(QWidget *parent = 0);
    ~RoomCreationWaitingLobby();

private:
    Ui::RoomCreationWaitingLobby *ui;

private:

    void closeEvent(QCloseEvent *event);

private:

    void setUpUiGeometricRelations();

signals:

    void SignalUserIsClosingRoomCreationLobby();
};

#endif // ROOMCREATIONWAITINGLOBBY_H
