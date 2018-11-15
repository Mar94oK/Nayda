#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

#include <QObject>
#include <QString>
#include <Application/card.h> //cards
#include <QTcpSocket>
#include <QDataStream>
#include <QNetworkSession>
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include "QDebug"
#include <QtNetwork>
#include <QDebug>
#include "gamesettings.h"
#include "MessagesDefinitions.h"
#include <QStringList>


QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

typedef QPair<QString, QString> serverSettings;

enum class RoomPosessionType {RoomMaster, RoomGuest};

  class Server : public QObject
  {
      Q_OBJECT

private:

     int m_value;
     Game_Card_Stock _Main_Doors;
     Game_Card_Stock _Main_Treausures;
     Game_Card_Stock _Fold_Doors;
     Game_Card_Stock _Fold_Treasures;
     Game_Card_Stock _Basis_Doors;
     Game_Card_Stock _Basis_Treasures;

     QPair<QString, QString> defaultSettings;
     QTimer *connectionUnexpectedBehaviorTimer;

private:

    QTcpSocket* tcpSocket;
    QNetworkSession* networkSession;
    QDataStream inputStream;
    QDataStream outputSream;
    serverSettings _srvrSettings;

    bool _socketStateHandlerReportedConnectedState;

private:

    RoomPosessionType _roomPosessionType;
    uint32_t _roomID = ROOM_ID_NOT_DEFINED;

public:

    explicit Server(QObject* parent =  nullptr, RoomPosessionType posessionType = RoomPosessionType::RoomMaster);
    int value() const { return m_value; }

    void ConnectionSetUp();
    void sendCreateNewRoomMessage();
    void ConnectionSendOutgoingData(const QString&);
    bool ConnectionSendOutgoingData(const QByteArray& data);

private slots:

    //void slotReadIncomingData();
    void slotConnectionReadIncomingData();
    void displayError(QAbstractSocket::SocketError socketError);
    void SlotSocketStateChanged(QAbstractSocket::SocketState state);


public slots:

    void slot_saveServerSettings(serverSettings settings)
    {
        _srvrSettings = settings;
        qDebug() << "Server settings saved!";
    }

    void SlotSendTestDataToServer();
    void SlotSetUpConnection();
    void slot_sessionOpened();

    void SlotUserHaveChangedGameSettings(const GameSettings& settings);
    void SlotSendClientRoomCreationRequest();
    void SlotCloseConnectionByUserInitiative();
    void SlotSendChartMessage(const QString& message);


signals:

    void valueChanged(int newValue);
    void socketErrorReportToGUI(QAbstractSocket::SocketError signal);
    void SignalSocketConnectionSuccessReportToGui(bool);
    void SignalServerHasChangedGameSettings(const GameSettings&);
    void SignalReportServerQueryReplyData(ServerQueryReplyData data);
    void SignalReportClientRoomCreationReplyData(ClientRoomCreationReplyData data);
    void SignalServerReportsOpponentIsEnteringRoom(const QString& clientName);

    void SignalChartMessageReceived(const QStringList& message);

//error signals

    void SignalRemoteHostClosedErrorReport();
    void SignalRemoteHostConnectionRefusedErrorReport();
    void SignalRemoteHostNotFoundErrorReport();
    void SignalLockConnectionButtonWhileConnecting();
    void SignalUnlockConnectionButtonAfterConnection();

private:

    GameSettings _gameSettings;

private:

    void ProtobufMessageParser(const QByteArray& data, int socketDescriptor);
    void ProcessServerInputQueryReply(const QByteArray &data, int socketDescriptor);
    void ProcessClientRoomCreationReply(const QByteArray &data, int socketDescriptor);
    void ProcessServerReportsOpponentIsEnteringRoom(const QByteArray &data, int socketDescriptor);
    void ProcessChartMessage(const QByteArray &data, int socketDescriptor);

    void SocketErorHandler(QAbstractSocket::SocketError socketError);
    void SetUpConnectionTImeoutTimer();
    void ConnectionUnexpectedBehaviourHandler();

    QString _currentUnheldedErrorString = "";


public:

    QByteArray FormServerInputQueryRequest();
    QByteArray FormClientRoomCreationRequest();
    QByteArray FromClientConnectionToRoomRequest();
    QByteArray FormChartMessage(const QString& textMessage);

};


#endif // SERVER_H
