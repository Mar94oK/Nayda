#ifndef PROTOBUFMESSAGESIDENTIFICATORS_H
#define PROTOBUFMESSAGESIDENTIFICATORS_H


#define MessageServerInputQueryID 1
#define MessageServerQueryReplyID 2
#define MessageClientEnteringRequestID 3
#define MessageClientRoomCreationReplyID 4
#define MessageClientConnectionToRoomReplyID 5

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

#endif // PROTOBUFMESSAGESIDENTIFICATORS_H
