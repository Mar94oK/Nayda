#ifndef ROOMCREATIONWAITINGLOBBY_H
#define ROOMCREATIONWAITINGLOBBY_H

#include <QWidget>
#include "gamesettings.h"
#include <QPushButton>
#include <QTimer>
#include "MessagesDefinitions.h"

#define FIRST_OPPONENT_AWAITING 0
//#define ALL_OPPONENTS_ARE_HERE 6

namespace Ui {
class RoomCreationWaitingLobby;
}

class RoomCreationWaitingLobby : public QWidget
{
    Q_OBJECT

public:
    explicit RoomCreationWaitingLobby(const GameSettings& settings, QWidget *parent = 0);
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
    void SetUpSignalsSlotsConnections();

    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);
    void SetUpOpponentsName(QPushButton* btn, const QString& name);
    bool CheckOpponentNameIsUnique(const QString& name);

private:

    GameSettings _gameSettings;

    const double buttonsWidthCoefficient = 0.1;
    const double buttonsHeightWidthRelatio = 1.0000;

    QString _mainPlayerPictureAddress;

    QTimer* _backCountTimer;

public:

    void SetUpInitalState(GameSettings settings);

    uint32_t currentOpponentAwaiting() const;
    void setCurrentOpponentAwaiting(const uint32_t &currentOpponentAwaiting);

    void SetUpForNotMasterPossessionType(const ServerClientWantedToEnterTheRoomReplyData& data);
    void RedrawForMasterPossessionType(const ServerClientWantedToEnterTheRoomReplyData& data);

signals:

    void SignalUserIsClosingRoomCreationLobby();
    void SignalAllThePlayersAreHere();
    void SignalChartMessageReceived(const QStringList& message);
    void SignalChartMessageToBeSend(const QString& message);


public slots:

    void SlotProcessServerReportsOpponentIsEnteringRoom(const QString& opponentName);

    //Error processing
    void SlotProcessRemoteHostClosedErrorReport();

    void SlotProcessChartMessageReceived(const QStringList& message)
    { emit SignalChartMessageReceived(message); }

    void SlotProcessChartMessageSending(const QString& message)
    { emit SignalChartMessageToBeSend(message); }

    void SlotProcessServerReportsClientIsLeaving(const QString& name);

    void SlotProcessServerReportsRoomHasChangedOwner(const QString& previousOwner, const QString& currentOwner);

private:

    std::vector<QPushButton*> _opponnets;
    uint32_t _currentOpponentAwaiting = 0;
    std::vector<QString> _opponentsNames;
    QString _masterName;

public:

    const std::vector<QString>& GetPlayersOrder()
    {
        _opponentsNames.insert(_opponentsNames.begin(), _masterName);
        return _opponentsNames;
    }

private slots:

    void EnbleBackCounterToTheGameStart();
    void SlotBackCounterSetNewValue(QString value);

};

#endif // ROOMCREATIONWAITINGLOBBY_H
