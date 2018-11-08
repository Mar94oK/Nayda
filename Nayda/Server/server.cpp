#include "Server/server.h"
#include "QDebug"
#include <QtNetwork>
#include <QDebug>
#include "serverMessageSystem.pb.h"
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <sstream>


Server::Server(QObject *parent, RoomPosessionType posessionType) : QObject(parent), _roomPosessionType(posessionType)
{
    m_value = 0;
    _srvrSettings.first = "";
    _srvrSettings.second = "";
    defaultSettings.first = "";
    defaultSettings.second = "";
    ConnectionSetUp();
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
    MessageParser(array, tcpSocket->socketDescriptor());
}

void Server::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Host is closed!";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the "
                                    "host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() <<"The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.";
        break;
    default:
        qDebug() << "The following error occurred: %1." << tcpSocket->errorString();
    }
}

void Server::slot_sendTestDataToServer()
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

   initialQuery.PrintDebugString();

   QByteArray block;
   block.resize(initialQuery.ByteSize());
   initialQuery.SerializeToArray(block.data(), block.size());

   qDebug() << "NAY-0001: Sending data to the server!";
   ConnectionSendOutgoingData(block);
}

void Server::slot_openConnection()
{
    if (_srvrSettings == defaultSettings)
    {
        qDebug() << "Error! Setting are empty!";
    }
    else
    {
        tcpSocket->abort();
        tcpSocket->connectToHost(_srvrSettings.first, static_cast<unsigned short>(_srvrSettings.second.toInt()));
        qDebug() << "Connected!";
        qDebug() << "Now to send data...";
        //sendDataToTheConnection("Some other data");
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

void Server::MessageParser(const QByteArray &data, int socketDescriptor)
{

    qDebug() << "NAY-0001: Parsing Message for socketDescriptor: " << socketDescriptor;

    serverMessageSystem::CommonHeader header;
    if(!header.ParseFromArray(data.data(), data.size()))
    {
       qDebug() << "NAY-0001: Error during protobuf message parsing! ";
       qDebug() << "NAY-001: Array size: array.size()";
       qDebug() << "NAY-0001: Error during protobuf message parsing! ";
    }
    else
    {
       qDebug() << "NAY-0001: Header Parsed successfully! ";
       qDebug() << "NAY-001: Array size: " << data.size();

       switch (header.subsystem())
       {
            case serverMessageSystem::SubSystemID::CONNECTION_SUBSYSTEM:
            {
                switch (header.commandid())
                {
                    case serverMessageSystem::ConnectionSubSysCommandsID::SERVER_INPUT_QUERY_REPLY:
                    {
                        ProcessServerInputQueryReply(data, socketDescriptor);
                    }
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_ROOM_CREATION_REPLY:
                    break;

                    case serverMessageSystem::ConnectionSubSysCommandsID::CLIENT_CONNECTION_TO_ROOM_REPLY:
                    break;

                    default:
                        qDebug() << ("NAY-0001: Unsupported Command in CONNECTION_SUBSYSTEM with CmdID: " + QString::number(header.commandid()));
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

    qDebug() << ("NAY-001: ServerQueryReply: ServerName: " + QString::fromStdString(message.servername()));
    qDebug() << ("NAY-001: ServerQueryReply: ServerName: " + QString::number(message.roomcreationallowed()));
    qDebug() << ("NAY-001: ServerQueryReply: ServerName: " + QString::number(message.connectiontoroomallowed()));

    ServerQueryReplyData replyData(message.roomcreationallowed(),
                              message.connectiontoroomallowed(),
                              QString::fromStdString(message.servername()));

    emit SignalReportServerQueryReplyData(replyData);

}

