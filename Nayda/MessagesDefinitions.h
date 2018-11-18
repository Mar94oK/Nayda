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

enum class RoomCreationErrors
{
    NO_ERRORS = 0,
    NO_FREE_SLOTS_AVAILABLE = 1,
    RULES_ARE_NOT_SUPPORTED = 2,
    INCORRECT_SETTINGS = 3
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

struct ErrorType
{
    bool noFreeSlots;
    bool rulesAreNotSupported;
    bool incorrectSettings;
};

struct ClientRoomCreationReplyData
{
    bool _connectionAllowed;        //check
    uint32_t _slotID;               //to identify the slot's number
    uint32_t _freeSlotsLeft;        //how many slots left
    ErrorType _errors;      //to identify the Error

    ClientRoomCreationReplyData(bool connectionAllowed, uint32_t slotID, uint32_t freeSlotsLeft, ErrorType errors) :
        _connectionAllowed(connectionAllowed), _slotID(slotID), _freeSlotsLeft(freeSlotsLeft), _errors(errors)
    { }
};

struct ClientConnectToRoomSettingsData
{
    bool agreeToWait;
    bool connectToAnyRoom;

    ClientConnectToRoomSettingsData(bool agree, bool connectToAny) :
        agreeToWait(agree), connectToAnyRoom(connectToAny)
    { }
};

struct ServerRoomReadyToConnectData
{
    uint32_t roomID;
    QString roomName;
    uint32_t players;
    uint32_t maximumNumberOfPlayers;

    ServerRoomReadyToConnectData(uint32_t id, const QString& name, uint32_t pl, uint32_t maxNumber):
        roomID(id), roomName(name), players(pl), maximumNumberOfPlayers (maxNumber)
    { }
};

struct ClientConnectionToRoomReplyData
{
    std::vector<ServerRoomReadyToConnectData> _rooms;
    uint32_t _queryOrder;

    ClientConnectionToRoomReplyData(const std::vector<ServerRoomReadyToConnectData>& data, uint32_t order):
        _rooms(data), _queryOrder(order)
    { }
};


#define ROOM_ID_NOT_DEFINED 9999

#define NO_QUERY_POSITION 777
#define QUERY_OVERSIZE 999

#endif // PROTOBUFMESSAGESIDENTIFICATORS_H
