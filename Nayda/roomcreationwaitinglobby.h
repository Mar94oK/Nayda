#ifndef ROOMCREATIONWAITINGLOBBY_H
#define ROOMCREATIONWAITINGLOBBY_H

#include <QWidget>
#include "gamesettings.h"
#include <QPushButton>


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
    void SetUpPicturesAddressses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);


private:

    GameSettings _gameSettings;

    const double buttonsWidthCoefficient = 0.1;
    const double buttonsHeightWidthRelatio = 1.0000;

    QString _mainPlayerPictureAddress;

public:

    void SetUpInitalState(GameSettings settings);

signals:

    void SignalUserIsClosingRoomCreationLobby();


};

#endif // ROOMCREATIONWAITINGLOBBY_H
