#ifndef ROOMCREATIONWAITINGLOBBY_H
#define ROOMCREATIONWAITINGLOBBY_H

#include <QWidget>
#include "gamesettings.h"
#include <QPushButton>


#define FIRST_OPPONENT_AWAITING 0
//#define ALL_OPPONENTS_ARE_HERE 6

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
    void SetUpOpponentsName(QPushButton* btn, const QString& name);
    bool CheckOpponentNameIsUnique(const QString& name);

private:

    GameSettings _gameSettings;

    const double buttonsWidthCoefficient = 0.1;
    const double buttonsHeightWidthRelatio = 1.0000;

    QString _mainPlayerPictureAddress;

public:

    void SetUpInitalState(GameSettings settings);

    uint32_t currentOpponentAwaiting() const;
    void setCurrentOpponentAwaiting(const uint32_t &currentOpponentAwaiting);

signals:

    void SignalUserIsClosingRoomCreationLobby();
    void SignalAllThePlayersAreHere();

public slots:

    void SlotProcessServerReportsOpponentIsEnteringRoom(const QString& opponentName);

    //Error processing
    void SlotProcessRemoteHostClosedErrorReport();

private:

    std::vector<QPushButton*> _opponnets;
    uint32_t _currentOpponentAwaiting;
    std::vector<QString> _opponentsNames;



};

#endif // ROOMCREATIONWAITINGLOBBY_H
