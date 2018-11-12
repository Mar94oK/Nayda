#ifndef ROOMCREATIONWAITINGLOBBY_H
#define ROOMCREATIONWAITINGLOBBY_H

#include <QWidget>
#include "gamesettings.h"


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
    void applyNewSettings(GameSettings settings);
    void setUpCreatorsName(const QString& name);

private:

    GameSettings _gameSettings;

public:

    void SetUpInitalState(GameSettings settings);

signals:

    void SignalUserIsClosingRoomCreationLobby();


};

#endif // ROOMCREATIONWAITINGLOBBY_H
