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

    connect(tcpSocket, &QIODevice::readyRead, this, &Server::SlotConnectionReadIncomingData);
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
//        NAY-001: EXPECTED_ERROR
            return false;
        }
    }
    else
    {
        qDebug() << "Error during data send. Socket is closed! ";
//        NAY-001: EXPECTED_ERROR
        return false;
    }
 }


void Server::SlotConnectionReadIncomingData()
{
    qDebug() << ("SlotConnectionReadIncomingData::Reading Data.");
    //1. Disconnect readyRead signal to be sure the packet will come here, in handler.
    disconnect(tcpSocket, &QIODevice::readyRead, this, &Server::SlotConnectionReadIncomingData);

    QByteArray initialArray;
    //2. Check the bytes available (They will allways be since there's ReadyRead here.)
    qDebug() << "Total Bytes available: " << tcpSocket->bytesAvailable();

    //3. the first one will be lenght;
    qDebug() << "Read lenght first";
    uint32_t lenght = ReadIncomingLenght();
    qDebug() << "Given lenght: " << lenght;

    //4. check if there's lenght (should never get here)
    if (!lenght)
    {
        qDebug() << "Rejecting packet!";
        QByteArray rejectedArray = tcpSocket->readAll();
        qDebug() << "Bytes rejected due to error: " << rejectedArray.size();
        rejectedArray.clear();
        connect(tcpSocket, &QIODevice::readyRead, this, &Server::SlotConnectionReadIncomingData);
        return;
    }

    //NAY-001: EXPECTED_ERROR

    //then wait for ReadyRead if there are no bytes in message.
    if (!tcpSocket->bytesAvailable())
        tcpSocket->waitForReadyRead(1000); //some wait here (non-blocking? - blocking...)

    //then read again, we habe here data
    initialArray = tcpSocket->read(lenght);

    //check BufferSize
    qDebug() << "Initial Buffer Lenght: " << initialArray.length();

    //if there are some bytes still:
    std::vector<QByteArray> theReallyHardVector;
    while (tcpSocket->bytesAvailable())
    {
        qDebug() << "Enter buffering!";
        qDebug() << "Bytes left: " << tcpSocket->bytesAvailable();
        uint32_t lenght = ReadIncomingLenght();
        QByteArray bufferedArray;
        //check if there's lenght
        if (!lenght)
        {
            qDebug() << "Rejecting packet!";
            QByteArray rejectedArray = tcpSocket->readAll();
            qDebug() << "Bytes rejected due to error: " << rejectedArray.size();
            rejectedArray.clear();
        }
        else
        {
            bufferedArray = tcpSocket->read(lenght);
            uint32_t bufferedArrayLenght = bufferedArray.length();
            qDebug() << "Buffer Lenght: " << bufferedArrayLenght;
            if (bufferedArrayLenght)
              theReallyHardVector.push_back(bufferedArray);
            else
            {
                qDebug() << "There's lenght but no message. Reject message.";
                return;
            }
        }

        //waiting for a 300 ms without messages
        QObject().thread()->wait(300);
    }
    //re-enable Reading
    connect(tcpSocket, &QIODevice::readyRead, this, &Server::SlotConnectionReadIncomingData);

    //Take a long time. So first read all till there's nothing to read;
    ProtobufMessageParser(initialArray, tcpSocket->socketDescriptor());
    for (uint32_t var = 0; var < theReallyHardVector.size(); ++var) {
        ProtobufMessageParser(theReallyHardVector[var], tcpSocket->socketDescriptor());
    }

    //this improvement works!!!

}

uint32_t Server::ReadIncomingLenght()
{
    quint32 lenght;
    QByteArray readedLenght;
    readedLenght = tcpSocket->read(sizeof(uint32_t));
    lenght = qFromBigEndian<quint32 >((const uchar*)readedLenght.constData());
    qDebug() << "Lenght from Big Endian : " << lenght;
    return lenght;
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

void Server::SlotUserHaveChangedGameSettings(const GameSettings &settings, bool resetClientsName)
{
    if (!resetClientsName)
    {
        QString nameWas = _gameSettings.clientName();
        _gameSettings.applyNewSettings(settings);
        _gameSettings.setClientName(nameWas);
    }
    else
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
    if (connectionUnexpectedBehaviorTimer->isActive())
        connectionUnexpectedBehaviorTimer->stop();

    tcpSocket->abort();
}

void Server::SlotSendChartMessage(const QString &message)
{
    qDebug() << "NAY-001: Send ChartMessage";
    ConnectionSendOutgoingData(FormChartMessage(message));
}

void Server::SlotSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data)
{
    qDebug() << "NAY-001: Send ClientConnectionToRoomRequest";
    ConnectionSendOutgoingData(FormClientConnectionToRoomRequest(data));
}

void Server::SlotSendClientWantedToEnterTheRoom(uint32_t roomId)
{
    qDebug() << "NAY-001: Send SlotSendClientWantedToEnterTheRoom";
    ConnectionSendOutgoingData(FormClientWantedToEnterTheRoom(roomId));
}

void Server::SlotSendClientHasSoldCards(const TheGameMainGamerHasSoldCards &data)
{
    qDebug() << "NAY-002: Send SlotSendClientHasSoldCards";
    ConnectionSendOutgoingData(FormClientHasSoldCards(data));
}

void Server::SlotSendClientHasImplementedCard(const TheGameMainGamerHasImplementedCard &data)
{
    qDebug() << "NAY-002: Send SlotSendClientHasImplementedCard";
    ConnectionSendOutgoingData(FormClientHasImplementedCard(data));
}

void Server::ProcessClientHasSoldCards(const QByteArray &data, int socketDescriptor)
{
   qDebug() << ("NAY-0001: Error while ProcessClientHasSoldCards() ");
   serverMessageSystem::ClientHasSoldCards message;

   if (!message.ParseFromArray(data.data(), data.size()))
   {
       qDebug() << ("NAY-0001: Error while ProcessClientHasSoldCards() ");
       return;
   }

   std::vector<SimpleCard> soldCards;

   for (uint32_t var = 0; var < static_cast<uint32_t>(message.soldcards_size()); ++var)
   {
       soldCards.push_back(SimpleCard{ message.soldcards(static_cast<int32_t>(var)).doortreasure(),
                           message.soldcards(static_cast<int32_t>(var)).cardid()});
   }
   emit SignalServerReportsPlayerSoldCards(TheGameMainGamerHasSoldCards(message.gamerid(),
                                                                        soldCards,
                                                                        message.leveldelta(),
                                                                        message.gamerid(),
                                                                        message.roomid()));
}

void Server::ProcessClientHasImplementedCard(const QByteArray &data, int socketDescriptor)
{
    qDebug() << "NAY-002: Server::ProcessClientHasImplementedCard.";

    serverMessageSystem::ClientHasImplementedCard message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-0001: Error while ProcessClientHasImplementedCard() ");
        return;
    }

    SimpleCard playedCard(message.card().doortreasure(), message.card().cardid());
    CardImplementationDirection direction;

    switch (message.direction())
    {
    case serverMessageSystem::CardPlayDirection::HAND_TO_CARDS_IN_GAME:
        direction = CardImplementationDirection::HandToCardsInGame;
        break;
    case serverMessageSystem::CardPlayDirection::HAND_TO_BATTLE_FIELD:
        direction = CardImplementationDirection::HandToBattleField;
        break;
    case serverMessageSystem::CardPlayDirection::CARDS_IN_GAME_TO_BATTLE_FIELD:
        direction = CardImplementationDirection::CardsInGameToBattlefield;
        break;
    default:
    {
        qDebug() << "NAY-002: ERROR WHILE Server::ProcessClientHasImplementedCard. Not implemented type of CardImplementationDirection!";
        return;
    }
        break;
    }


    emit SignalServerReportsPlayerHasImplementedCard(TheGameMainGamerHasImplementedCard( message.gamerid(),
                                                                                playedCard,
                                                                                message.roomid(),
                                                                                message.battlestarts(),
                                                                                direction));
}

QByteArray Server::FormClientHasSoldCards(const TheGameMainGamerHasSoldCards &data)
{
    serverMessageSystem::ClientHasSoldCards message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(serverMessageSystem::SubSystemID::GAME_ACTIONS_SUBSYSTEM);
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::GameActionsSubSysCommandsID::CLIENT_HAS_SOLD_CARDS));
    message.set_connectioncmdid(serverMessageSystem::GameActionsSubSysCommandsID::CLIENT_HAS_SOLD_CARDS);

    message.set_gamerid(data.gamerID);
    message.set_iscardprocessing(data.isCardProcessing);
    message.set_leveldelta(data.levelDelta);
    message.set_roomid(data.roomID);

    for (uint32_t var = 0; var < data.soldCards.size(); ++var)
    {
        message.add_soldcards();
        serverMessageSystem::SimpleCard *newCard(message.mutable_soldcards(var));
        newCard->set_cardid(data.soldCards[var].second);
        newCard->set_doortreasure(data.soldCards[var].first);
    }


    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-002: Serialized FormClientHasSoldCards is ready.";
    return block;
}

QByteArray Server::FormClientHasImplementedCard(const TheGameMainGamerHasImplementedCard &data)
{
    serverMessageSystem::ClientHasImplementedCard message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(serverMessageSystem::SubSystemID::GAME_ACTIONS_SUBSYSTEM);
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::GameActionsSubSysCommandsID::CLIENT_HAS_IMPLEMENTED_CARD));
    message.set_connectioncmdid(serverMessageSystem::GameActionsSubSysCommandsID::CLIENT_HAS_IMPLEMENTED_CARD);

    message.set_gamerid(data.gamerID);
    message.set_roomid(data.roomID);
    switch (data.direction)
    {
    case CardImplementationDirection::HandToCardsInGame:
        message.set_direction(serverMessageSystem::CardPlayDirection::HAND_TO_CARDS_IN_GAME);
        break;
    case CardImplementationDirection::HandToBattleField:
        message.set_direction(serverMessageSystem::CardPlayDirection::HAND_TO_BATTLE_FIELD);
        break;
    case CardImplementationDirection::CardsInGameToBattlefield:
        message.set_direction(serverMessageSystem::CardPlayDirection::CARDS_IN_GAME_TO_BATTLE_FIELD);
        break;
    default:
        break;
    }

    serverMessageSystem::SimpleCard *newCard(message.mutable_card());

    newCard->set_doortreasure(data.playedCard.first);
    newCard->set_cardid(data.playedCard.second);

    message.set_battlestarts(data.battleStarts);

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-002: Serialized FormClientHasImplementedCard is ready.";
    return block;
}

void Server::ProtobufMessageParser(const QByteArray &data, int socketDescriptor)
{

    qDebug() << "NAY-0001: Parsing Message for socketDescriptor: " << socketDescriptor;

    serverMessageSystem::DefaultMessage defaultMessage;
    if(!defaultMessage.ParseFromArray(data.data(), data.size()))
    {
       qDebug() << "NAY-001: Error during protobuf message parsing! ";
//       qDebug() << "NAY-001: Array size: array.size()";
    }
    else
    {
//       qDebug() << "NAY-0001: Header Parsed successfully! ";
//       qDebug() << "NAY-0010: Array size: " << data.size();

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
                    ProcessClientConnectionToRoomReply(data, socketDescriptor);
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_REPORTS_OPPONENT_IS_ENTERING_ROOM:
                    {
                        ProcessServerReportsOpponentIsEnteringRoom(data, socketDescriptor);
                    }
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_ROOM_CHANGES_IN_SELECTABLE_LIST:
                    {
                        ProcessServerRoomChangesInSelectableList(data, socketDescriptor);
                        break;
                    }

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_REPORTS_CLIENT_IS_LEAVING:
                    {
                        ProcessServerReportsClientIsLeaving(data, socketDescriptor);
                        break;
                    }

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_REPORTS_ROOM_HAS_CHANGED_OWNER:
                    {
                        ProcessServerReportsRoomHasChangedOwner(data, socketDescriptor);
                        break;
                    }

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_CLIENT_WANTED_TO_ENTER_THE_ROOM_REPLY:
                    ProcessServerClientWantedToEnterTheRoomReply(data,socketDescriptor);
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_REPORTS_THE_GAME_IS_ABOUT_TO_START:
                    ProcessServerReportsTheGameIsAboutToStart(data, socketDescriptor);
                    break;


                    default:
                        qDebug() << ("NAY-0001: Unsupported Command in CONNECTION_SUBSYSTEM with CmdID: " + QString::number(defaultMessage.header().commandid()));
                    break;
                }
            }
            break;
            case serverMessageSystem::SubSystemID::GAME_ACTIONS_SUBSYSTEM:
            {
                switch (defaultMessage.header().commandid())
                {
                    case serverMessageSystem::GameActionsSubSysCommandsID::CLIENT_HAS_SOLD_CARDS:
                    {
                        ProcessClientHasSoldCards(data, socketDescriptor);
                    }
                    break;
                    case serverMessageSystem::GameActionsSubSysCommandsID::CLIENT_HAS_IMPLEMENTED_CARD:
                    {
                        ProcessClientHasImplementedCard(data, socketDescriptor);
                    }
                    break;
                }
                qDebug() << ("NAY-002: Unsupported Command in GAME_ACTIONS_SUBSYSTEM with CmdID: ") << QString::number(defaultMessage.header().commandid());
            }

           break;

       case serverMessageSystem::SubSystemID::GAME_NOTIFICATION_SUBSYSTEM:
           qDebug() << ("NAY-0001: Message SubSystem"
                                      " GAME_NOTIFICATION_SUBSYSTEM "
                                      " Not supported yet.");
           break;

       case serverMessageSystem::SubSystemID::CHART_SUBSYSTEM:
           switch (defaultMessage.header().commandid())
           {
           case serverMessageSystem::ChartSubSysCommandsID::CHART_MESSAGE:
               ProcessChartMessage(data, socketDescriptor);
               break;
           case serverMessageSystem::ChartSubSysCommandsID::CHART_NOTIFICATION:
               qDebug() << ("NAY-0001: Unsupported Command in CHART_SUBSYSTEM with CmdID: " + QString::number(defaultMessage.header().commandid()));
               break;
           default:

               qDebug() << ("NAY-0001: Unsupported Command in CHART_SUBSYSTEM with CmdID: " + QString::number(defaultMessage.header().commandid()));
               serverMessageSystem::ServerClientWantedToEnterTheRoomReply message;

               if (!message.ParseFromArray(data.data(), data.size()))
               {
                   qDebug() << ("NAY-001: Error while ProcessServerRoomChangesInSelectableList() ");
                   return;
               }
               message.PrintDebugString();
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
    qDebug() << "NAY-001: After room creation: _roomID: " << _roomID;

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
    //NAY-001: EXPECTED_ERROR
    //May find some way to check?
    qDebug() << "NAY-001: message: Room ID: " << QString::number(message.roomid());


    QString textMessage = QString::fromStdString(message.sendername());
    textMessage += " : ";
    textMessage += QString::fromStdString(message.chartmessage());

    emit SignalChartMessageReceived(QStringList{QString::fromStdString(message.sendername()),
                                                QString::fromStdString(message.chartmessage())});
}

void Server::ProcessClientConnectionToRoomReply(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ClientConnectionToRoomReply message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessClientConnectionToRoomReply() ");
        return;
    }

    qDebug() << "NAY-001: message: noRoomsAvailable: " << QString::number(message.noroomsavailable());
    qDebug() << "NAY-001: message: FreeSlotsLeft: " << QString::number(message.freeslotsleft());
    qDebug() << "NAY-001: message: queryOrder: " << QString::number(message.queryorder());
    qDebug() << "NAY-001: message: queryOrder: " << QString::number(message.querysize());

    std::vector<ServerRoomReadyToConnectData> messageData;



    for (int var = 0; var < message.room_size(); ++var)
    {
         qDebug() << "NAY-001: message: ClientConnectionToRoomReply: Players: " << QString::number(message.room(var).players());
         qDebug() << "NAY-001: message: ClientConnectionToRoomReply: RoomID: " << QString::number(message.room(var).roomid());
         qDebug() << "NAY-001: message: ClientConnectionToRoomReply: RoomName: " << QString::fromStdString(message.room(var).roomname());
         qDebug() << "NAY-001: message: ClientConnectionToRoomReply: MaximumNumberOfPlayers: " << QString::number(message.room(var).maximumnumberofplayers());
         messageData.push_back(ServerRoomReadyToConnectData(message.room(var).roomid(),
                                                            QString::fromStdString(message.room(var).roomname()),
                                                            message.room(var).players(),
                                                            message.room(var).maximumnumberofplayers(),
                                                             true));
    }

    ClientConnectionToRoomReplyData replyData(messageData, message.queryorder(), message.querysize());

    //check Query order first. If oversized: report immidiately and return;
    if (message.queryorder() == QUERY_OVERSIZE)
    {
        emit SignalServerQueryOversize();
        qDebug() << "NAY-001:  ProcessClientConnectionToRoomReply() QueryOversize!";
        return;
    }
    else
    {
        emit SignalProcessClientConnectionToRoomReply(replyData);
    }


}

void Server::ProcessServerRoomChangesInSelectableList(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerRoomChangesInSelectableList message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerRoomChangesInSelectableList() ");
        return;
    }

    qDebug() << "NAY-001: deleteUpdate Flag: " << message.deletedorupdateflag();


        qDebug() << "NAY-001: Room: ID: " << QString::number(message.room().roomid());
        qDebug() << "NAY-001: Room: Max number of players: " << QString::number(message.room().maximumnumberofplayers());
        qDebug() << "NAY-001: Room: Plaers: " << QString::number(message.room().players());
        qDebug() << "NAY-001: Room: Name: " << QString::fromStdString(message.room().roomname());




    emit SignalProcessServerRoomChangesInSelectableList(ServerRoomReadyToConnectData(message.room().roomid(),
                                                                                     QString::fromStdString(message.room().roomname()),
                                                                                     message.room().players(),
                                                                                     message.room().maximumnumberofplayers(),
                                                                                     message.deletedorupdateflag()));

}

void Server::ProcessServerClientWantedToEnterTheRoomReply(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerClientWantedToEnterTheRoomReply message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerRoomChangesInSelectableList() ");
        return;
    }

    qDebug() << "NAY-001: Entrance allowed: " << message.entranceallowed();

    qDebug() << "NAY-001: Created Room Credentials: ";
    qDebug() << "NAY-001: Room Name: " << QString::fromStdString(message.room().roomname());
    qDebug() << "NAY-001: Room ID: " << QString::number(message.room().roomid());
    qDebug() << "NAY-001: Players: " << QString::number(message.room().players());
    qDebug() << "NAY-001: Maximum number of players: " << QString::number(message.room().maximumnumberofplayers());

    //Setting roomId!
    _roomID = message.room().roomid();

    std::vector<PlayerData> playersData;
    GameSettings givenSettings(message.settings().maximumnumberofplayers(),
                               message.settings().timesettings().totaltimetomove(),
                               message.settings().timesettings().timetothink(),
                               message.settings().timesettings().timeforopponentsdecision(),
                               message.settings().timesettings().diplomacytime(),
                               message.settings().gametype().hasaddonclericalerrors(),
                               message.settings().gametype().hasaddonwildaxe(),
                               QString::fromStdString(message.mastername()),
                               QString::fromStdString(message.room().roomname()),
                               static_cast<RulesType>(message.settings().gametype().rulestype()),
                               message.settings().settingscorrectionallowed());

    for (uint32_t var = 0; var < message.room().player_size(); ++var)
    {
        qDebug() << "NAY-001 : Player ID: " << QString::number(message.room().player(var).playerid());
        qDebug() << "NAY-001 : Player ID: " << QString::fromStdString(message.room().player(var).playername());
        playersData.push_back(PlayerData(QString::fromStdString(message.room().player(var).playername()),
                                         message.room().player(var).playerid()));
    }

    //ServerClientWantedToEnterTheRoomReplyData
    //PlayerData

    emit SignalProcessServerClientWantedToEnterTheRoomReply(ServerClientWantedToEnterTheRoomReplyData(message.entranceallowed(),
                                                                                                      message.room().roomid(),
                                                                                                      QString::fromStdString(message.room().roomname()),
                                                                                                      QString::fromStdString(message.mastername()),
                                                                                                      message.room().players(),
                                                                                                      message.room().maximumnumberofplayers(),
                                                                                                      playersData,
                                                                                                      givenSettings
                                                                                                      ));


}

void Server::ProcessServerReportsClientIsLeaving(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerReportsClientIsLeaving message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerRoomChangesInSelectableList() ");
        return;
    }

    qDebug() << "NAY-001: ProcessServerReportsClientIsLeaving() ClientName: " << QString::fromStdString(message.clientname());
    qDebug() << "NAY-001: ProcessServerReportsClientIsLeaving() SocketDescriptor: " << QString::number(message.socketdescriptor());

    emit SignalServerReportsClientIsLeavingRoom(QString::fromStdString(message.clientname()));

}

void Server::ProcessServerReportsRoomHasChangedOwner(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerReportsRoomHasChangedOwner message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerRoomChangesInSelectableList() ");
        return;
    }

    qDebug() << "NAY-001: ProcessServerReportsRoomHasChangedOwner() PreviousOwner: " << QString::fromStdString(message.previousowner());
    qDebug() << "NAY-001: ProcessServerReportsRoomHasChangedOwner() CurrentOwner: " << QString::fromStdString(message.currentowner());

    emit SignalProcessServerReportsRoomHasChangedOwner(QString::fromStdString(message.previousowner()),
                                                       QString::fromStdString(message.currentowner()));
}

void Server::ProcessServerReportsTheGameIsAboutToStart(const QByteArray &data, int socketDescriptor)
{
    serverMessageSystem::ServerReportsTheGameIsAboutToStart message;

    if (!message.ParseFromArray(data.data(), data.size()))
    {
        qDebug() << ("NAY-001: Error while ProcessServerRoomChangesInSelectableList() ");
        return;
    }

    qDebug() << "NAY-001: ProcessServerReportsTheGameIsAboutToStart() start: " << message.start();

    std::vector<uint32_t> positionsDoors;
    for (uint32_t var = 0; var < message.posdoors_size(); ++var)
    {
        positionsDoors.push_back(message.posdoors(var));
        qDebug() << QString::number(message.posdoors(var));
    }

    std::vector<uint32_t> positionsTreasures;
    for (uint32_t var = 0; var < message.postreasures_size(); ++var)
    {
        positionsTreasures.push_back(message.postreasures(var));
        qDebug() << QString::number(message.postreasures(var));
    }

    std::vector<QString> players;
    for (uint32_t var = 0; var < message.playersorder_size(); ++var)
    {
        players.push_back(QString::fromStdString(message.playersorder(var)));
        qDebug() << QString::fromStdString(message.playersorder(var));
    }

    emit SignalServerReportsTheGameIsAboutToStart(TheGameIsAboutToStartData(message.start(),
                                                  positionsDoors,
                                                  positionsTreasures,
                                                  players));
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
        //NAY-001: EXPECTED_ERROR.
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
    message.set_roomname(_gameSettings.roomName().toUtf8().constData());

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

QByteArray Server::FormClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data)
{
    serverMessageSystem::ClientConnectionToRoomRequest message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM);
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_CONNECTION_TO_ROOM_REQUEST));
    message.set_connectioncmdid(serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_CONNECTION_TO_ROOM_REQUEST);
    message.set_clientname(_gameSettings.clientName().toUtf8().constData());
    message.set_agreetowait(data.agreeToWait);
    message.set_connecttoanyroom(data.connectToAnyRoom);

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-001: Serialized FromClientConnectionToRoomRequest is ready.";
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

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-001: Serialized FormChartMessage is ready.";
    return block;
}

QByteArray Server::FormClientWantedToEnterTheRoom(uint32_t roomId)
{
    serverMessageSystem::ClientWantedToEnterTheRoom message;
    serverMessageSystem::CommonHeader *header(message.mutable_header());
    header->set_subsystem(serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM);
    header->set_commandid(static_cast<uint32_t>(serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_WANTED_TO_ENTER_THE_ROOM));
    message.set_connectioncmdid(serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_WANTED_TO_ENTER_THE_ROOM);
    message.set_clientname(_gameSettings.clientName().toUtf8().constData());
    message.set_roomid(roomId);

    QByteArray block;
    block.resize(message.ByteSize());
    message.SerializeToArray(block.data(), block.size());
    qDebug() << "NAY-001: Serialized FormClientWantedToEnterTheRoom is ready.";
    return block;

}

