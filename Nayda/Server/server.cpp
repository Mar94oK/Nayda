#include "Server/server.h"
#include "QDebug"
#include <QtNetwork>
#include <QDebug>



Server::Server(QObject *parent, RoomPosessionType posessionType) : QObject(parent), _roomPosessionType(posessionType)
{
    m_value = 0;
    _srvrSettings.first = "";
    _srvrSettings.second = "";
    defaultSettings.first = "";
    defaultSettings.second = "";
    setupConnection();
}

bool Server::something()
{
    int i = 1;
    return true;
}

void Server::setupConnection()
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

    connect(tcpSocket, &QIODevice::readyRead, this, &Server::readIncomingData);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),this, &Server::displayError);

}

void Server::sendDataToTheConnection(const QString &dataStr)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << dataStr;

    if (tcpSocket->isOpen())
    {
       if (tcpSocket->ConnectedState == QTcpSocket::ConnectedState)
       {
           tcpSocket->write(block);
       }
    }

}



void Server::readIncomingData()
{
    inputStream.startTransaction();

    QString nextFortune;
    inputStream >> nextFortune;

    if (!inputStream.commitTransaction())
        return;

    qDebug() << "Fortune: " << nextFortune;
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
        sendDataToTheConnection("Some other data");
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

