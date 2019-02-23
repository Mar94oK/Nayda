#ifndef SMARTQTLOGGER_H
#define SMARTQTLOGGER_H
#include <QDebug>



enum class LoggerLevel
{
    Info = 0,
    Warning,
    Debug,
    Error,
    Essential,
    TaskCompletion,
    Observation,
    All
};

static const LoggerLevel logLevel = LoggerLevel::All;

class Logger
{
private:

    static const std::vector<LoggerLevel> levels;
    LoggerLevel _currentMessageLevel = LoggerLevel::All;

private:

    QString GetLogLevelName(LoggerLevel type)
    {
        switch (type)
        {
        case LoggerLevel::Info:
            return "===Info===";

        default:
            break;
        }
    }

public:

    template <typename T>
    Logger& operator<< (const T& message)
    {
        if (std::find(levels.begin(), levels.end(), _currentMessageLevel) != levels.end() )

    }

};

const std::vector<LoggerLevel>Logger::levels = { LoggerLevel::All };

#endif // SMARTQTLOGGER_H
