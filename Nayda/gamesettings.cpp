#include "gamesettings.h"
#include <QTime>

unsigned int GameSettings::maximumNumberOfPlayers() const
{
    return _maximumNumberOfPlayers;
}

void GameSettings::setMaximumNumberOfPlayers(unsigned int maximumNumberOfPlayers)
{
    _maximumNumberOfPlayers = maximumNumberOfPlayers;
}

unsigned int GameSettings::totalTimeToMove() const
{
    return _totalTimeToMove;
}

void GameSettings::setTotalTimeToMove(unsigned int totalTimeToMove)
{
    _totalTimeToMove = totalTimeToMove;
}

unsigned int GameSettings::timeToThink() const
{
    return _timeToThink;
}

unsigned int GameSettings::timeForOpponentsDecision() const
{
    return _timeForOpponentsDecision;
}

void GameSettings::setTimeForOpponentsDecision(unsigned int timeForOpponentsDecision)
{
    _timeForOpponentsDecision = timeForOpponentsDecision;
}

unsigned int GameSettings::diplomacyTime() const
{
    return _diplomacyTime;
}

void GameSettings::setDiplomacyTime(unsigned int diplomacyTime)
{
    _diplomacyTime = diplomacyTime;
}

bool GameSettings::hasAddonClericalErrors() const
{
    return _hasAddonClericalErrors;
}

void GameSettings::setHasAddonClericalErrors(bool hasAddonClericalErrors)
{
    _hasAddonClericalErrors = hasAddonClericalErrors;
}

bool GameSettings::hasAddonWildAxe() const
{
    return _hasAddonWildAxe;
}

void GameSettings::setHasAddonWildAxe(bool hasAddonWildAxe)
{
    _hasAddonWildAxe = hasAddonWildAxe;
}

QString GameSettings::clientName() const
{
    return _clientName;
}

void GameSettings::setClientName(const QString &clientName)
{
    _clientName = clientName;
}

RulesType GameSettings::rulesType() const
{
    return _rulesType;
}

void GameSettings::setRulesType(const RulesType &rulesType)
{
    _rulesType = rulesType;
}

void GameSettings::setTimeToThink(unsigned int timeToThink)
{
    _timeToThink = timeToThink;
}

bool GameSettings::settingsCorrectionAllowed() const
{
    return _settingsCorrectionAllowed;
}

void GameSettings::setSettingsCorrectionAllowed(bool settingCorrectionAllowed)
{
    _settingsCorrectionAllowed = settingCorrectionAllowed;
}

QString GameSettings::roomName() const
{
    return _roomName;
}

void GameSettings::setRoomName(const QString &roomName)
{
    _roomName = roomName;
}

GameSettings::GameSettings()
{
    //to Debug set this value to 2!
    _maximumNumberOfPlayers = 2;
    _totalTimeToMove = 120;
    _timeToThink = 15;
    _timeForOpponentsDecision = 10;
    _diplomacyTime = 30;
    _hasAddonClericalErrors = true;
    _hasAddonWildAxe = true;
    _settingsCorrectionAllowed = true;
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    QString::number(qrand() % ((99999 + 1) - 1) + 1);
    _clientName = "EmpERRoR" + QString::number(qrand() % ((99999 + 1) - 1) + 1);
    _roomName = "Room" + QString::number(qrand() % ((99999 + 1) - 1) + 1);

    _rulesType = RulesType::Automatic;
}

GameSettings::GameSettings(const GameSettings &settings)
{
    _maximumNumberOfPlayers = settings.maximumNumberOfPlayers();
    _totalTimeToMove = settings.totalTimeToMove();
    _timeToThink = settings.timeToThink();
    _timeForOpponentsDecision = settings.timeForOpponentsDecision();
    _diplomacyTime = settings.diplomacyTime();
    _hasAddonClericalErrors = settings.hasAddonClericalErrors();
    _hasAddonWildAxe = settings.hasAddonWildAxe();
    _clientName = settings.clientName();
    _roomName = settings.roomName();
    _rulesType = settings.rulesType();
    _settingsCorrectionAllowed = settings.settingsCorrectionAllowed();  
}

void GameSettings::applyNewSettings(const GameSettings &settings)
{
    _maximumNumberOfPlayers = settings.maximumNumberOfPlayers();
    _totalTimeToMove = settings.totalTimeToMove();
    _timeToThink = settings.timeToThink();
    _timeForOpponentsDecision = settings.timeForOpponentsDecision();
    _diplomacyTime = settings.diplomacyTime();
    _hasAddonClericalErrors = settings.hasAddonClericalErrors();
    _hasAddonWildAxe = settings.hasAddonWildAxe();
    _clientName = settings.clientName();
    _roomName = settings.roomName();
    _rulesType = settings.rulesType();
    _settingsCorrectionAllowed = settings.settingsCorrectionAllowed();
}
