#ifndef PROTOBUFMESSAGESIDENTIFICATORS_H
#define PROTOBUFMESSAGESIDENTIFICATORS_H

#include <QString>

namespace MessageSystem {


}

enum class MessageSubSystems
{
    CONNECTION_SUBSYSTEM = 0,
    GAME_ACTIONS_SUBSYSTEM = 1,
    GAME_NOTIFICATION_SUBSYSTEM = 2
};

enum class ConnectionSubSysCommandsID
{
    SERVER_INPUT_QUERY_REQUEST = 0,
    SERVER_INPUT_QUERY_REPLY = 1,
    CLIENT_ROOM_CREATION_REQUEST = 2,
    CLIENT_ROOM_CREATION_REPLY = 3,
    CLIENT_CONNECTION_TO_ROOM_REQUEST = 4,
    CLIENT_CONNECTION_TO_ROOM_REPLY = 5
};

struct ServerQueryReplyData
{
    bool _roomCreationAllowed;
    bool _connectionToRoomAllowed;
    QString _serverName;

    ServerQueryReplyData(bool creationAllowed, bool connectionAllowed, QString name) :
        _roomCreationAllowed(creationAllowed), _connectionToRoomAllowed(connectionAllowed), _serverName(name)
    { }
};

#endif // PROTOBUFMESSAGESIDENTIFICATORS_H
