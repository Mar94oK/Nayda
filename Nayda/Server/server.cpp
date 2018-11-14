#include "Server/server.h"
#include "QDebug"
#include <QtNetwork>
#include <QDebug>
#include "serverMessageSystem.pb.h"
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <sstream>
#include <QThread>
#include <QTimer>


Server::Server(QObject *parent, RoomPosessionType posessionType) : QObject(parent), _roomPosessionType(posessionType)
{
    m_value = 0;
    _srvrSettings.first = "";
    _srvrSettings.second = "";
    defaultSettings.first = "";
    defaultSettings.second = "";
    ConnectionSetUp();
    SetUpConnectionTImeoutTimer();

    QObject::connect(connectionUnexpectedBehaviorTimer, &QTimer::timeout, this, &Server::ConnectionUnexpectedBehaviourHandler);
}

void Server::ConnectionSetUp()
{
    tcpSocket = new QTcpSocket(this);

    inputStream.setDevice(tcpSocket);
    inputStream.setVersion(QDataStream::Qt_4_0);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &Server::slot_sessionOpened);
        networkSession->open();
    }

    connect(tcpSocket, &QIODevice::readyRead, this, &Server::slotConnectionReadIncomingData);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),this, &Server::displayError);
    connect(tcpSocket, &QAbstractSocket::stateChanged, this, &Server::SlotSocketStateChanged);

}

bool Server::ConnectionSendOutgoingData(const QByteArray &data)
{
    if (tcpSocket->isOpen())
    {
        if (tcpSocket->ConnectedState == QTcpSocket::ConnectedState)
        {
             tcpSocket->write(data);
             return true;
        }
        else
        {
            qDebug() << "Error during data send. Socket is not closed, but in NOTConnected state! ";
//        NAY-001: MARK_EXPECTED_ERROR
            return false;
        }
    }
    else
    {
        qDebug() << "Error during data send. Socket is closed! ";
//        NAY-001: MARK_EXPECTED_ERROR
        return false;
    }
 }


void Server::slotConnectionReadIncomingData()
{
    qDebug() << ("Trying to read the info...");
    QByteArray array;
    qDebug() << "NAY-0001: Before message parsing! ";
    array = tcpSocket->readAll();
    ProtobufMessageParser(array, tcpSocket->socketDescriptor());
}

void Server::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "displayError()";
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    {
        qDebug() << "Host is closed!";
        if (connectionUnexpectedBehaviorTimer->isActive())
            connectionUnexpectedBehaviorTimer->stop();
        emit SignalRemoteHostClosedErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
    }
    break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the "
                                    "host name and port settings.";
        if (connectionUnexpectedBehaviorTimer->isActive())
            connectionUnexpectedBehaviorTimer->stop();
        emit SignalRemoteHostNotFoundErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
        break;
    case QAbstractSocket::ConnectionRefusedError:
    {
        qDebug() <<"The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.";
        if (connectionUnexpectedBehaviorTimer->isActive())
            connectionUnexpectedBehaviorTimer->stop();
        emit SignalRemoteHostConnectionRefusedErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
    }
        break;
    default:
        qDebug() << "The following error occurred: %1." << tcpSocket->errorString();
    }
}

void Server::SlotSocketStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::SocketState::ClosingState:
        qDebug() << "Socket is in the Closing State";
        _socketStateHandlerReportedConnectedState = false;
        break;
    case QAbstractSocket::SocketState::ConnectedState:
        qDebug() << "Socket is in the Connected State!";
        _socketStateHandlerReportedConnectedState = true;
        emit SignalUnlockConnectionButtonAfterConnection();
        ConnectionSendOutgoingData(FormServerInputQueryRequest());
        break;
    case QAbstractSocket::SocketState::UnconnectedState:
        _socketStateHandlerReportedConnectedState = false;
        qDebug() << "Socket is in the UnconnectedState State!";
        break;
    case QAbstractSocket::SocketState::HostLookupState:
        _socketStateHandlerReportedConnectedState = false;
        qDebug() << "Socket is in the HostLookupState State!";
        break;
    case QAbstractSocket::SocketState::BoundState:
        _socketStateHandlerReportedConnectedState = false;
        qDebug() << "Socket is in the BoundState State!";
        break;
    case QAbstractSocket::SocketState::ListeningState:
        _socketStateHandlerReportedConnectedState = false;
        qDebug() << "Socket is in the ListeningState State!";
        break;
    case QAbstractSocket::SocketState::ConnectingState:
        _socketStateHandlerReportedConnectedState = false;
        qDebug() << "Socket is in the ConnectingState State!";
        break;

    default:
        qDebug() << "Socket is in the Some Another State!";
        _socketStateHandlerReportedConnectedState = false;
        break;
    }
}

void Server::SlotSendTestDataToServer()
{
   serverMessageSystem::ServerInputQuery initialQuery;
   serverMessageSystem::CommonHeader *header(initialQuery.mutable_header());
   header->set_subsystem(serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM);
   header->set_commandid(static_cast<uint32_t>(serverMessageSystem::ConnectionSubSysCommandsID::SERVER_INPUT_QUERY_REQUEST));
   initialQuery.set_connectioncmdid(serverMessageSystem::ConnectionSubSysCommandsID::SERVER_INPUT_QUERY_REQUEST);
   initialQuery.set_clientname(_gameSettings.clientName().toUtf8().constData());
   QString OSName("");
#ifdef Q_OS_WIN
  OSName = "Windows";
#elif defined __linux__
  OSName = "Linux";
#endif
   initialQuery.set_ostype(OSName.toUtf8().constData());

   QByteArray block;
   block.resize(initialQuery.ByteSize());
   initialQuery.SerializeToArray(block.data(), block.size());

   qDebug() << "NAY-0001: Sending data to the server!";
   ConnectionSendOutgoingData(block);
}

void Server::SlotSetUpConnection()
{
    if (_srvrSettings == defaultSettings)
    {
        qDebug() << "Error! Setting are empty!";
    }
    else
    {
        tcpSocket->abort();
        tcpSocket->connectToHost(_srvrSettings.first, static_cast<unsigned short>(_srvrSettings.second.toInt()));

        //Error signal will be emmitted here if socket connection was refused.
        //Place handler there.

        qDebug() << "Preparing the timer!";
        emit SignalLockConnectionButtonWhileConnecting();
        connectionUnexpectedBehaviorTimer->setInterval(15000);
        connectionUnexpectedBehaviorTimer->start();
    }
}

void Server::slot_sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

void Server::SlotUserHaveChangedGameSettings(const GameSettings &settings)
{
    _gameSettings.applyNewSettings(settings);
    //NAY-001: EMIT HERE SIGNAL TO NOTIFY REMMOTE SERVER
}

void Server::SlotSendClientRoomCreationRequest()
{
    qDebug() << "NAY-001: Send Room Creation Request";
    ConnectionSendOutgoingData(FormClientRoomCreationRequest());
}

void Server::SlotCloseConnectionByUserInitiative()
{
    qDebug() << "NAY-001: Aborting connection by user initiative.";
    tcpSocket->abort();
}

void Server::SlotSendChartMessage(const QString &message)
{
    qDebug() << "NAY-001: Send ChartMessage";
    ConnectionSendOutgoingData(FormChartMessage(message));
}

void Server::ProtobufMessageParser(const QByteArray &data, int socketDescriptor)
{

    qDebug() << "NAY-0001: Parsing Message for socketDescriptor: " << socketDescriptor;

    serverMessageSystem::DefaultMessage defaultMessage;
    if(!defaultMessage.ParseFromArray(data.data(), data.size()))
    {
       qDebug() << "NAY-0001: Error during protobuf message parsing! ";
       qDebug() << "NAY-001: Array size: array.size()";
    }
    else
    {
       qDebug() << "NAY-0001: Header Parsed successfully! ";
       qDebug() << "NAY-0010: Array size: " << data.size();

       switch (defaultMessage.header().subsystem())
       {
            case serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM:
            {
                switch (defaultMessage.header().commandid())
                {
                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_INPUT_QUERY_REPLY:
                    {
                        ProcessServerInputQueryReply(data, socketDescriptor);
                    }
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_ROOM_CREATION_REPLY:
                    {
                        ProcessClientRoomCreationReply(data, socketDescriptor);
                    }
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_CONNECTION_TO_ROOM_REPLY:
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_REPORTS_OPPONENT_IS_ENTERING_ROOM:
                    {
                        ProcessServerReportsOpponentIsEnteringRoom(data, socketDescriptor);
                    }
                    break;


                    default:
                        qDebug() << ("NAY-0001: Unsupported Command in CONNECTION_SUBSYSTEM with CmdID: " + QString::number(defaultMessage.header().commandid()));
                    break;
                 }
            }
            break;
       case serverMessageSystem::SubSystemID::GAME_ACTIONS_SUBSYSTEM:
           qDebug() << ("NAY-0001: Message SubSystem"
                                      " GAME_ACTIONS_SUBSYSTEM "
                                      " Not supported yet.");
           break;

       case serverMessageSystem::SubSystemID::GAME_NOTIFICATION_SUBSYSTEM:
           qDebug() << ("NAY-0001: Message SubSystem"
                                      " GAME_NOTIFICATION_SUBSYSTEM "
                                      " Not supported yet.");
           break;

       case serverMessageSystem::SubSystemID::CHART_SUBSYSTEM:
           switch (defaultMessage.header().commandid())
           {
           qDebug() << "Chart SubSystem! ";
           case serverMessageSystem::ChartSubSysCommandsID::CHART_MESSAGE:
               ProcessChartMessage(data, socketDescriptor);
               break;
           case serverMessageSystem::ChartSubSysCommandsID::CHART_NOTIFICATION:
               qDebug() << ("NAY-0001: Unsupported Command in CHART_SUBSYSTEM with CmdID: " + QString::number(defaultMessage.header().commandid()));
               break;
           default:
               qDebug() << ("NAY-0001: Unsupported Command in CHART_SUBSYSTEM with CmdID: " + QString::number(defaultMessage.header().commandid()));
               break;
           }
           break;

       default:
           qDebug() << ("NAY-0001: Message SubSystem"
                                      " GAME_NOTIFICATION_SUBSYSTEM "
                                      " Not supported yet.");
           break;
       }
    }

}

void Server::ProcessServerInputQueryReply(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerQueryReply message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerInputQueryReply() ");
        return;
    }

    ServerQueryReplyData replyData(message.roomcreationallowed(),
                              message.connectiontoroomallowed(),
                              QString::fromStdString(message.servername()));

    emit SignalReportServerQueryReplyData(replyData);
}

void Server::ProcessClientRoomCreationReply(const QByteArray &data, int socketDescriptor)
{
     qDebug() << ("NAY-0001: Error while ProcessClientRoomCreationReply() ");
    serverMessageSystem::ClientRoomCreationReply message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-0001: Error while ProcessClientRoomCreationReply() ");
        return;
    }

    qDebug() << "Message ClientRoomCreationReply: connectionAllowed() " << message.connectionallowed();
    qDebug() << "Message ClientRoomCreationReply: message.slotid() " << message.slotid();
    qDebug() << "Message ClientRoomCreationReply: message.freeslotsleft() " << message.freeslotsleft();
    qDebug() << "Message ClientRoomCreationReply: message.roomcreationerrors().nofreeslotsavailable() " << message.roomcreationerrors().nofreeslotsavailable();
    qDebug() << "Message ClientRoomCreationReply: message.roomcreationerrors().rulesarenotsupported() " << message.roomcreationerrors().rulesarenotsupported();
    qDebug() << "Message ClientRoomCreationReply: message.roomcreationerrors().incorrectsettings() " << message.roomcreationerrors().incorrectsettings();


    ErrorType errors;
    if (message.roomcreationerrors().nofreeslotsavailable())
        errors.noFreeSlots = true;
    else
        errors.noFreeSlots = false;
    if (message.roomcreationerrors().rulesarenotsupported())
        errors.rulesAreNotSupported = true;
    else
        errors.rulesAreNotSupported = false;
    if (message.roomcreationerrors().incorrectsettings())
        errors.incorrectSettings = true;
    else
        errors.incorrectSettings = false;

    _roomID = message.slotid();
    ClientRoomCreationReplyData replyData(message.connectionallowed(), message.slotid(), message.freeslotsleft(), errors);
    emit SignalReportClientRoomCreationReplyData(replyData);
}

void Server::ProcessServerReportsOpponentIsEnteringRoom(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerReportsOpponentIsEnteringRoom message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerReportsOpponentIsEnteringRoom() ");
        return;
    }

    qDebug() << "NAY-001: message: Opponent's name: " << QString::fromStdString(message.opponentname());
    qDebug() << "NAY-001: message: Room's id: " << message.roomid();

    _roomID = message.roomid();

    emit SignalServerReportsOpponentIsEnteringRoom(QString::fromStdString(message.opponentname()));

}

void Server::ProcessChartMessage(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ChartMessage message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerReportsOpponentIsEnteringRoom() ");
        return;
    }

    qDebug() << "NAY-001: message: Sender's name: " << QString::fromStdString(message.sendername());
    qDebug() << "NAY-001: message: Message: " << QString::fromStdString(message.chartmessage());
    //NAY-001: MARK_EXPECTED_ERROR
    //May find some way to check?
    qDebug() << "NAY-001: message: Room ID: " << QString::number(message.roomid());


    QString textMessage = QString::fromStdString(message.sendername());
    textMessage += " : ";
    textMessage += QString::fromStdString(message.chartmessage());

    emit SignalChartMessageReceived(textMessage);
}


void Server::SocketErorHandler(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Host is closed!";
        emit SignalRemoteHostClosedErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the "
                                    "host name and port settings.";
        emit SignalRemoteHostNotFoundErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() <<"The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.";
        emit SignalRemoteHostConnectionRefusedErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug() <<"Connection has been timed out!";
        emit SignalRemoteHostConnectionRefusedErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
        break;
    default:
        qDebug() << "The following error occurred: %1." << tcpSocket->errorString();
        _currentUnheldedErrorString = tcpSocket->errorString();
    }
}

void Server::SetUpConnectionTImeoutTimer()
{
    connectionUnexpectedBehaviorTimer = new QTimer(this);
    connectionUnexpectedBehaviorTimer->setSingleShot(true);
    connectionUnexpectedBehaviorTimer->setInterval(15000);
}

void Server::ConnectionUnexpectedBehaviourHandler()
{
    //for the fact, should never go here...
    if (_socketStateHandlerReportedConnectedState)
    {
        qDebug() << "Socket State Handler Reported Connected state Earlier then the timer. Nothing to do here!";
        return;
    }

    if (tcpSocket->state() != QTcpSocket::SocketState::ConnectedState)
    {
        qDebug() << "Connection unhelded error occured,"
                    "or unhelded behaviour timeout is longer then the system timeout!";
        //NAY-001: MARK_EXPECTED_ERROR.
        //By the fact, the Error occured here might differ from the actual error reported by the signal.
        //Consider reworking the handler of the errors making signal signal-slot connection passing actual error there
        emit SignalRemoteHostNotFoundErrorReport();
        emit SignalUnlockConnectionButtonAfterConnection();
    }
    else
    {
        qDebug() << "Connected!";
        qDebug() << "Ready to send data";
        qDebug() << "NAY-0001: Sending ServerQueryRequest!";
        emit SignalUnlockConnectionButtonAfterConnection();
        ConnectionSendOutgoingData(FormServerInputQueryRequest());
    }
}



QByteArray Server::FormServerInputQueryRequest()
{
    serverMessageSystem::ServerInputQuery message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM);
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::ConnectionSubSysCommandsID::SERVER_INPUT_QUERY_REQUEST));
    message.set_connectioncmdid(serverMessageSystem::ConnectionSubSysCommandsID::SERVER_INPUT_QUERY_REQUEST);
    message.set_clientname(_gameSettings.clientName().toUtf8().constData());
    QString OSName("");

 #ifdef Q_OS_WIN
   OSName = "Windows";
 #elif defined __linux__
   OSName = "Linux";
 #endif

    message.set_ostype(OSName.toUtf8().constData());

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-001: Serialized FormServerInputQueryRequest is ready.";
    return block;
}



QByteArray Server::FormClientRoomCreationRequest()
{
    serverMessageSystem::ClientRoomCreationRequest message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM);
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_ROOM_CREATION_REQUEST));
    message.set_connectioncmdid(serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_ROOM_CREATION_REQUEST);
    message.set_clientname(_gameSettings.clientName().toUtf8().constData());

    serverMessageSystem::GameSettings *settings(message.mutable_gamesettings());
    settings->set_settingscorrectionallowed(_gameSettings.settingsCorrectionAllowed());
    settings->set_maximumnumberofplayers(_gameSettings.maximumNumberOfPlayers());
    serverMessageSystem::GameType *gameType(settings->mutable_gametype());
    gameType->set_hasaddonwildaxe(_gameSettings.hasAddonWildAxe());
    gameType->set_hasaddonclericalerrors(_gameSettings.hasAddonClericalErrors());
    gameType->set_rulestype(serverMessageSystem::RulesType::Automatic);

    serverMessageSystem::TimeSettings *timeSettings(settings->mutable_timesettings());
    timeSettings->set_diplomacytime(_gameSettings.diplomacyTime());
    timeSettings->set_timeforopponentsdecision(_gameSettings.timeForOpponentsDecision());
    timeSettings->set_timetothink(_gameSettings.timeToThink());
    timeSettings->set_totaltimetomove(_gameSettings.totalTimeToMove());

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-001: Serialized FormServerInputQueryRequest is ready.";
    return block;
}

QByteArray Server::FormChartMessage(const QString &textMessage)
{
    serverMessageSystem::ChartMessage message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(::serverMessageSystem::SubSystemID::CHART_SUBSYSTEM);
    qDebug() << "NAY-001::SubSystemID: " << message.header().subsystem();
    qDebug() << "NAY-001:: Chart message command id: " << serverMessageSystem::ChartSubSysCommandsID::CHART_MESSAGE;
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::ChartSubSysCommandsID::CHART_MESSAGE));
    message.set_chartcmdid(serverMessageSystem::ChartSubSysCommandsID::CHART_MESSAGE);
    message.set_sendername(_gameSettings.clientName().toUtf8().constData());
    message.set_chartmessage(textMessage.toUtf8().constData());

    //NAY-001: WHERE TO SAVE THIS DATA?
    //De-facto, now it is needed only by the server.
    message.set_roomid(_roomID);

    message.PrintDebugString();

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-001: Serialized FormChartMessage is ready.";
    return block;
}
