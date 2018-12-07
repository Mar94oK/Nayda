#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QString>

enum class RulesType {Automatic, Manual};

class GameSettings
{

private:

    unsigned int _maximumNumberOfPlayers;
    unsigned int _totalTimeToMove;
    unsigned int _timeToThink;
    unsigned int _timeForOpponentsDecision;
    unsigned int _diplomacyTime;
    bool         _hasAddonClericalErrors;
    bool         _hasAddonWildAxe;
    QString      _clientName;
    QString      _roomName;
    RulesType    _rulesType;
    bool         _settingsCorrectionAllowed;

private:
    //GameProcessSettings:
    bool _HardCodedSettings_AllowedToSellAtLevelNine = true;
    bool _HardCodedSettings_AllowedToOverSellAtLevelNine = true;
    bool _HardCodedSettings_AllowLevelOverSell = false;

public:
    GameSettings();
    GameSettings(unsigned int maxNumberOfPlayers, unsigned int totaltimeToMove,
                 unsigned int timeToThink, unsigned int timeForOpponentsDecision,
                 unsigned int diplomacyTime, bool AddonClericalErrors, bool hasAddonWildAxe,
                 const QString& clientName, const QString& roomName, RulesType rulesType, bool correctionAllowed = true) :
        _maximumNumberOfPlayers(maxNumberOfPlayers), _totalTimeToMove(totaltimeToMove),
        _timeToThink(timeToThink), _timeForOpponentsDecision(timeForOpponentsDecision),
        _diplomacyTime(diplomacyTime), _hasAddonClericalErrors(AddonClericalErrors),
        _hasAddonWildAxe(hasAddonWildAxe), _clientName(clientName), _roomName(roomName),
        _rulesType(rulesType), _settingsCorrectionAllowed(correctionAllowed)
    {}
    GameSettings(const GameSettings& settings);

    void applyNewSettings(const GameSettings& settings);

    unsigned int maximumNumberOfPlayers() const;
    void setMaximumNumberOfPlayers(unsigned int maximumNumberOfPlayers);
    unsigned int totalTimeToMove() const;
    void setTotalTimeToMove(unsigned int totalTimeToMove);
    unsigned int timeToThink() const;
    unsigned int timeForOpponentsDecision() const;
    void setTimeForOpponentsDecision(unsigned int timeForOpponentsDecision);
    unsigned int diplomacyTime() const;
    void setDiplomacyTime(unsigned int diplomacyTime);
    bool hasAddonClericalErrors() const;
    void setHasAddonClericalErrors(bool hasAddonClericalErrors);
    bool hasAddonWildAxe() const;
    void setHasAddonWildAxe(bool hasAddonWildAxe);
    QString clientName() const;
    void setClientName(const QString &clientName);
    RulesType rulesType() const;
    void setRulesType(const RulesType &rulesType);
    void setTimeToThink(unsigned int timeToThink);
    bool settingsCorrectionAllowed() const;
    void setSettingsCorrectionAllowed(bool settingCorrectionAllowed);
    QString roomName() const;
    void setRoomName(const QString &roomName);

    bool GetHardCodedSettingsAllowedToSellAtLevelNine() const { return _HardCodedSettings_AllowedToSellAtLevelNine; }
    bool GetHardCodedSettingsAllowedToOverSellAtLevelNine() const { return _HardCodedSettings_AllowedToOverSellAtLevelNine; }
    bool GetHardCodedSettingsAllowLevelOverSell() const { return _HardCodedSettings_AllowLevelOverSell; }
};

#endif // GAMESETTINGS_H
